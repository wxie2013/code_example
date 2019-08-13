#include <iostream>

using namespace std;
void test(int **a, int **b)
{
   cout<<"1__"<<**a<< " "<<**b<<endl;
   *a = *b;
}

int main()
{
    int a = 2;
    int b = 2;

    int *pa = &a;
    int *pb = &b;

    cout<<pa<<" "<<pb<<endl;

    test(&pa, &pb);

    cout<<pa<<" "<<pb<<endl;
    cout<<a<<" "<<b<<endl;
    cout<<*pa<<" "<<*pb<<endl;
    return 0;
}

