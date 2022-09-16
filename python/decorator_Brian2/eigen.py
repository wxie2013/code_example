from brian2 import *

set_device('cpp_standalone', directory='standalone', debug=True)

@implementation('cuda', '''
          __host__ __device__ double add_more() {
             return 100;
          }
          ''')
@implementation('cpp', '''
      using Eigen::MatrixXd;
      double add_more() {
           MatrixXd m(2,2);
           m(0,0) = 3;
           m(1,0) = 2.5;
           m(0,1) = -1;
           m(1,1) = m(1,0) + m(0,1);
           std::cout << m << std::endl;

         return 100;
      }
      ''', 
      headers=['<Eigen/Dense>'],
      include_dirs=['/home/wxie/local_pkgs/eigen-3.4.0']
      )
@check_units(result=Hz)
def add_more():
    return 100;


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
