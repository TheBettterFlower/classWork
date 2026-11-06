#pragma once
#include <iostream>
#include <exception>
#include <typeinfo>
#include <type_traits>
#include <cmath>
template <typename T>
class Array {
private:
    T* data;
    size_t length;
    static void checkv(const T& value) {
        if constexpr (std::is_integral_v<T>)  if (value < -100 || value > 100) throw std::invalid_argument("Invalid argument");
    }
public:
    explicit Array(size_t len) {
        length = len;
        data = new T[length]{};
    }
    Array(const Array& other) {
        length = other.length;
        if (length > 0) {
            data = new T[length]{};
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
    T get(size_t index) {
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
        } else {
            size_t len = (length < other.length) ? length : other.length;
            for(size_t i = 0; i < len; i++){
                data[i] += other.data[i];
            }
        }
    }
    
    void subArray(const Array& other) {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            size_t len = (length < other.length) ? length : other.length;
            for(size_t i = 0; i < len; i++){
                data[i] -= other.data[i];
            }
        }
    }

    class ElementProxy {
    private:
        Array* array;
        size_t index;
    public:
        ElementProxy(Array* array, size_t index) : array(array), index(index) {}

        ElementProxy& operator=(const T& value) {
            array->set(index, value);
            return *this;
        }

        ElementProxy& operator=(const ElementProxy& other) {
            array->set(index, other.operator const T&());
            return *this;
        }

        operator const T&() const {
            return array->data[index];
        }
    };

    ElementProxy operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Out of range");
        return ElementProxy(this, index);
    }

    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Out of range");
        return data[index];
    }

    bool operator==(const Array& other) const {
        if (length != other.length) return false;
        for (size_t i = 0; i < length; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    Array& operator+=(const Array& other) {
        addArray(other);
        return *this;
    }

    Array& operator-=(const Array& other) {
        subArray(other);
        return *this;
    }

    Array& operator+=(const T& scalar) {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            for (size_t i = 0; i < length; i++) {
                set(i, data[i] + scalar);
            }
            return *this;
        }
    }

    Array& operator-=(const T& scalar) {
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            for (size_t i = 0; i < length; i++) {
                set(i, data[i] - scalar);
            }
            return *this;
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        delete[] data;length = other.length;
        if (length > 0) {
            data = new T[length]{};
            for (size_t i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        return *this;
    }

    Array(Array&& other) noexcept {
    data = other.data;
    length = other.length;

    other.data = nullptr;
    other.length = 0;
    }

    Array& operator=(Array&& other) noexcept {
    if (this == &other) return *this;

    delete[] data;

    data = other.data;
    length = other.length;

    other.data = nullptr;
    other.length = 0;

    return *this;
    }

    T* begin() noexcept { return data; }
    T* end() noexcept { return data + length; }

    const T* begin() const noexcept { return data; }
    const T* end() const noexcept { return data + length; }

    friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
        os << "Array: [";
        for (size_t i = 0; i < arr.length; i++) {
            os << arr.data[i];
            if (i + 1 < arr.length) os << "; ";
        }
        os << "]";
        return os;
    }
        
    double euclidDist(const Array& other) const { 
        if constexpr (!std::is_arithmetic_v<T>) {
            throw std::bad_typeid();
        } else {
            if (length != other.length) {
                throw std::invalid_argument("Arrays must be of the same size");
            }
            double dist = 0.0;
            for (size_t i = 0; i < length; i++) {
                double diff = static_cast<double>(data[i] - other.data[i]);
                dist += diff * diff;
            }
            return std::sqrt(dist);
        }
    }

    ~Array () {
        delete[] data;
        data = nullptr;
    }
};
