#include "../include/DynamicArray.h"
#include <iostream>

int main() {   
    Array a(5);
    a.print();
    a.set(2, 90);
    a.print();
    Array b(a);
    b.print();
    std::cout << b.get(0);
    b.push_back(10);
    b.print();
    a.subArray(b);
    a.print();
    b.addArray(a);
    b.print();
    
    return 0;
}