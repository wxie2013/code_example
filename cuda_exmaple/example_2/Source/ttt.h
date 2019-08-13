#ifndef TTT_H
#define TTT_H

#include "add.h"
#include "add_thread.h"

#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

class ttt
{
    private: 
        ADD example;
        ADD_thread example_thread;
    public:
        ttt() {;}
        void calculate();
};

#endif
