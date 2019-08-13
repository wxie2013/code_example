#include "ttt.h"

//
void ttt::calculate()
{
    auto start = high_resolution_clock::now();
    example.calculate();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<" time: "<<duration.count()*1e-6<<" seconds"<<endl;

    start = high_resolution_clock::now();
    example_thread.calculate();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<" time: "<<duration.count()*1e-6<<" seconds"<<endl;
}

