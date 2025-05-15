#include <iostream>
using namespace std;
class parent
{
    private: 
    public:
        float nn;
        parent() {;}
        parent(int mm) {nn = mm*10; cout<<"mm: "<<mm<<" nn: "<<nn<<endl;}
        ~parent() {cout<<" done1 "<<endl;}
        virtual void print() {cout<<"1______________"<<endl;}
        float get_nn() {return nn;}
};

class daughter: public parent
{
    public:
        daughter(parent& b): parent(b) {;}
        ~daughter() {cout<<" done 2"<<endl;}
        void print() {
            parent::print();
            cout<<"2______________"<<endl;
        }
};

int main()
{
    parent *a = new parent(10);
    cout<<a->get_nn()<<endl;
    daughter d(*a);

    cout<<d.get_nn()<<endl;
}

