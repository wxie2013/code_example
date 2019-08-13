// CPP program to demonstrate multithreading 
// using three different callables. 
#include <iostream> 
#include <vector>
#include <thread> 
using namespace std; 
  
// A dummy function 
void foo(int Z, int X) 
{ 
    for (int i = 0; i < Z; i++) { 
        cout << "Thread using function"
               " pointer as callable\n"; 
    } 

    cout<<"!!!! X: "<<X<<endl;
} 
  
// A callable object 
class thread_obj { 
public: 
    void operator()(int x) 
    { 
        for (int i = 0; i < x; i++) 
            cout << "Thread using function"
                  " object as  callable\n"; 
    } 
}; 

void fref(vector<int> &Z) 
{ 
    for (int i = 0; i < Z.size(); i++) { 
        Z[i] *=10;
    } 
} 
  
  
int main() 
{ 
    cout << "Threads 1 and 2 and 3 "
         "operating independently" << endl; 
  
    // This thread is launched by using  
    // function pointer as callable 
    thread th1(foo, 3, 10); 
  
    // This thread is launched by using 
    // function object as callable 
    thread th2(thread_obj(), 3); 
  
    // Define a Lambda Expression 
    int yy = 10;
    vector<int> vy {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto f = [&]() { 
        for (int i = 0; i < vy.size(); i++) 
            vy[i]+=10;
    }; 
  
    // This thread is launched by using  
    // lamda expression as callable 
    thread th3(f); 

    //Define a Lambda Expression
    auto f2 = [](int x) {
        cout<<" !!!! x"<<endl;
    };
    thread th4(f2, 1);

    //.. pass by reference: 
    thread th5(fref, std::ref(vy));
  

    // Wait for the threads to finish 
    // Wait for thread t1 to finish 
    th1.join(); 
  
    // Wait for thread t2 to finish 
    th2.join(); 
  
    // Wait for thread t3 to finish 
    th3.join(); 

    // Wait for thread t4 to finish 
    th4.join(); 

    // Wait for thread t4 to finish 
    th5.join(); 

    for (int i = 0; i < vy.size(); i++) 
        cout<<"vy: "<<vy[i]<<endl;
  
    return 0; 
} 
