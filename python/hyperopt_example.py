# define an objective function
NNN = 9999

print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1")
def objective(params, idx_start=0, idx_end = 100, nnn = NNN):
    # Note: params are dictionaries defined from the following 'space'
    #print(type(params))
    #print(params['test0'])
    #print(idx_start, idx_end)
    print('test0: ', params['test0'])
    print('test1: ', params['test1'][0], params['test1'][1])
    print('test2: ', params['test2'])
    print('switch: ', params['switch'])
    print('nnn: ', nnn)
    case, val = params['test0']
    if case == 'case 1':
        print('1___: ', val)
    if case == 'case 2':
        print('2___: ', val)

    case, val = params['test2']
    if case == 'case 1':
        return val
    else:
        return val ** 2

# define a search space
from hyperopt import hp
space = {
        'switch': True, 
        'test0': hp.choice('s2', 
            [
                ('case 1', {'a': 10, 'b': hp.uniform('s', 100, 200)}), 
                ('case 2', {'c': 5, 'd': 20 }), 
                ]), 
        'test1': [hp.uniform('s0', 0.6, 1.0), hp.uniform('s1', 0., 0.6)], 
        'test2': hp.choice('a',
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

