#include "../include/DynamicArray.h"
#include <iostream>

int main() {   
    Array a(5);
    a.print();
    a.set(2, 90);
    a.print();
    try {
        a.get(10);
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << "\n";
    }
    try {
        Array c(-1);
    } catch (const std::bad_alloc& e) {
        std::cerr << e.what() << "\n";
    }

    Array b(a);
    b.print();
    std::cout << b.get(0);
    try {
        b.push_back(200);    
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }   
    b.print();
    a.subArray(b);
    a.print();
    b.addArray(a);
    b.print();
    
    return 0;
}