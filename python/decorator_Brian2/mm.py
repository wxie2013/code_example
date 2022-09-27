import os
from brian2 import *

def read_spike_rate_code(spike_mon_obj):
    with open(os.path.join(current_dir,'spike_rate.cpp')) as f:
        spike_rate_code = f.read()

    return spike_rate_code.replace('%%SPIKECOUNT%%',
        device.get_array_name(spikemon.variables['count']))



current_dir = os.path.dirname(__file__)
set_device('cpp_standalone', directory='standalone', debug=True)

ta2d = TimedArray([[1, 2, 3, 4, 5, 6], [100, 200, 300, 400, 500, 600]], dt=0.2*ms)

N = 6
input_neurons = NeuronGroup(N, '''rate : Hz
                                  scale: 1''', threshold='rand()<rate*dt')
spikemon = SpikeMonitor(input_neurons)

spike_rate_code = read_spike_rate_code(spikemon)
@implementation('cpp', spike_rate_code,
                dependencies={'ta2d': ta2d})
@check_units(t=second, i=1, result=1)
def spike_rate(scale, t, i):
    raise NotImplementedError('use standalone mode')

input_neurons.scale = [0.1, 1, 10, 100, 1000, 10000]
input_neurons.run_regularly('rate=spike_rate(scale, t, i)*Hz', dt=0.2*ms)
run(0.3*ms, report='text')
print(input_neurons.rate[:])