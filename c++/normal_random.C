// normal_distribution
#include <iostream>
#include <string>
#include <random>
#include "TNtuple.h"

//..see: https://stackoverflow.com/questions/55857740/using-normal-distribution-in-a-loop#55858126
using namespace std;
void normal_random()
{
    const int nrolls=1000000;  // number of experiments
    TNtuple* nt = new TNtuple("nt", "", "x");

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(5.0,2.0);

    for (int i=0; i<nrolls; ++i) {
        //std::normal_distribution<double> distribution(5.0,2.0); //.. can put here but less efficient
        float x = distribution(generator);
        nt->Fill(x);

    }

    nt->Draw("x");
}

