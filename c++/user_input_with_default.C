#include <iostream>
using namespace std;
void assign(auto & c)
{
    int i = 0;
    cout << "Enter a num: \n";

    cin.ignore();  //..without this, it will go all the way to the end of a loop without user input

    if (std::cin.peek() == '\n') { //check if next character is newline
        cout<<" .. using default value: "<<endl;
    } else if (cin >> i) {
        c = c + i;
    } else {
        cout<<" ... invalid inputs, need to be integer ..."<<endl; //error handling
    }
}

int main()
{
    int c=0;
    do
    {
        assign(c);

    } while (c < 15);

    cout << "The sum of the numbers are: " << c << endl;


    system("pause");
    return (0);
}

