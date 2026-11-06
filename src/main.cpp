#include "../include/DynamicArray.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "Проверка числового массива (int) и оператора <<\n";
    Array<int> arr1(3);
    arr1.set(0, 10);
    arr1.set(1, 20);
    arr1.set(2, 30);
    std::cout << "arr1: " << arr1 << "\n";

    try {
        arr1.get(10);
    } catch (const std::out_of_range& e) {
        std::cerr << "Поймали out_of_range: " << e.what() << "\n";
    }

    try {
        arr1.set(0, 150);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Поймали invalid_argument: " << e.what() << "\n";
    }

    try {
        Array<int> huge(-1);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Поймали bad_alloc: " << e.what() << "\n";
    }

    std::cout << "\nВычисление евклидова расстояния\n";
    Array<double> v1(2);
    v1.set(0, 0.0);
    v1.set(1, 0.0);

    Array<double> v2(2);
    v2.set(0, 3.0);
    v2.set(1, 4.0);

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";
    std::cout << "Расстояние: " << v1.euclidDist(v2) << " (ожидается 5)\n";

    try {
        Array<double> v3(3);
        v1.euclidDist(v3);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Поймали invalid_argument (разные размеры): " << e.what() << "\n";
    }

    std::cout << "\nПроверка нечислового типа\n";
    Array<std::string> words(2);
    words.set(0, "Hello");
    words.set(1, "World");
    std::cout << "words: " << words << "\n";

    words.push_back("C++");
    std::cout << "words после push_back: " << words << "\n";

    try {
        Array<std::string> words2(words);
        words.euclidDist(words2);
    } catch (const std::bad_typeid& e) {
        std::cerr << "Поймали bad_typeid для строк: " << e.what() << "\n";
    }

    std::cout << "\nОператоры\n";
    arr1[0] = 50;
    std::cout << "arr1[0] = 50: " << arr1 << "\n";
    std::cout << "arr1[0]: " << arr1[0] << "\n";

    try {
        arr1[10] = 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Поймали out_of_range через operator[]: " << e.what() << "\n";
    }

    try {
        arr1[0] = 200;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Поймали invalid_argument через arr1[0] = 200: " << e.what() << "\n";
    }

    Array<int> arr2(arr1);
    std::cout << "arr1 == arr2: " << std::boolalpha << (arr1 == arr2) << "\n";
    std::cout << "arr1 != arr2: " << (arr1 != arr2) << "\n";

    Array<int> arr3(3);
    arr3[0] = 1; arr3[1] = 2; arr3[2] = 3;
    arr1 += arr3;
    std::cout << "arr1 += arr3: " << arr1 << "\n";
    arr1 -= arr3;
    std::cout << "arr1 -= arr3: " << arr1 << "\n";

    arr1 += 10;
    std::cout << "arr1 += 10: " << arr1 << "\n";
    arr1 -= 10;
    std::cout << "arr1 -= 10: " << arr1 << "\n";

    std::cout << "Итерация for (const auto& x : arr1): ";
    for (const auto& x : arr1) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "Итерация for (auto& x : arr1) с модификацией x += 1: ";
    for (auto& x : arr1) {
        x += 1;
    }
    std::cout << "\narr1: " << arr1 << "\n";

    return 0;
}
