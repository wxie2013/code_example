//..global namespace 
// https://stackoverflow.com/questions/10269012/global-scope-vs-global-namespace
//The global namespace refers to using ::, and the symbols defined in this namespace are said to have global scope. A symbol, by default, exists in a global namespace, unless it is defined inside a block starts with keyword namespace, or it is a member of a class, or a local variable of a function:

#include <iostream>

//__
int a = 10;

//__
void printf()
{
    std::cout<<" test "<<std::endl;
}

//__
namespace N
{
    int a = 100;

    void f()
    {
         int a = 1000;
         std::cout << a << std::endl;      //prints 1000
         std::cout << N::a << std::endl;   //prints 100
         std::cout << ::a << std::endl;    //prints 10
    }

    namespace m
    {
        float a = 99.9;
        void printf() {
            std::cout<<a<<std::endl;
            using namespace std; //.. use it only in this m scope
            cout<<a<<endl;
        }

        void pf() {
            std::cout<<a<<std::endl;
        }
    }
}

//__
namespace O
{
    std::string a = "hello";
}

//
namespace common
{
    class A
    {
        public:
        A(); 
    };
}

namespace common
{
    A::A()
    {
        int num = 10;
    }
}

//using namespace N::m;  //..calling this leads to ambiguity with the global "int a = 100"
//using namespace O; //..calling this leads to ambiguity with the global "int a = 100"
//using namespace std; //..//..calling this leads to ambiguity with the global "void printf()"

int main()
{
    //.. the following two are the same ..
    std::cout<<::a<<std::endl;
    std::cout<<a<<std::endl;

    //.. the following two are the same ..
    std::cout<<::N::a<<std::endl;
    std::cout<<N::a<<std::endl;

    //..
    N::f();

    //.. nested namespace 
    std::cout<<N::m::a<<std::endl;
    N::m::printf();

    //.. the following two are the same ..
    ::printf();
    printf();

    //...
    std::cout<<O::a<<std::endl;

    //..
    common::A a;

    return 0;
}
