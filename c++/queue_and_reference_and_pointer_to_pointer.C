//.. similar as recursion_3.C except the node using object instead of pointer to avoid memory issue of the child
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
void test(int *&t) 
{//. no recursion. print out easy to understand 
    queue<int **> q;  // Create a queue to the address of pointer
    q.push(&t); // store the address of the pointer t

    int **p = q.front();  //.. now (*p) is the original pointer
    q.pop();

    int num = 10;
    *p = &num;
} 
void test2(int *&t) 
{//. no recursion. print out easy to understand 
    int num = 10;
    t = &num;
} 

int main()
{
    int num = 2;
    int *p = &num;

    test(p);
    cout<<*p<<endl;

    test2(p);
    cout<<*p<<endl;
}
