from brian2 import *
import brian2cuda

set_device('cuda_standalone', directory='standalone', debug=True)
#set_device('cpp_standalone', directory='standalone', debug=True)

@implementation('cuda', '''
          __host__ __device__ double add_more() {
             return 100;
          }
          ''')
@implementation('cpp', '''
      double add_more() {
         return 100;
      }
      ''')
@check_units(result=Hz)
def add_more():
    return 100;


@implementation('cuda', '''
        __host__ __device__ double ttt() {
        return 100 + add_more();
        }
        ''', dependencies={'add_more':add_more})
@implementation('cpp', '''
     double ttt() {
        return 100 + add_more();
     }
     ''', dependencies={'add_more':add_more})
@check_units(result=Hz)
def ttt():
    raise NotImplementedError('use standalone mode')
##
input = PoissonGroup(10, rates='ttt()')
run(1*second, report='text')

