#include <iostream>
using namespace std;
class parent
{
    public:
        parent(int mm) {cout<<"mm"<<mm<<endl;}
        ~parent() {cout<<" done1 "<<endl;}
        virtual void print() {cout<<"1______________"<<endl;}
};

class daughter: public parent
{
    public:
        daughter():parent(10) {cout<<"2222222222222222222222222222222"<<endl;}
        ~daughter() {cout<<" done 2"<<endl;}
        void print() {
            parent::print();
            cout<<"2______________"<<endl;
        }
};

void inheritance()
{
    parent *a = new daughter;
    a->print();
    delete a;
}
