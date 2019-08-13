#include <iostream>

using namespace std;
const int ii = 100;

//Static variables when used inside function are initialized only once, and then they hold there value even through function calls.  These static variables are stored on static storage area , not in stack.
void counter()
{
    static int static_count=0;
    int non_static_count = 0;
    cout << static_count++<<" "<<non_static_count++<<endl;
}

//Static keyword works in the same way for class objects too. Objects declared static are allocated storage in static storage area, and have scope till the end of program.  Static objects are also initialized using constructors like other normal objects. Assignment to zero, on using static keyword is only for primitive datatypes, not for user defined datatypes.
class Abc
{
    int i;

    public:
    Abc()
    {
        i=0;
        cout << "constructor"<<endl;
    }
    ~Abc()
    {
        cout << "destructor"<<endl;
    }
};

void f1()
{
    static Abc obj;
}

void f2()
{
    Abc obj;
}

//Static data members of class are those members which are shared by all the objects. Static data member has a single piece of storage, and is not available as separate copy with each object, like other non-static data members.  Static member variables (data members) are not initialied using constructor, because these are not dependent on object initialization.  Also, it must be initialized explicitly, always outside the class. If not initialized, Linker will give error.
class X
{
    private:
      static int i;
    public:
      X() {};
      void print() {cout<<i<<endl;}
    
};

int X::i=1;  //it must be initialized explicitly,

//Static Member Functions work for the class as whole rather than for a particular object of a class.  It can be called using an object and the direct member access . operator. But, its more typical to call a static member function by itself, using class name and scope resolution :: operator. These functions cannot access ordinary data members and member functions, but only static data members and static member functions.  It doesn't have any "this" keyword which is the reason it cannot access ordinary members

class Y
{
    private:
       static int i;
       int p;

    public:
       Y() {p = 100;}
       static void print()
       {
           cout<<i<<endl;
           //cout<<p<<endl; //.. compile error since static function can not access non-static members
           cout<<ii<<endl;
       }
};
int Y::i = 10;

//__
int main()
{
    for(int i=0;i<5;i++)
    {
        counter();
    }

   //..
   f1(); //.. destructor called after "...END ...."
   f2(); //.. destructor called before "....END ..." after f2() is done being called.

   //..
   X obj1;
   X obj2;
   obj1.print();
   obj2.print();

   //..
   Y t1;
   Y::print();
   t1.print(); //.. same as Y::print() for static function
   cout<<" ..END .."<<endl;
}


