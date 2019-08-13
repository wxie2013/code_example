#include <iostream>
#include <fstream>

#include <sys/stat.h>


using namespace std;

int main()
{
    float  value1, value2, value3;
    string ts;
    ifstream fin;
    fin.open ("oo.dat", ifstream::in);
    if (!fin.good()) {
        cout<<" no oo.dat files "<<endl;
    }
    else {
        fin >> value1 >> value2 >> value3 >> ts;
        cout<<value1<<" "<<value2<<" "<<value3<<" "<<ts<<endl;
    }


    string a = to_string(value1) + to_string(value2) + to_string(value3) + ts;
    cout<<a<<endl;

    string dir_name = "tt";
    if(mkdir(dir_name.c_str(), S_IRUSR | S_IWUSR | S_IXUSR)) {
        cout<<" directory exit, can not create "<<endl;
    }
    ifstream fout;
    fout.open("out.txt", ios::out | ios::binary);
    return 0;
}

