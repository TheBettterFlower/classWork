#include "../include/DynamicArray.h"
#include <iostream>

int main() {   
    Array a(4);
    a.set(0, 1);
    a.set(1, 2);
    a.set(2, 3);
    a.set(3, 4);
    a.print();
    Array b(a);
    b.push_back(10);
    b.print();
    b.addArray(a);
    b.print();
    

    return 0;
}