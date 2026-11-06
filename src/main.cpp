#include "../include/DynamicArray.h"
#include <iostream>
#include <string>
#include <utility>

template <typename T>
void processArray(Array<T> arr) {
    std::cout << "Внутри функции processArray: " << arr << "\n";
}

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

    std::cout << "\nRule of Five\n";

    
    std::cout << "operator= (копирование)\n";
    Array<int> assigned(1);
    assigned = arr1;
    std::cout << "assigned после assigned = arr1: " << assigned << "\n";

    
    Array<int>& ref_assigned = assigned;
    assigned = ref_assigned;
    std::cout << "assigned после самоприсваивания: " << assigned << "\n";

    
    Array<int> chain1(1), chain2(1);
    chain1 = chain2 = arr1;
    std::cout << "chain1 после chain1 = chain2 = arr1: " << chain1 << "\n";

    
    std::cout << "\nMove-конструктор\n";
    Array<int> temp(3);
    temp[0] = 100; temp[1] = 90; temp[2] = 80;
    std::cout << "temp до move: " << temp << "\n";

    Array<int> moved_construct(std::move(temp));
    std::cout << "moved_construct (принял ресурсы): " << moved_construct << "\n";
    std::cout << "temp после move (ресурсы обнулены): " << temp << "\n";

    
    std::cout << "\nMove-оператор присваивания\n";
    Array<int> moved_assign(1);
    moved_assign = std::move(moved_construct);
    std::cout << "moved_assign (принял ресурсы): " << moved_assign << "\n";
    std::cout << "moved_construct после move: " << moved_construct << "\n";

    
    std::cout << "\n--- 4. Передача в функцию до и после move ---\n";
    Array<int> demo(2);
    demo[0] = 42; demo[1] = 43;
    std::cout << "demo до вызова processArray: " << demo << "\n";

    
    processArray(demo);
    std::cout << "demo после передачи по значению (копия): " << demo << "\n";

    
    processArray(std::move(demo));
    std::cout << "demo после передачи через std::move: " << demo << "\n";

    return 0;
}
