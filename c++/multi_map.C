#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    //Multi Map of char and int
    // Initializing with initializer list
    multimap<char, int> mmapOfPos ={
        {'t', 1},
        {'h', 1},
        {'i', 2},
        {'s', 3},
        {'i', 5},
        {'s', 6},
        {'i', 8},
        {'t', 2}
    };
    // Inserting an element in map
    mmapOfPos.insert(pair<char, int>('t', 9));
    // Iterate over the multimap using Iterator
    for (multimap<char, int>::iterator it = mmapOfPos.begin();
            it != mmapOfPos.end(); it++)
        cout << it->first << " :: " << it->second << endl;
    cout << "****************************************" << endl;
    // Iterate over the multimap using range based for loop
    for (pair<char, int> elem : mmapOfPos)
        cout << elem.first << " :: " << elem.second << endl;

    cout << "****************************************" << endl;
    pair <multimap<char,int>::iterator, multimap<char,int>::iterator> ret;
    ret = mmapOfPos.equal_range('t');
    for(multimap<char, int>::iterator it =ret.first; it!=ret.second; ++it)
        cout<<"t: "<<it->second<<endl;

    ret = mmapOfPos.equal_range('h');
    for(multimap<char, int>::iterator it =ret.first; it!=ret.second; ++it)
        cout<<"t: "<<it->second<<endl;

    return 0;
}
