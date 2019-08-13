#include <iostream>

using namespace std;

#define defined_class(BACKEND, TYPE) \
     class TYPE {                                                         \
        private:                                                          \
          BACKEND tt;                                                     \
        public:                                                           \
          TYPE(BACKEND in) {                                              \
            tt = in;                                                      \
            cout<<tt<<endl;                                               \
          }                                                               \
     }                                                                    



#define defined_function() \
  void t1() {std::cout<<"t1"<<std::endl;}\
  void t2() {std::cout<<"t2"<<std::endl;}\
  void t3() {std::cout<<"t3"<<std::endl;}

class tt
{
    public: 
        tt() {;}
        defined_function(); //.. this is equal to write down t1(), t2(), t3(), explicitly
};

//.. defined class 
defined_class(int, test_define_class);

int main()
{
    tt test;

    test.t1();
    test.t2();
    test.t3();

    //.. this is the one defined through template
    test_define_class check(10);


    return 0;
}
