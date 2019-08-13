#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Synapse {
  float pre_ID;
  float weight;
  int delay; // in time_step

  bool operator< ( const Synapse &s ) const { return pre_ID > s.pre_ID; } //..used for equal_range and sort
};

vector<Synapse> f()
{
    vector<Synapse> tmp;
    Synapse t;

    for(int i = 0; i<10; i++) {
        t.pre_ID = i;
        t.weight = i;
        t.delay = i;
        tmp.push_back(t);
    }

    for(int i = 0; i<10; i++) {
        t.pre_ID = i+0.7;
        t.weight = i+0.7;
        t.delay = i+0.7;
        tmp.push_back(t);
    }

    for(int i = 0; i<10; i++) {
        t.pre_ID = i;
        t.weight = i;
        t.delay = i;
        tmp.push_back(t);
    }


    return tmp;
};

bool compare_two_synapses(Synapse &s1, Synapse &s2)
{
    return s1.pre_ID <= s2.pre_ID;
}

bool identical_two_synapses(Synapse &s1, Synapse &s2)
{
    return s1.pre_ID == s2.pre_ID;
}

//__
int main()
{
    vector<Synapse> a = f();
    cout<<" ---- before sort ----"<<endl;
    for(int i = 0; i<30; i++) 
        cout<<"i: "<<a[i].pre_ID<<endl;

    //.. now sort
    cout<<" ---- after sort ----"<<endl;
    //sort(a.begin(), a.end(), compare_two_synapses); //.. this is also OK. 
    sort(a.begin(), a.end());
    for(int i = 0; i<30; i++) 
        cout<<"i: "<<a[i].pre_ID<<endl;

    cout<<" --- after remove duplicate ----"<<endl;
    vector<Synapse>::iterator ip = unique(a.begin(), a.end(), identical_two_synapses);
    a.resize(distance(a.begin(), ip));

    cout<<" new size: "<<a.size()<<endl;
    for(int i = 0; i<a.size(); i++) 
        cout<<"i: "<<a[i].pre_ID<<endl;
}
