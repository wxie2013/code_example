#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream weightfile;
    weightfile.open("oo.dat");
    while( weightfile.good() )
    {
        string fileline;
        getline( weightfile, fileline);
        cout<<fileline<<endl;
        if (weightfile.eof()) {
            weightfile.close();
            break;
        }
    }

    return 0;
}

