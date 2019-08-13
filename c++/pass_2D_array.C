#include <iostream>
using namespace std;
const int dim = 5;

void print(auto array)
{
    for(int i = 0; i<dim; i++) 
        for(int j = 0; j<dim; j++)
            cout<<"i: "<<i<<" j: "<<j<<" "<<array[i][j]<<endl;
}


int main()
{
    auto array = new float[dim][dim]();
    /*
    for(int i = 0; i<dim; i++) 
        for(int j = 0; j<dim; j++)
            array[i][j] = i*j;
            */

    print(array);

    delete[] array;

    return 0;
}

