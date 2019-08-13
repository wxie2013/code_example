// compile using: g++ parallel_2.C -o oo -lpthread
#include <iostream>
#include <cstdlib>
#include <vector>
#include <thread>

using namespace std;

const unsigned NUM_THREADS = std::thread::hardware_concurrency();


//
struct INPUT
{
    int start;
    int end;
    vector<int> data;
};

//
void *Loop(void *param)
{
   INPUT *in = (INPUT*)param;
   int start = in->start;
   int end = in->end;

   cout<<" start: "<<start<<" end: "<<end<<endl;
   for(int i = start;i < end;i++)
       for(int m=0; m<100000000; m++) {
           in->data.push_back(i);
       }

   pthread_exit(NULL);
}

int main ()
{
   pthread_t threads[NUM_THREADS];

   INPUT input[NUM_THREADS];

   for( int i=0; i < NUM_THREADS; i++ ){
      cout << "main() : creating thread, " << i << endl;

      input[i].start = i*5;
      input[i].end = input[i].start + 5;
      int rc = pthread_create(&threads[i], NULL,
                          Loop, (void *)&input[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }

   }
   for(int i = 0; i<NUM_THREADS; i++) 
   {
       pthread_join(threads[i], NULL);
       cout<<"!! size of "<<i<<": "<<input[0].data.size()<<endl;
   }
   pthread_exit(NULL);
}


