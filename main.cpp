#include "src/CorePhysics.hpp"
#include <iostream>
int main(){
    constexpr vec2 a ={0,2};
    std::cout<<a<<'\n';
    a.normalize();
    std::cout<<"Normalized: "<<a<<'\n';

    
}