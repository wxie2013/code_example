#template for running mm.py
@implementation('cpp', cpp_code, dependencies={'ta2d': ta2d})
@check_units(t=second, i=1, result=1)
def spike_rate(scale, t, i):
    raise NotImplementedError('use standalone mode')
