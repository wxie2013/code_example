import os
from typing import Dict
import torch
from filelock import FileLock
from torch import nn
from torch.utils.data import DataLoader
from torchvision import datasets, transforms
from torchvision.transforms import Normalize, ToTensor
from tqdm import tqdm
import ray.train
from ray.train import ScalingConfig
from ray.train.torch import TorchTrainer
import numpy as np

def get_dataloaders(batch_size):
    # Transform to normalize the input images
    transform = transforms.Compose([ToTensor()]) # normalize pixel to [0,1]

    with FileLock(os.path.expanduser("~/data.lock")):
        # Download training data from open datasets
        training_data = datasets.MNIST(
            root="~/data",
            train=True,
            download=True,
            transform=transform,
        )

        # Download test data from open datasets
        test_data = datasets.MNIST(
            root="~/data",
            train=False,
            download=True,
            transform=transform,
        )


    # Create data loaders
    train_dataloader = DataLoader(training_data, batch_size=batch_size)
    test_dataloader = DataLoader(test_data, batch_size=batch_size)

    return train_dataloader, test_dataloader

# Model Definition
class NeuralNetwork(nn.Module):
    def __init__(self):
        super(NeuralNetwork, self).__init__()
        self.ttt = 0.1

    def forward(self, x, y):
        x = x.numpy()*255  # resize the pixel amplitude to [0,255]
        print('1-----: ', x.shape) #(8, 1, 28, 28). [batch_size, channel, width, height]. channel: Black/wihte channel, dim = 1. RGB channel, dim = 3
        print('2-----: ', y.numpy())

        logits = self.ttt
        return logits

def train_func_per_worker(config: Dict):
    lr = config["lr"]
    epochs = config["epochs"]
    batch_size = config["batch_size_per_worker"]

    # Get dataloaders inside the worker training function
    train_dataloader, test_dataloader = get_dataloaders(batch_size=batch_size)

    # [1] Prepare Dataloader for distributed training
    # Shard the datasets among workers and move batches to the correct device
    # =======================================================================
    train_dataloader = ray.train.torch.prepare_data_loader(train_dataloader)
    test_dataloader = ray.train.torch.prepare_data_loader(test_dataloader)

    model = NeuralNetwork()

    # [2] Prepare and wrap your model with DistributedDataParallel
    # Move the model to the correct GPU/CPU device

    # ============================================================
    model = ray.train.torch.prepare_model(model, parallel_strategy=None)

    # Model training loop
    for epoch in range(epochs):
        for X, y in tqdm(train_dataloader, desc=f"Train Epoch {epoch}"):
            pred = model(X, y)
            print(pred)

        for X, y in tqdm(test_dataloader, desc=f"Test Epoch {epoch}"):
            pred = model(X, y)

        # [3] Report metrics to Ray Train
        # ===============================
        ray.train.report(metrics={"loss": 0, "accuracy": 1})

def train_fashion_mnist(num_workers=2, use_gpu=False):
    global_batch_size = 32
    train_config = {
        "lr": 1e-3,
        "epochs": 5,
        "batch_size_per_worker": global_batch_size // num_workers,
    }

    # Configure computation resources
    scaling_config = ScalingConfig(num_workers=num_workers, use_gpu=use_gpu)

    # Initialize a Ray TorchTrainer
    trainer = TorchTrainer(
        train_loop_per_worker=train_func_per_worker,
        train_loop_config=train_config,
        scaling_config=scaling_config,
    )

    # [4] Start distributed training
    # Run `train_func_per_worker` on all workers
    # =============================================
    result = trainer.fit()
    print(f"Training result: {result}")

if __name__ == "__main__":

    train_fashion_mnist(num_workers=4, use_gpu=False)

