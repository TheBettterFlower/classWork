#include "../include/DynamicArray.h"
#include <stdexcept>


Array::Array (size_t len) {
    length = len;     
    data = new int[len]{};   
}

Array::Array(const Array& other) {
    length = other.length;
    data = new int[length]{};
    for (size_t i = 0; i < length; i++) data[i] = other.data[i];
}

void Array::push_back(int value) {
    if (value < -100 || value > 100) {
        std::cerr << "Invalid value";
        return;
    }
    length += 1;
    int * new_data = new int[length];
    for (size_t i = 0; i < length - 1; i++) {
        new_data[i] = data[i];
    }
    new_data[length-1] = value;
    delete[] data;
    data = new_data;
}

void Array::addArray(const Array& other) {
    int len = (length < other.length) ? length : other.length;
    for(int i = 0; i < len; i++){
        data[i] += other.data[i];
    }
}

void Array::subArray(const Array& other) {
    int len = (length < other.length) ? length : other.length;
    for(int i = 0; i < len; i++){
        data[i] -= other.data[i];
    }
}

void Array::print() {
    for (int i = 0; i < length; i++) std::cout << data[i] << " ";
    std::cout << "\n";
}

void Array::set(int index, int value) {
    if (index < 0 || index > length - 1) {
        std::cerr << "Index out of range";
        return;
    }
    if (value < -100 || value > 100) {
        std::cerr << "Invalid value";
        return;
    }
    data[index] = value;
}

int Array::get(int index) {
    if (index < 0 || index > length - 1) return -9999;
    return data[index];
}


Array::~Array () {
    data = nullptr;
    delete[] data;
}
