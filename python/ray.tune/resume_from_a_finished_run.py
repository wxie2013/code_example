import os, time, ray
import pandas as pd
import multiprocessing
from ray import tune, air
from hyperopt import hp
from ray.tune.search.hyperopt import HyperOptSearch
from ray.tune.search import ConcurrencyLimiter
from ray.tune.schedulers import ASHAScheduler

# disable dash board. See: https://discuss.ray.io/t/disable-dashboard/8471
ip_head = os.getenv("ip_head")
if ip_head != None:
    ray.init(address=ip_head)
else:
    print('-- running without a cluster ---')

n_epoch = 2

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
    "a": hp.uniform("a", 0, 1),
    "b": hp.uniform("b", 0, 1)
    }

raw_log_dir = "./ray_log"
raw_log_name = "example"

initial_params = [
        {"a": 1, "b": 1},
        ]
algorithm = HyperOptSearch(search_space, metric="SCORE", mode="max", n_initial_points=8, points_to_evaluate=initial_params)
algorithm = ConcurrencyLimiter(algorithm, max_concurrent=8)
if os.path.exists(os.path.join(raw_log_dir, raw_log_name)) == False:
    print('--- this is the 1st run ----')
else: #note: restoring described here doesn't work: https://docs.ray.io/en/latest/tune/tutorials/tune-stopping.html 
    print('--- previous run exist, continue the tuning ----')
    algorithm.restore_from_dir(os.path.join(raw_log_dir, raw_log_name))

# 3. Start a Tune run and print the best result.

trainable_with_resources = tune.with_resources(objective, {"cpu": 1})
#trainable_with_resources = tune.with_resources(objective, {"cpu": multiprocessing.cpu_count()})
tuner = tune.Tuner(
        #tune.with_parameters(trainable_with_resources, data = "aaaa"),
        trainable_with_resources,
        tune_config = tune.TuneConfig(
            num_samples = 100, # number of tries. too expensive for Brian2
            time_budget_s = 10000, # tot running time in seconds
            search_alg=algorithm, 
            scheduler=ASHAScheduler(metric="SCORE", mode="max"),
            ),
        run_config = air.RunConfig(local_dir = raw_log_dir, name = raw_log_name) # where to save the log which will be loaded later
        )

results = tuner.fit()
best_result = results.get_best_result(metric="SCORE", mode="max")
print('--1: config: ', best_result.config)
print('--2: log_dir: ', best_result.log_dir)
print('--3: SCORE: ', best_result.metrics['SCORE'])
print('--4: trial_id: ', best_result.metrics['trial_id'])
print('--5: experiment_id: ', best_result.metrics['experiment_id'])
print('--6: all metrics: ', best_result.metrics) # contains all metrics 

# Obtain a trial dataframe from all run trials of this `tune.run` call.
dfs = {result.log_dir: result.metrics_dataframe for result in results}
for d in dfs.values():
    print(d.SCORE) # this print out SCORE vs. epoch

# save it to CSV file for future analysis
csv_name = "all_trials.csv"
for df in dfs.values():
    df.to_csv("all_trials.csv", index_label="epoch", mode='a')

# now read it and printout epoch vs. SCORE
dfs2 = pd.read_csv("all_trials.csv")
for epoch, score in zip(dfs2.epoch, dfs2.SCORE):
    print(epoch, score)
