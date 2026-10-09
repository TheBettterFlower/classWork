#pragma once
#include <iostream>

class Array {
public:
    
    Array(size_t length); 
    Array(const Array& other);

    void print();
    void set(int index, int value);
    int get(int index);
    void push_back(int value);
    void addArray(const Array& other);
    void subArray(const Array& other);
    ~Array ();
private:
    int * data;
    size_t length;
};

