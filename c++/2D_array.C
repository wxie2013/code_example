#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
using namespace std;

int main()
{
    const auto M = 2;
    const auto N = 2;

    // allocate (no initializatoin)
    auto array = new double[M][N];

    // pollute the memory
    array[0][0] = 2;
    array[1][0] = 3;
    array[0][1] = 4;
    array[1][1] = 5;

    // re-allocate, probably will fetch the same memory block (not portable)
    delete[] array;
    array = new double[M][N];

    // show that memory is not initialized
    for(int r = 0; r < M; r++)
    {
        for(int c = 0; c < N; c++)
            cout << array[r][c] << " ";
        cout << endl;
    }
    cout << endl;

    delete[] array;

    // the proper way to zero-initialize the array
    array = new double[M][N]();

    // show the memory is initialized
    for(int r = 0; r < M; r++)
    {
        for(int c = 0; c < N; c++)
            cout << array[r][c] << " ";
        cout << endl;
    }

    int info;
    cout << abi::__cxa_demangle(typeid(array).name(),0,0,&info) << endl;

    return 0;
}

