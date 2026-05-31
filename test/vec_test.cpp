#include <iostream>
#include <ds/vector.hpp>

int main(){

    dsa::Vector<int> v;

    v.push_back(10);
    v.push_back(22);

    std::cout << v.size() << v[0] << v[1] ;
}

