#include <iostream> 
#include <thread> 
#include <chrono> 
  
using namespace std; 
  
int main() 
{ 
  for (int i = 1; i <= 5; ++i) 
  { 
      //cout << i << " ";  //.. output 1 2 3 4 5 at once.
      cout << i << " "<<flush; 
      this_thread::sleep_for(chrono::seconds(1));  //print the numbers(1 2 3 4 5) one by one rather than once
  } 
  cout << endl; 
  return 0; 
} 
