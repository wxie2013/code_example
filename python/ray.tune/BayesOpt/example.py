import os, time, ray
import pandas as pd
import multiprocessing
from ray import tune, air
from hyperopt import hp
from ray.tune.search.bayesopt import BayesOptSearch
from ray.tune.search import ConcurrencyLimiter
from ray.tune.schedulers import ASHAScheduler

# disable dash board. See: https://discuss.ray.io/t/disable-dashboard/8471
ip_head = os.getenv("ip_head")
if ip_head != None:
    ray.init(address=ip_head)
else:
    print('-- running without a cluster ---')

n_epoch = 2

raw_log_dir = "./ray_log"
raw_log_name = "example"

def define_tuner(search_space = None):
    trainable_with_resources = tune.with_resources(objective, {"cpu": 1})
    #trainable_with_resources = tune.with_resources(objective, {"cpu": multiprocessing.cpu_count()})
    tuner = tune.Tuner(
            #tune.with_parameters(trainable_with_resources, data = "aaaa"),
            trainable_with_resources,
            tune_config = tune.TuneConfig(
                num_samples = 5, # number of tries. too expensive for Brian2
                time_budget_s = 10000, # tot running time in seconds
                search_alg=algorithm, 
                scheduler=ASHAScheduler(metric="SCORE", mode="max"),
                ),
            param_space = search_space,
            run_config = air.RunConfig(storage_path = raw_log_dir, name = raw_log_name, verbose=2) # where to save the log which will be loaded later
            )
    return tuner

# 1. Define an objective function.
def objective(config, data = None):
    #time.sleep(60)
    f = open(os.path.join(os.getcwd(), "oo.root"), "w")
    for i in range(n_epoch): 
        score = config["a"] ** 2 + config["b"]
        #SCORE 1st apparence which defines the key of the dictionary, i.e. metric="SCORE", 
        # or  return {"SCORE": score}
        tune.report(SCORE=score)  # this or the following return should work
        #return {"SCORE": score}


# 2. Define a search space.
search_space = {
        "a": tune.uniform(0, 1),
        "b": tune.uniform(0, 1)
    }


initial_params = [
        {"a": 0.5, "b": 0.5},
        ]
algorithm = BayesOptSearch(
        metric="SCORE", 
        mode="max", 
        points_to_evaluate=initial_params)
algorithm = ConcurrencyLimiter(algorithm, max_concurrent=8)
if os.path.exists(os.path.join(raw_log_dir, raw_log_name)) == False:
    print('--- this is the 1st run ----')
    tuner = define_tuner(search_space)
else:  # the difference from the 1st run is w/o param_space because it's already defined in the 1st run and restore_from_dir() will have them defined.
    print('--- previous run exist, continue the tuning ----')
    algorithm.restore_from_dir(os.path.join(raw_log_dir, raw_log_name))
    tuner = define_tuner()

# 3. Start a Tune run and print the best result.
results = tuner.fit()
best_result = results.get_best_result(metric="SCORE", mode="max")
print('--1: config: ', best_result.config)
print('--2: log_dir: ', best_result.log_dir)
print('--3: SCORE: ', best_result.metrics['SCORE'])
print('--4: trial_id: ', best_result.metrics['trial_id'])
