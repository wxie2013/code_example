#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXf;
using Eigen::VectorXf;

int main()
{
  int nrow = 2;
  int ncol = 2;
  MatrixXf m(nrow, ncol);

  m << 1,2, 
       3,4;

  for(int i = 0; i<2; i++) {
    std::cout<<"col"<<i<<": "<<m.col(i)<<std::endl;
    std::cout<<"   num element > 0: "<<(m.col(i).array()>0).count()<<std::endl;
    std::cout<<"   sum of col"<<i<<": "<<m.col(i).sum()<<std::endl;
  }

  VectorXf v(2);
  v(0)=2;
  v(1)=3;

  //create a new matrix using the existing vector for element wise operation, e.g. m*n
  MatrixXf n(nrow, ncol);
  for(int i = 0; i<m.cols(); i++) 
    n.row(i) = v;

  m.array() = m.array()*n.array();

  std::cout<<"matrix n: "<<n<<std::endl;
  std::cout<<"m*n (element-wise): "<<m.array()<<std::endl;
  std::cout<<"m flatten: "<<m.transpose().reshaped(1,nrow*ncol)<<std::endl;

  Eigen::MatrixXf tv = m.transpose().reshaped(1,nrow*ncol);

  float *tt;
  Eigen::MatrixXf::Map(tt, tv.rows(), tv.cols()) = tv;

  for(int i = 0; i<tv.cols(); i++) 
    std::cout<<tt[i]<<std::endl;
}
