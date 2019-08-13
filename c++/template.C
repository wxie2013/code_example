#include <iostream>

using namespace std;

template<typename A, typename B> 
class test 
{
	public:
		A* a;
		B* b;
	public:
		test() {a = new A; b = new B;}
		void assign(A* in1, B* in2) {
			a = in1;
			b = in2;
		}
		void print(int num)
		{
			for(int i = 0; i<num; i++) {
				cout<<*(a+i)<<" ";
			}
			cout<<endl;
			for(int i = 0; i<num; i++) {
				cout<<*(b+i)<<" ";
			}
			cout<<endl;
		}

};


// A C++ program to demonstrate working of non-type
// parameters to templates in C++.
#include <iostream>
using namespace std;

template <typename T, int max>
int arrMin(T arr[], int n)
{
   int m = max;
   for (int i = 0; i < n; i++)
      if (arr[i] < m)
         m = arr[i];

   return m;
}


//__template for class-type input
//template <typename T>  //.. can use "typename" instead of "class".
template <class T>
void print(T tt)
{
    tt.print(3);
}
//___
int main() 
{
    const int num = 3;
    int in1[num] = {1, 2, 3};
    float in2[num] = {5., 6., 7.};
    test<int, float> t;
    t.assign(in1, in2);
    t.print(num);

    //..
    int arr1[]  = {10, 20, 15, 12};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);

    char arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    // Second template parameter to arrMin must be a constant
    cout << arrMin<int, 10000>(arr1, n1) << endl;
    cout << arrMin<char, 256>(arr2, n2);

    //__
    print(t);
    return 0;
}
