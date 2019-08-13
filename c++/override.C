// https://stackoverflow.com/questions/18198314/what-is-the-override-keyword-in-c-used-for
//And as addendum to all answers, FYI: override is not a keyword, but a special kind of identifier! It has meaning only in context of declaring/defining virtual functions, in other contexts it's just an ordinal identifier. For details read 2.11.2 of The Standard.

// kate: hl C++11;
#include <iostream>

struct base
{
    virtual void foo() = 0;
};

struct derived : base
{
    //void foo(int i) override  //.. compiling error since foo is different from the base::foo, thus not an override
    void foo() override
    {
        std::cout << " +++++ this is an override ++++ "<< std::endl;
    }

    void foo(int i) {std::cout<<" ...this is not an override ..."<<std::endl;}
};

int main()
{
    base* override = new derived();
    override->foo();

    derived* tt = new derived();
    tt->foo(10);
    return 0;
}
