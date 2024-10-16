#pragma once
#include <iostream>
#include <initializer_list>
#include <string>
//#include "IPrint.h"

template<typename T>
class Array 
{
private:
    const size_t GROWTH_FACTOR = 2; // !!!
    T* data;
    size_t size;
    size_t capacity;
public:
    Array() noexcept;
    Array(std::initializer_list<T> init_list);
    Array(T data[], size_t size);
    Array(const Array& other);
    ~Array() noexcept;
    Array& operator=(const Array& other);
    T& operator[](size_t index);
    void erase(size_t first) noexcept;
    void push_back(const T& value);
    void clear() noexcept;
    size_t get_size() const noexcept;
    void print() const noexcept;
};

template<typename T>
Array<T>::Array() noexcept
    : size(0), capacity(30)
{
    data = new T[capacity];
}

// Це конструктор який підтримує список ініціалізації наприклад:
// Array<int> arr = { 1,2,3,4,5 };
template<typename T>
Array<T>::Array(std::initializer_list<T> init_list)
    :size(init_list.size()), capacity(init_list.size()* GROWTH_FACTOR) // !!!
{
    data = new T[capacity];
    const T* begin = init_list.begin();
    for (size_t i = 0; i < size; i++)
    {
        data[i] = begin[i];
    }
}

template<typename T>
Array<T>::Array(T data[], size_t size)
    : size(size), capacity(size* GROWTH_FACTOR)
{
    this->data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        this->data[i] = data[i];
    }
}

template<typename T>
Array<T>::Array(const Array<T>& other)
    : size(other.size), capacity(other.capacity)
{
    delete[] data;
    data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
Array<T>::~Array() noexcept
{
    delete[] data;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    if (this != &other) {
        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
    if (index > size)
    {
        throw std::out_of_range("Index is out of range!");
    }
    return data[index];
}

template<typename T>
void Array<T>::erase(size_t first) noexcept
{
    for (int i = first; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
void Array<T>::push_back(const T& value)
{
    if (size == capacity) {
        capacity = capacity * GROWTH_FACTOR;
        T* newData = new T[capacity];

        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }
    data[size++] = value;
}

template<typename T>
void Array<T>::clear() noexcept
{
    size = 0;
}

template<typename T>
size_t Array<T>::get_size() const noexcept
{
    return size;
}

template<typename T>
void Array<T>::print() const noexcept {
    if (this->size == 0) return;
    for (size_t i = 0; i < this->size; i++)
    {
        std::cout << this->data[i] << ' ';
    }
    std::cout << std::endl;
}