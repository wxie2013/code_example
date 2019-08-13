#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <map>
using namespace std;

const int NUM_THREADS = 8;

std::mutex mu;

int main()
{

    std::map<int, int> mapOfWords;

    for(int i = 0; i<10000; i++) 
        mapOfWords.insert(std::make_pair(i, i+5));

    std::thread td[NUM_THREADS];

    unsigned int gap = 100;
    for(unsigned int i = 0; i< NUM_THREADS; i++) {

        int idx_start = i*gap;
        int idx_end = idx_start+gap;
        if(i==NUM_THREADS-1) 
            idx_end = mapOfWords.size()-1;

        //.. direct pass to lambda by reference does not work and leads to errors
        //auto it_s = std::next(mapOfWords.begin(), idx_start);
        //auto it_e = std::next(it_s, gap);

        // passing idx_start, idx_end by reference doesn't work and lead to error
        //.. need to pass by value 
        auto split_loop = [&](int is, int ie, int idx)
        {

            mu.lock();
            auto it_s = std::next(mapOfWords.begin(), is);
            auto it_e = std::next(mapOfWords.begin(), ie);
            cout<<"idx_thread: "<< idx<<" it_s.first: "<<it_s->first<<" it_s.second: "<<it_s->second<<" it_e.first: "<<it_e->first<<" it_e.second: "<<it_e->second<<endl;
            mu.unlock();
        };


        td[i] = std::thread(split_loop, idx_start, idx_end, i);
    }
    //
    for(unsigned int i = 0; i< NUM_THREADS; i++) {
        td[i].join();
    }

}
