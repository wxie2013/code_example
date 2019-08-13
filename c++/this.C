//Following are the situations where ‘this’ pointer is used:

//1) When local variable’s name is same as member’s name
#include<iostream> 
using namespace std; 
  
/* local variable is same as a member's name */
class Test1 
{ 
private: 
   int x; 
public: 
   void setX (int x) 
   { 
       // The 'this' pointer is used to retrieve the object's x 
       // hidden by the local variable 'x' 
       this->x = x; 
   } 
   void print() { cout << "x = " << x << endl; } 
}; 

//2) To return reference to the calling object
//When a reference to a local object is returned, the returned reference can be used to chain function calls on a single object.
class Test2
{
private:
  int x;
  int y;
public:
  Test2(int x = 0, int y = 0) { this->x = x; this->y = y; }
  Test2 &setX(int a) { x = a; return *this; }
  Test2 &setY(int b) { y = b; return *this; }
  void print() { cout << "x = " << x << " y = " << y << endl; }
};

class Test3
{
private:
  int x;
  int y;
public:
  Test3(int x = 0, int y = 0) { this->x = x; this->y = y; }
  void fun1() { cout << "Inside fun1()"<<endl; }
  void fun2() { cout << "Inside fun2()"<<endl; this->fun1(); }
};

class Test4
{
private:
  int x;
  int y;
public:
  Test4(int x = 0, int y = 0) { this->x = x; this->y = y; }
  void setX(int a) { x = a; }
  void setY(int b) { y = b; }
  void destroy()  { delete this; }
  void print() { cout << "x = " << x << " y = " << y << endl; }
};


//__
int main() 
{ 
   Test1 obj; 
   int x = 20; 
   obj.setX(x); 
   obj.print(); 

   //..
   Test2 obj2(5, 5);
   obj2.print();
   obj2.setX(10).setY(20);
   obj2.print();

   //..
   Test3 obj3;
   obj3.fun2();

   //..
   Test4 obj4;
   obj4.destroy(); //.. deleted
   obj4.print(); //.. since obj4 is deleted, it will code dump

   return 0; 
} 

