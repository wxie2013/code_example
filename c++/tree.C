#include <iostream>
#include <vector>

using namespace std;
class PG
{
    public:
        int id;
        vector<PG> child;
    public:
        PG():id{0} {;}
        //
        void AddChild(int id) {
            PG tmp;
            tmp.id = id;
            child.push_back(tmp);
        }
        //
        int get_N_children() {return child.size();}
};

int main()
{
    PG a; 
    a.AddChild(1);
    a.AddChild(2);
    a.AddChild(3);

    for(int i = 0; i<a.get_N_children(); i++) {
        a.child[i].AddChild(10+i);
    }

    cout<<"1st: "<<a.child.size()<<" child"<<endl;
    for(int i = 0; i<a.child.size(); i++)  {
        cout<<"1st: "<<a.child[i].id<<endl;
        for(int m = 0; m<a.child[i].child.size(); m++) {
            cout<<"2nd: "<<a.child[i].child[m].id<<endl;
        }
    }
}
