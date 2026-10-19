#pragma once
#include <iostream>
#include <exception>

class Array {
public:
    
    Array(size_t length); 
    Array(const Array& other);

    void print();
    void set(size_t index, int value);
    int get(size_t index);
    void push_back(int value);
    void addArray(const Array& other);
    void subArray(const Array& other);
    ~Array ();
private:
    int * data;
    size_t length;
};

