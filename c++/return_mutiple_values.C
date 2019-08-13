#  include <tuple>
# include <iostream>

using namespace std;

tuple < int,int,int,int,int >   cal(int n1, int n2)
{
    return  make_tuple(n1/n2,n1%n2,n1+n2,n1-n2,n1*n2);
}

int main()
{
    int qut,rer,add,sub,mul,a,b;
    cin>>a>>b;
    tie(qut,rer,add,sub,mul)=cal(a,b);
    cout << "quotient= "<<qut<<endl;
    cout << "remainder= "<<rer<<endl;
    cout << "addition= "<<add<<endl;
    cout << "subtraction= "<<sub<<endl;
    cout << "multiplication= "<<mul<<endl;
    return 0;
}


