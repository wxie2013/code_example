#include <iostream>
#include <cstring>
#define get_name(name) #name

using namespace std;
int main() {
  int aa = 10;
  string bb = get_name(aa);
  const char *cc = get_name(aa);
  if(bb=="aa")
    cout<<"bb: "<<bb<<endl;
  else
    cout<<"!!!! no such name !!!"<<endl;

  if(strcmp(cc, "aa")==0)
    cout<<"cc: "<<bb<<endl;
  return 0;
}
