#include <iostream>
class  B {
 public:
    B() {;}
    virtual void f(int) { std::cout << "B::f\n"; }
    void g(char)        { std::cout << "B::g\n"; }
    void h(int)         { std::cout << "B::h\n"; }
    void k(int)         {std::cout<<" B::k"<<std::endl;}
 protected:
    int m; // B::m is protected
    typedef int value_type;
};

class  D : public B {
  public:
    using B::m; // D::m is public
    using B::value_type; // D::value_type is public

    using B::f;
    void f(int) { std::cout << "D::f\n"; } // D::f(int) overrides B::f(int)
    using B::g;
    void g(int) { std::cout << "D::g\n"; } // both g(int) and g(char) are visible
                                           // as members of D
    using B::h;
    void h(int) { std::cout << "D::h\n"; } // D::h(int) hides B::h(int)

    using B::k;  //.. using B::k function 

};

int main()
{
    D d;
    B& b = d;

//    b.m = 2; // error, B::m is protected
    d.m = 1; // protected B::m is accessible as public D::m
    b.f(1); // calls derived f()
    d.f(1); // calls derived f()
    d.g(1); // calls derived g(int)
    d.g('a'); // calls base g(char)
    b.h(1); // calls base h()
    d.h(1); // calls derived h()

    b.k(1);
    d.k(1);

    using std::cout;
    cout<<" .... done ...."<<std::endl; 

    using namespace std;
    cout<<" ... OK. finally done ...."<<endl;
}

