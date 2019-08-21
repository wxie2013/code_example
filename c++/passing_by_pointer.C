//https://stackoverflow.com/questions/57576936/change-of-result-after-passing-by-pointer
//Yes, the pointer parameter itself is passed by value, any modification on the pointer has nothing to do with the pointer argument. That's why the value doesn't change for the 1st code sample.
//
//But it's different for the 2nd one; you're modifying the object pointed by the pointer. Both the parameter and the argument point to the same object, then the object gets changed.


#include <vector>
#include <iostream>
using namespace std;
//
class A
{
        public:
                int b;
                A() {;}
};

//
void  test1(A *a)
{
    A t;
    t.b = 200;
    cout<<"0__"<<&a<<endl;
    a = &t;  //.. now the pointer a point to the object t and not the original input anymore. modification don't affect the original inputs
    cout<<"1__"<<&a<<endl;
    cout<<&a<<endl;
}

//
void  test2(A *a)
{
    cout<<"2__"<<&a<<endl;
    a->b = 200;  //.. the pointer still points to the original inputs. Modification leads to changes of original inputs
    cout<<"3__"<<&a<<endl;
}

//
void test3(A &a)
{
    cout<<&a<<endl;
}

//
int main()
{
    A a;
    a.b = 10;

    cout<<&a<<endl;
    test1(&a);
    cout<<"a.b value is NOT changed"<<endl;
    cout<<a.b<<endl;

    test2(&a);
    cout<<"a.b value is changed"<<endl;
    cout<<a.b<<endl;

    test3(a);
}
