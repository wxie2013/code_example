import os
from ray import tune, air
from hyperopt import hp
from ray.tune.search.hyperopt import HyperOptSearch


# 1. Define an objective function.
def objective(config):
    score = config["a"] ** 2 + config["b"]
    #SCORE 1st apparence which defines the key of the dictionary, i.e. metric="SCORE", 
    # or  return {"SCORE": score}
    tune.report(SCORE=score)  # this or the following return should work
    #return {"SCORE": score}


# 2. Define a search space.
search_space = {
    "a": hp.uniform("a", 0, 1),
    "b": hp.uniform("b", 0, 1)
    }

raw_log_dir = "./ray_log"
raw_log_name = "example"

algorithm = HyperOptSearch(search_space, metric="SCORE", mode="max", n_initial_points=1)
if os.path.exists(os.path.join(raw_log_dir, raw_log_name)) == False:
    print('--- this is the 1st run ----')
else: #note: restoring described here doesn't work: https://docs.ray.io/en/latest/tune/tutorials/tune-stopping.html 
    print('--- previous run exist, continue the tuning ----')
    algorithm.restore_from_dir(os.path.join(raw_log_dir, raw_log_name))

# 3. Start a Tune run and print the best result.

trainable_with_resources = tune.with_resources(objective, {"cpu": 8})
tuner = tune.Tuner(objective, 
        tune_config = tune.TuneConfig(
            num_samples = 100, # number of tries. too expensive for Brian2
            search_alg=algorithm, 
            ),
        param_space=search_space, 
        run_config = air.RunConfig(local_dir = raw_log_dir, name = raw_log_name) # where to save the log which will be loaded later
        )

results = tuner.fit()
print(results.get_best_result(metric="SCORE", mode="max").config)
