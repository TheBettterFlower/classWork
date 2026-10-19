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
        throw std::invalid_argument("Invalid argument");
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
    size_t len = (length < other.length) ? length : other.length;
    for(size_t i = 0; i < len; i++){
        data[i] += other.data[i];
    }
}

void Array::subArray(const Array& other) {
    size_t len = (length < other.length) ? length : other.length;
    for(size_t i = 0; i < len; i++){
        data[i] -= other.data[i];
    }
}

void Array::print() {
    for (size_t i = 0; i < length; i++) std::cout << data[i] << " ";
    std::cout << "\n";
}

void Array::set(size_t index, int value) {
    if (index >= length) {
        throw std::out_of_range("Out of range");
    }
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Invalid argument");
    }
    data[index] = value;
}

int Array::get(size_t index) {
    if (index >= length) throw std::out_of_range("Out of range");
    return data[index];
}


Array::~Array () {
    delete[] data;
    data = nullptr;
}
