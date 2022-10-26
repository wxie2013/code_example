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

hyperopt_search = HyperOptSearch(search_space, metric="SCORE", mode="max")

# 3. Start a Tune run and print the best result.
tuner = tune.Tuner(objective, 
        tune_config = tune.TuneConfig(
            num_samples = 5, # number of tries. too expensive for Brian2
            search_alg=hyperopt_search, 
            ),
        param_space=search_space
        )
results = tuner.fit()
print(results.get_best_result(metric="SCORE", mode="max").config)
