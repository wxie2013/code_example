#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

int main()
{
  const int nrolls=10000;  // number of experiments

  ofstream fout("oo.dat");

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(5.0,2.0);
  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    fout<<number<<endl;
  }

  return 0;
}

