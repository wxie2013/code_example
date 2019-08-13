// equal_range example
// equal_range example
#include <iostream>     // std::cout
#include <algorithm>    // std::equal_range, std::sort
#include <vector>       // std::vector
#include <utility>


int main () {
  int myints[] = {10,20,30,30,20,10,10,20};
  std::vector<int> v(myints,myints+8);                         // 10 20 30 30 20 10 10 20
  std::pair<std::vector<int>::iterator,std::vector<int>::iterator> bounds;

  // using default comparison:
  std::sort (v.begin(), v.end());                              // 10 10 10 20 20 20 30 30
  for(int i = 0; i<v.size(); i++) {
      std::cout<<v[i]<<std::endl;
  }
  bounds=std::equal_range (v.begin(), v.end(), 20);            //          ^        ^

  std::cout << "bounds at positions " << (bounds.first - v.begin());
  std::cout << " and " << (bounds.second - v.begin()) << '\n';

  //... try pairs .....
  std::vector<std::pair<int, int>> test_pair;
  test_pair.push_back(std::make_pair(1, 1));
  test_pair.push_back(std::make_pair(10, 1));
  test_pair.push_back(std::make_pair(1, 2));
  test_pair.push_back(std::make_pair(1, 1));
  test_pair.push_back(std::make_pair(3, 2));
  test_pair.push_back(std::make_pair(2, 3));
  test_pair.push_back(std::make_pair(2, 2));
  test_pair.push_back(std::make_pair(1, 10));
  test_pair.push_back(std::make_pair(1, 12));
  test_pair.push_back(std::make_pair(1, 1));
  test_pair.push_back(std::make_pair(1, 2));
  test_pair.push_back(std::make_pair(2, 2));

  std::cout<<" ... before sort ...."<<std::endl;
  for(int i = 0; i<test_pair.size(); i++) {
      std::cout<<test_pair[i].first<<", "<<test_pair[i].second<<std::endl;
  }

  std::sort (test_pair.begin(), test_pair.end());  

  std::cout<<" ... after sort ...."<<std::endl;
  for(int i = 0; i<test_pair.size(); i++) {
      std::cout<<test_pair[i].first<<", "<<test_pair[i].second<<std::endl;
  }

  std::pair<std::vector<std::pair<int, int>>::iterator,std::vector<std::pair<int, int>>::iterator> range;
  range = std::equal_range(test_pair.begin(), test_pair.end(), std::make_pair(2,2));
  std::cout << "bounds at positions " << (range.first - test_pair.begin());
  std::cout << " and " << (range.second - test_pair.begin()) << '\n';


  return 0;
}
