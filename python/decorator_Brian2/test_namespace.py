import os
from brian2 import *

set_device('cpp_standalone', directory='standalone', debug=True)
current_dir = os.path.abspath(os.path.dirname(__file__))

@implementation('cpp', '''
     using namespace aaa;
     double test() {
        return val;
     }
     ''', 
     headers=['"namespace.h"'],
     sources=[os.path.join(current_dir, 'namespace.cpp')], 
     include_dirs=[current_dir]
     )
@check_units(result=Hz)
def test():
    raise NotImplementedError('use standalone mode')
##
input = PoissonGroup(10, rates='test()')
run(1*second, report='text')
