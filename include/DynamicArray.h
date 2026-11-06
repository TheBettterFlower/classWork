#pragma once
#include <iostream>
#include <exception>
#include <typeinfo>
#include <cmath>
template <typename T>
class Array {
private:
    int* data;
    size_t length;
    static void checkv(const T& value) {
        if constexpr (std::is_integer_v(value))  if (-100 < value && value > 100) throw std::invalid_argument("Invalid argument");
    }
public:
    explicit Array(size_t len) {
        length = len;
        data = new int[length]{};
    }
    Array(const Array& other) {
        length = other.length;
        if (length > 0) {
            data = new int[length]{};
            for (size_t i = 0; i < length; i++) data[i] = other.data[i];
        } else {
            data = nullptr;
        }
    }
    void print() {
        for (size_t i = 0; i < length; i++) std::cout << data[i] << " ";
        std::cout << "\n";
    }  
    void set(size_t index, T value) {
        if (index >= length) {
            throw std::out_of_range("Out of range");
        }
        checkv(value);
        data[index] = value;
    }
    int get(size_t index) {
        if (index >= length) throw std::out_of_range("Out of range");
        return data[index];
    }
    void push_back(T value) {
        checkv(value);
        length += 1;
        T * new_data = new T[length];
        for (size_t i = 0; i < length - 1; i++) {
            new_data[i] = data[i];
        }
        new_data[length-1] = value;
        delete[] data;
        data = new_data;
    }

    void addArray(const Array& other) {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        }
        size_t len = (length < other.length) ? length : other.length;
        for(size_t i = 0; i < len; i++){
            data[i] += other.data[i];
        }
    }
    
    void subArray(const Array& other) {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        }
        size_t len = (length < other.length) ? length : other.length;
        for(size_t i = 0; i < len; i++){
            data[i] -= other.data[i];
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
        os << "Array: [";
        for (int i = 0; i < arr.size(); i++) {
            os << arr.data[i];
            if (i < arr.size() - 1) os << ";";
        }
        os << "]"
    }

    double euclidDist(const Array& other) const { 
        if constexpr (!std::is_arithmetic_v<T>) throw std::bad_typeid();
        if (length != other.length) throw std::invalid_argument("Invalid argiument");
        double dist = 0.0;
        for (int i = 0; i < length; i++) {
            dist += static_cast<double>(data[i] - other.data[i]) * static_cast<double>(data[i] - other.data[i]); 
        }
        dist = std::sqrt(dist);
        return dist;
    }



    Array::~Array () {
        delete[] data;
        data = nullptr;
    }
};
