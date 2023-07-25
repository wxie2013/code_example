import json
import os
from pathlib import Path
import tempfile
import shutil
import time

import ray
from ray import tune
from ray.air import RunConfig, Checkpoint, session, FailureConfig, CheckpointConfig
from ray.air._internal.remote_storage import download_from_uri, delete_at_uri
from ray.tune import Trainable, Callback
from ray.tune.execution.trial_runner import _find_newest_experiment_checkpoint
from ray.tune.experiment import Trial
from ray.tune.tune_config import TuneConfig
from ray.tune.tuner import Tuner

def _train_fn_sometimes_failing(config, checkpoint_dir=None):
    # Fails if failing is set and marker file exists.
    # Hangs if hanging is set and marker file exists.
    failing, hanging = config["failing_hanging"]
    print('0--: ', failing, hanging)

    if checkpoint_dir:
        state = Checkpoint.from_directory(checkpoint_dir).to_dict()
    else:
        state = {"it": 0}

    print('1--: ', config.get("num_epochs", 1))
    for i in range(config.get("num_epochs", 1)):
        state["it"] += 1
        print('2--: ', state["it"])

        session.report(state, checkpoint=Checkpoint.from_dict(state))

    # We fail after reporting num_epochs checkpoints.
    if failing == 'failing':
        raise RuntimeError("I am failing")

    if hanging  == 'hanging':
        time.sleep(60)

    state["it"] += 1
    print('2--: ', state["it"])

    session.report(state, checkpoint=Checkpoint.from_dict(state))


class _FailOnStats(Callback):
    """Fail when at least num_trials exist and num_finished have finished."""

    def __init__(self, num_trials: int, num_finished: int, delay: int = 1):
        self.num_trials = num_trials
        self.num_finished = num_finished
        self.delay = delay
        self.fail_at = None

    def on_step_begin(self, iteration: int, trials: list, **info):
        if self.fail_at and iteration >= self.fail_at:
            print(
                "Actually failing after delay:",
                [(t.status, t.last_result.get("it")) for t in trials],
            )
            raise RuntimeError("Failing")

        if len(trials) < self.num_trials:
            return

        if (
            len([t for t in trials if t.status in [Trial.TERMINATED, Trial.ERROR]])
            >= self.num_finished
        ):
            self.fail_at = iteration + self.delay
            print(
                f"Triggering fail in {self.delay} iterations:",
                [(t.status, t.last_result.get("it")) for t in trials],
            )
        else:
            print("Not failing:", [(t.status, t.last_result.get("it")) for t in trials])


def test_tuner_resume_unfinished():
    trainable_with_resources = tune.with_resources(_train_fn_sometimes_failing, {"cpu": 4})
    tuner = Tuner(
        trainable_with_resources,
        tune_config=TuneConfig(num_samples=1),
        run_config=RunConfig(
            name="test_tuner_resume_unfinished",
            local_dir=os.getcwd(),
            failure_config=FailureConfig(fail_fast=False),
            callbacks=[_FailOnStats(num_trials=4, num_finished=2, delay=1)],
        ),
        param_space={
            # First trial succeeds, second hangs, third fails, fourth hangs
            "failing_hanging": tune.grid_search(
                [
                    (None, None),
                    (None, 'failing'),
                    ('failing', None),
                    (None, 'hanging'),
                ]
            ),
        },
    )
    # Catch the FailOnStats erro
    try:
        results = tuner.fit()
    except:
        print('----- got an error, go to next step -----')

    # After this run we have the following trial states (status, metric):
    # [('TERMINATED', 2), ('RUNNING', 1), ('ERROR', 1), ('PENDING', None)]

    # Restarting without hanging/failing should lead to the results:
    # [2, 3, 1, 2], because:
    # the TERMINATED trial is finished (state = 2),
    # the RUNNING trial is continued (and picks up from state = 1 for 2 iterations),
    # the ERROR trial is not continued (remains at 1 and errored)
    # and the PENDING trial has not state, yet.

    del tuner

    print('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
    tuner = Tuner.restore(os.path.join(os.getcwd(), "test_tuner_resume_unfinished"))
    tuner._local_tuner._run_config.callbacks = None

    results = tuner.fit()
    assert len(results) == 4
    assert len(results.errors) == 1
    assert sorted([r.metrics["it"] for r in results]) == sorted([2, 3, 1, 2])

if __name__ == '__main__':
    test_tuner_resume_unfinished()
