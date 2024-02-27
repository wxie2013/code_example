import os
import numpy as np
import random
import torch
import torch.nn as nn
import torch.nn.functional as F
from filelock import FileLock
from torch.utils.data import DataLoader, random_split, Subset
from torchmetrics import Accuracy
from torchvision.datasets import MNIST
from torchvision import transforms

import pytorch_lightning as pl
from pytorch_lightning import trainer
from pytorch_lightning.loggers.csv_logs import CSVLogger

class MNISTDataModule(pl.LightningDataModule):
    def __init__(self, batch_size=100):
        super().__init__()
        self.data_dir = os.getcwd()
        self.batch_size = batch_size
        self.transform = transforms.Compose(
            [transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))]
        )

    def setup(self, stage=None):
        with FileLock(f"{self.data_dir}.lock"):
            mnist = MNIST(
                self.data_dir, train=True, download=True, transform=self.transform
            )

            # Split data into train and val sets
            self.mnist_train, self.mnist_val = random_split(mnist, [55000, 5000])

    def train_dataloader(self):
        return DataLoader(self.mnist_train, batch_size=self.batch_size, num_workers=4)

    def val_dataloader(self):
        return DataLoader(self.mnist_val, batch_size=self.batch_size, num_workers=4)

    def test_dataloader(self):
        with FileLock(f"{self.data_dir}.lock"):
            self.mnist_test = MNIST(
                self.data_dir, train=False, download=True, transform=self.transform
            )

        return DataLoader(self.mnist_test, batch_size=self.batch_size, num_workers=4)

#
class MNISTClassifier(pl.LightningModule):
    def __init__(self, lr=1e-3, feature_dim=128):
        torch.manual_seed(421)
        super(MNISTClassifier, self).__init__()
        self.save_hyperparameters()

        self.linear_relu_stack = nn.Sequential(
            nn.Linear(28 * 28, feature_dim),
            nn.ReLU(),
            nn.Linear(feature_dim, 10),
            nn.ReLU(),
        )

        self.lr = lr
        self.accuracy = Accuracy(task="multiclass", num_classes=10, top_k=1)
        self.eval_loss = []
        self.eval_accuracy = []
        self.test_accuracy = []
        pl.seed_everything(888)

    def forward(self, x):
        x = x.view(-1, 28 * 28)
        x = self.linear_relu_stack(x)
        return x

    def training_step(self, batch, batch_idx):
        x, y = batch
        y_hat = self(x)
        loss = torch.nn.functional.cross_entropy(y_hat, y)
        self.log("train_loss", loss)
        return loss

    def validation_step(self, val_batch, batch_idx):
        loss, acc = self._shared_eval(val_batch)
        self.log("val_accuracy", acc)
        self.eval_loss.append(loss)
        self.eval_accuracy.append(acc)

        return {"val_loss": loss, "val_accuracy": acc}

    def test_step(self, test_batch, batch_idx):
        loss, acc = self._shared_eval(test_batch)
        self.test_accuracy.append(acc)
        self.log("test_accuracy", acc, sync_dist=True, on_epoch=True)
        return {"test_loss": loss, "test_accuracy": acc}



    def _shared_eval(self, batch):
        x, y = batch
        logits = self.forward(x)
        loss = F.nll_loss(logits, y)
        acc = self.accuracy(logits, y)
        return loss, acc

    def on_validation_epoch_end(self):
        avg_loss = torch.stack(self.eval_loss).mean()
        avg_acc = torch.stack(self.eval_accuracy).mean()
        self.log("val_loss", avg_loss, sync_dist=True)
        self.log("val_accuracy", avg_acc, sync_dist=True)
        self.eval_loss.clear()
        self.eval_accuracy.clear()

    def configure_optimizers(self):
        optimizer = torch.optim.Adam(self.parameters(), lr=self.lr)
        return optimizer

use_gpu = False # Set to False if you want to run without GPUs
num_workers = 4

import pytorch_lightning as pl
from ray.train import RunConfig, ScalingConfig, CheckpointConfig
from ray.train.torch import TorchTrainer
from ray.train.lightning import (
    RayDDPStrategy,
    RayLightningEnvironment,
    RayTrainReportCallback,
    prepare_trainer,
)

def train_func_per_worker():
    model = MNISTClassifier(lr=1e-3, feature_dim=128)
    datamodule = MNISTDataModule(batch_size=128)
    trainer = pl.Trainer(
        devices="auto",
        strategy=RayDDPStrategy(),
        plugins=[RayLightningEnvironment()],
        callbacks=[RayTrainReportCallback()],
        max_epochs=10,
        accelerator="gpu" if use_gpu else "cpu",
        log_every_n_steps=100,
        logger=CSVLogger("logs"),
    )

    trainer = prepare_trainer(trainer)

    # Train model
    trainer.fit(model, datamodule=datamodule)

    # Evaluation on the test dataset
    trainer.test(model, datamodule=datamodule)

scaling_config = ScalingConfig(num_workers=num_workers, use_gpu=use_gpu)
run_config = RunConfig(
    name="ptl-mnist-example",
    storage_path="/tmp/ray_results",
    checkpoint_config=CheckpointConfig(
        num_to_keep=3,
        checkpoint_score_attribute="val_accuracy",
        checkpoint_score_order="max",
    ),
)

trainer = TorchTrainer(
    train_func_per_worker,
    scaling_config=scaling_config,
    run_config=run_config,
)

result = trainer.fit()
