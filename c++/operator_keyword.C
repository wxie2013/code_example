#include<iostream>
using namespace std;

class Complex {
private:
    int real, imag;
public:
    Complex(int r = 0, int i =0)  {real = r;   imag = i;}

    // This is automatically called when '+' is used with
    // between two Complex objects
    Complex operator + (Complex const &obj) {
         this->real += obj.real;
         this->imag += obj.imag;

         return *this;
    }
    void print() { cout << real << " + i" << imag << endl; }
};

//__
class Fraction
{
       int num, den;
    public:
       Fraction(int n,  int d) { num = n; den = d; }

    // conversion operator: return float value of fraction
    operator float() const {
        return float(num) / float(den);
    }
};

//__
class Test
{
       int *ptr;
   public:
       Test (int i = 0)      { ptr = new int(i); }
       void setValue (int i) { *ptr = i; }
       void print()          { cout << *ptr << endl; }
       Test & operator = (const Test &t);
};


Test & Test::operator = (const Test &t)
{
   // Check for self assignment
   if(this != &t)
     *ptr = *(t.ptr);  //.. assign value only 

   return *this;
}

//__
//Following are some useful facts about overloading of [].
//1) Overloading of [] may be useful when we want to check for index out of bound.
//2) We must return by reference in function because an expression like “arr[i]” can be used an lvalue.
// A class to represent an integer array
class Array
{
  private:
    int *ptr;
    int size;
  public:
    Array(int *, int);

    // Overloading [] operator to access elements in array style
    int &operator[] (int);

    // Utility function to print contents
    void print() const;
};


// Implementation of [] operator.  This function must return a
// refernce as array element can be put on left side
int &Array::operator[](int index)
{
    if (index >= size)
    {
        cout << "Array index out of bound, exiting"<<endl;
        exit(0);
    }
    return ptr[index];
}

// constructor for array class
Array::Array(int *p = NULL, int s = 0)
{
    size = s;
    ptr = NULL;
    if (s != 0)
    {
        ptr = new int[s];
        for (int i = 0; i < s; i++)
            ptr[i] = p[i];
    }
}

void Array::print() const
{
    for(int i = 0; i < size; i++)
        cout<<ptr[i]<<" ";
    cout<<endl;
}


//__
int main()
{
    Complex c1(10, 5), c2(2, 4);
    Complex c3 = c1 + c2; // An example call to "operator+"
    c3.print();

    //..
    Fraction f(2, 5);
    float val = f;
    cout << val<<endl;

    //..
    Test t1(5);
    Test t2;
    t2 = t1;
    t1.setValue(10);
    t2.print();

    //__
    int a[] = {1, 2, 4, 5};
    Array arr1(a, 4);
    arr1[2] = 6;
    arr1.print();
    arr1[8] = 6;

    return 0;
}


