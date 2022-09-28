#include <iostream>
#define get_name(name) #name

using namespace std;
int main() {
  int aa = 10;
  string bb = get_name(aa);
  if(bb=="aa")
    cout<<bb<<endl;
  else
    cout<<"!!!! no such name !!!"<<endl;

  return 0;
}
