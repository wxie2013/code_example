#include <iostream>

using namespace std;
int main(){
  const unsigned int ArraySize = 10000000;
  float* a = new float[ArraySize];
  float* b = new float[ArraySize];
  float* c = new float[ArraySize];

  for (unsigned int j = 0; j< 200 ; j++) // some repetitions
    for ( unsigned int i = 0; i < ArraySize; ++ i) {
      a[i] = i;
      b[i] = j;
      c[i] += a[i] * b[i];
    }

  float tot = 0;
  for(unsigned int i = 0; i < ArraySize; ++ i)
    tot += c[i];

  cout<<"tot: "<<tot<<endl;
}
