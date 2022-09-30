import os, subprocess
from brian2 import *

ta2d = TimedArray([[1, 2, 3, 4, 5, 6], [100, 200, 300, 400, 500, 600]], dt=0.2*ms)

# generate user cpp function and it's decorator
def generate_user_cpp_function(cpp_infile, py_infile, outfile, obj_name):
    current_dir = os.path.dirname(__file__)
    # load the cpp function template
    with open(os.path.join(current_dir, cpp_infile)) as f:
        cpp_code = f.read()

    # load the cpp python decorator template
    with open(os.path.join(current_dir, py_infile)) as f:
        py_code = f.read()

    py_code = (py_code.replace('cpp_code', "'''"+cpp_code+"'''").
            replace('spike_rate', 'spike_rate_'+obj_name).
            replace('brian::_array_syn_count', 'brian::_array_'+obj_name+'_count')
            )
    pyfile = open(outfile, 'w')
    pyfile.write(py_code)
    pyfile.close()

#
set_device('cpp_standalone', directory='standalone', debug=True)

N = 6
input_neurons = NeuronGroup(N, '''rate : Hz
                                  scale: 1''', threshold='rand()<rate*dt')
spikemon = SpikeMonitor(input_neurons, name='ttt')
input_neurons.scale = [0.1, 1, 10, 100, 1000, 10000]
input_neurons.run_regularly('rate=spike_rate_'+spikemon.name+'(scale, t, i)*Hz', dt=0.2*ms)
 
# generate user function python file before run
fname = "user_func.py"
generate_user_cpp_function('spike_rate.cpp', 'cpp_decorator.py', fname, spikemon.name)
exec(open(fname).read()) # embed it into the current script

##
run(0.3*ms, report='text')
print(input_neurons.rate[:])
