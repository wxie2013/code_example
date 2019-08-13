#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
using namespace std;

const int NUM_THREADS = 8;

std::mutex mu;

int main()
{
    std::thread td[NUM_THREADS];
    int tot = 100000;

    unsigned int gap = 1000;
    for(unsigned int i = 0; i< NUM_THREADS; i++) {

        unsigned int idx_start = i*gap;
        unsigned int idx_end = idx_start+gap;

        // passing idx_start, idx_end by reference doesn't work and lead to error
        //.. need to pass by value 
        auto split_loop = [&](unsigned int is, unsigned int ie, int idx)
        {

            mu.lock();
            cout<<"2_  i:"<<idx<<" idx_start: "<<is<<" idx_end: "<<ie<<endl;
            mu.unlock();
        };


        td[i] = std::thread(split_loop, idx_start, idx_end, i);
    }
    //
    for(unsigned int i = 0; i< NUM_THREADS; i++) {
        td[i].join();
    }

}
