//Use shared_ptr if you want to share ownership of resource . Many shared_ptr can point to single resource. shared_ptr maintains reference count for this propose. 
//Use unique_ptr when you want to have single ownership(Exclusive) of resource. Only one unique_ptr can point to one resource. Since there can be one unique_ptr for single resource its not possible to copy one unique_ptr to another.

#include<iostream>
#include<memory>
using namespace std;

class A
{
public:
    void show()
    {
        cout<<"A::show()"<<endl;
    }
};

int main()
{
    //.. shared pointer ..
    A* ptr = new A;
    //.. note: shared_ptr can not be initialized with "=" to avoid accident like: std::shared_ptr<A> ptr = a;
    //std::shared_ptr<A> ptr2 = a; //second ptr holding a... UB
    //shared_ptr<A> p1 = ptr; //.. wrong since this is the place where the shared pointer is initialized
    shared_ptr<A> p1(ptr)  ;
    cout << p1.get() << endl;
    p1->show();
    shared_ptr<A> p2 = p1;  //.. this is OK since it's already initialized 
    //shared_ptr<A> p2 (p1); //.. this is also OK.
    p2->show();
    cout << p1.get() << endl;
    cout << p2.get() << endl;

    // Returns the number of shared_ptr objects
    //referring to the same managed object.
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;

    // Relinquishes ownership of p1 on the object
    //and pointer becomes NULL
    p1.reset();
    cout << p1.get() << endl;
    cout << p2.use_count() << endl;
    cout << p2.get() << endl;

    //.. unique pointer 
    cout<<" --- now unique pointer ---"<<endl;
    unique_ptr<A> pp1 (new A);
    pp1 -> show();

    // returns the memory address of p1
    cout << pp1.get() << endl;

    // transfers ownership to p2
    unique_ptr<A> pp2 = move(pp1);
    pp2 -> show();
    cout << pp1.get() << endl;
    cout << pp2.get() << endl;

    // transfers ownership to p3
    unique_ptr<A> pp3 = move (pp2);
    pp3->show();
    cout << pp1.get() << endl;
    cout << pp2.get() << endl;
    cout << pp3.get() << endl;


    return 0;
}


