#include "vector.h"
#include <iostream>
#include <vector>

int main()
{
    new_vector<int> s(5);
    for (int i=0; i<s.size();i++)
        std::cout<<s[i];
    std::cout<<'\n';
    new_vector<int> l {1,2,3,4,5,6,7};
    for (int i=0; i<s.size();i++)
        std::cout<<l[i];
    std::cout<<'\n';
    s = l;
    for (int i=0; i<7;i++)
        std::cout<<s[i];
    std::cout<<'\n';
    std::cout<<s.size()<<'\n';
    s.resize(3);
    std::cout<<s.size()<<'\n';
    s.push_back(7);
    for (int i=0; i<s.size();i++)
        std::cout<<s[i];
    std::cout<<'\n';
    s.reserve(10);
    std::cout<<s.capacity()<<'\n'<<s.size();

    return 0;

}
