#include <iostream>
#include <map>
#include <string>
#include <iterator>

using namespace std;

std::map<std::string, int>::iterator serachByValue(std::map<std::string, int> & mapOfWords, int val)
{
    // Iterate through all elements in std::map and search for the passed element
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        if(it->second == val)
        return it;
        it++;
    }
}

int main()
{
    std::map<std::string, int> mapOfWords;

    // Inserting data in std::map
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords["sun"] = 3;
    // Will replace the value of already added key i.e. earth
    mapOfWords["earth"] = 4;
    // Iterate through all elements in std::map
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
    // Check if insertion is successful or not
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
    }
    // Searching element in std::map by key.
    if(mapOfWords.find("sun") != mapOfWords.end()) {
        std::cout<<"word 'sun' found"<<std::endl;
        std::cout<<" value: "<<mapOfWords.find("sun")->second<<std::endl;
    }
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;

    //std::map<std::string, int>::iterator it3 = mapOfWords.find("sun");
    auto it3 = mapOfWords.find("sun");
    if (it3 != mapOfWords.end()) 
        std::cout<<" !!!!!"<<it3->second<<std::endl;
    //search data by value 
    std::map<std::string, int>::iterator it0 = serachByValue(mapOfWords, 3);
    if(it0 != mapOfWords.end())
        std::cout<<it0->first<<" :: "<<it0->second<<std::endl;

    //delete data 
    // Erasing By iterator
    std::map<std::string, int>::iterator it1 = mapOfWords.find("moon");
    mapOfWords.erase(it1);
    // Erasing By Key
    mapOfWords.erase("earth");

    //list the remaining elements
    cout<<" remaining elements"<<endl;
    std::map<std::string, int>::iterator it2 = mapOfWords.begin();
    while(it2 != mapOfWords.end()) {
        cout<<it2->first<<" :: "<<it2->second<<endl;
        it2++;
    }

    cout<<mapOfWords["sun"]<<endl;

    mapOfWords.insert(std::make_pair("t1", 1));
    mapOfWords.insert(std::make_pair("t2", 2));
    mapOfWords.insert(std::make_pair("t3", 3));
    mapOfWords.insert(std::make_pair("t4", 4));
    mapOfWords.insert(std::make_pair("t5", 5));
    mapOfWords.insert(std::make_pair("t6", 6));
    int tot = 0;
    for(std::map<std::string, int>::iterator it3 = mapOfWords.begin(); it3 != mapOfWords.end(); it3++) {

        std::cout<<tot<<": "<<it3->first<<" "<<it3->second<<std::endl;
        tot++;
    }

    std::map<std::string, int>::iterator it4 = mapOfWords.begin();

    //it4 += 6; //.. doesn't work
    //it4 = std::advance(it4, 6); // this onew works
    it4 = std::next(it4, 6);
    std::cout<<it4->first<<" "<<it4->second<<std::endl;

    auto it5 = mapOfWords.find("t5");
    std::cout<<"5__"<<it5->second<<std::endl;
    std::cout<<mapOfWords["t5"]<<std::endl;



    return 0;
}
