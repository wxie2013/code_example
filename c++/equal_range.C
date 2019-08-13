#include <algorithm>
#include <vector>
#include <iostream>
 
using namespace std;

struct S
{
    int number;
    char name;
    // note: name is ignored by this comparison operator
    bool operator< ( const S& s ) const { return number < s.number; }
};

int main()
{
    // note: not ordered, only partitioned w.r.t. S defined below
    std::vector<S> vec = { {1,'A'}, {2,'B'}, {2,'C'}, {2,'D'}, {4,'G'}, {3,'F'} };
 
 
    std::pair<std::vector<S>::iterator,std::vector<S>::iterator> p;
 
    for (int i = 0; i<vec.size(); i++) {
        p = std::equal_range(vec.begin(), vec.end(), vec[i]);
        if((p.second-p.first) ==3) {
            int index = p.first - vec.begin();
            cout<<vec[index].name<<" "<<vec[index+1].name<<" "<<vec[index+2].name<<endl;
        }

        i+=2;
    }
}

