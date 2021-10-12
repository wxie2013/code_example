# define an objective function
def objective(params):
    # Note: params are dictionaries defined from the following 'space'
    #print(type(params))
    #print(params['test0'])
    case, val = params['test1']
    if case == 'case 1':
        return val
    else:
        return val ** 2

# define a search space
from hyperopt import hp
space = {
        'test0': hp.uniform('test0', 0.6, 1.0), 
        'test1': hp.choice('a',
            [
                ('case 1', 1 + hp.lognormal('c1', 0, 1)),
                ('case 2', hp.uniform('c2', -10, 10))
                ]
            )
        }

# minimize the objective over the space
from hyperopt import fmin, tpe
best = fmin(objective, space, algo=tpe.suggest, max_evals=100)

print (best)

