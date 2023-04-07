import importlib, os

mdir = 'Brian2.jobs_sub.ray_tune.'
input_param = importlib.import_module(mdir+'input_param')
print(input_param.n_grp_train)
