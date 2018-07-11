#include "string"
#include "iostream"
#include "my_smartPoint.h"
using namespace std;
int main()
{

    i_shared_ptr<std::string> first(new std::string("123"));
    i_shared_ptr<std::string> shit(new std::string("456"));
    shit.use_count();
    std::cout << *first << std::endl;
    first=shit;
    std::cout<< *first <<std::endl;
    shit.use_count();


    std::cout<< std::endl;
    std::cout<<std::endl;

    i_shared_ptr<int> sp(new int(10));
    i_shared_ptr<int> sp2(sp);
    i_shared_ptr<int> sp3(new int(20));
    sp2 = sp3;
    sp.use_count();
    sp3.use_count();

    return 0;
}
