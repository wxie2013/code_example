#include <iostream>
double B1(int x)    // sample function that we call
{
    return x*42.0;
}

void B2(int x)
{
    std::cout<<"X: "<<x<<std::endl;
}
void B3(double x)
{
    std::cout<<"X: "<<x<<std::endl;
}

//.. template to use a function as a input
template<typename D, typename T> 
void A(D (*f)(T), T n)
{
    //for (int i = 0; i < 25; ++i)
    //    std::cout << f(i) << '\n';
    f(n);

}

int main()
{
    A(B1, 0);
    A(B2, 10);
    A(B3, 10.1);
}

