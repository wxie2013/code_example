#include <vector>
#include <iostream>
using namespace std;
//

class A
{
    public:
        vector<int *> a;
        //
        A(int in) 
        {
            for(int i = 0; i<10; i++)
                a.push_back(new int(in));
        }

        //
        ~A() {clear();}

        //
        void clear() 
        {
            for(int i = 0; i<a.size(); i++) 
                delete a[i];

            a.clear();
        };

        void print()
        {
            for(int i = 0; i<10; i++) 
                cout<<*a[i]<<endl;
        }

        //

};

template<typename A>
void update(A *&org, A *t) //.. reference to a pointer
{
    delete org;
    org = t;
}

int main()
{
    A *a0 = new A(0);
    A *a1 = new A(10);

    cout<<a0<<" "<<a1<<endl;

    update(a0, a1);

    cout<<a0<<" "<<a1<<endl;
    a0->print();
    cout<<"-----------------"<<endl;
    a1->print();
}
