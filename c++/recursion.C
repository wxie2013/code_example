//If the base case is not reached or not defined, then the stack overflow problem may arise. Let us take an example to understand this.
//int fact(int n)
//{
//    // wrong base case (it may cause
//    // stack overflow).
//    if (n == 100) 
//        return 1;
//
//    else
//        return n*fact(n-1);
//}
//If fact(10) is called, it will call fact(9), fact(8), fact(7) and so on but the number will never reach 100. So, the base case is not reached. If the memory is exhausted by these functions on the stack, it will cause a stack overflow error.
// An example of direct recursion
//void directRecFun()
//{
//    // Some code....
//
//    directRecFun();
//
//    // Some code...
//}
//
//// An example of indirect recursion
//void indirectRecFun1()
//{
//    // Some code...
//
//    indirectRecFun2();
//
//    // Some code...
//}
//void indirectRecFun2()
//{
//    // Some code...
//
//    indirectRecFun1();
//
//    // Some code...
//}


// A C++ program to demonstrate working of 
// recursion 

#include<bits/stdc++.h> 
using namespace std; 
  
void printFun(int test) 
{ 
    if (test < 1) 
        return; 
    else
    { 
        cout << test << " "; 
        printFun(test-1);    // statement 2 
        cout << test << " "; 
        return; 
    } 
} 
  
int main() 
{ 
    int test = 3; 
    printFun(test); 
}

//Output :
//3 2 1 1 2 3


