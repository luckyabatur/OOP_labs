#pragma once
#include <memory>
#include <cassert>



template <typename T>
class Array
{
    std::shared_ptr<T[]> array{nullptr};
    int size{0};
    int capacity{0};

    void resize();

public:

    void push_back(const T el);
    bool del(int index);
    bool empty(size_t index);
    int get_size();

    Array() = default;
    Array(const std::initializer_list<T> &t);
    Array(const Array &other);
    Array(Array &&other) noexcept;



    T& operator[](size_t index);
};

template <typename T>
void Array<T>::resize()
{
    if (capacity == 0)
        capacity = 1;
    else
        capacity *= 2;

    std::shared_ptr<T[]> new_arr (new T[capacity]);

    for (int i{0}; i < size; i++)
        new_arr[i] = array[i];

    array = new_arr;
}

template <typename T>
void Array<T>::push_back(const T el)
{
    if (size == capacity) resize();

    array[size] = el;
    ++size;
}

template <typename T>
bool Array<T>::del(int index)
{
    if (index < 0 || index >= size)
        return false;

    for (int i{index}; i < size-1; i++)
        array[i] = array[i+1];

    --size;
    return true;
}


template <typename T>
Array<T>::Array(const std::initializer_list<T> &t)
{
    array = std::shared_ptr<T[]>(new T[t.size()]);
    size_t i{0};
    for (auto &c : t)
        array[i++] = c;
    size = capacity = t.size();
}

template <typename T>
Array<T>::Array(const Array &other)
{
    size = capacity = other.size;
    array = std::shared_ptr<T[]>(new T[size]);

    for (size_t i{0}; i < size; ++i)
        array[i] = other.array[i];
}

template <typename T>
Array<T>::Array(Array &&other) noexcept
{
    size = other.size;
    array = other.array;
    capacity = other.capacity;

    other.size = other.capacity = 0;
    other.array = nullptr;
}

template <typename T>
T& Array<T>::operator[](size_t index)
{
    assert(index < size);
    return array[index];
}

template <typename T>
bool Array<T>::empty(size_t index)
{
    return size;
}

template <typename T>
int Array<T>::get_size()
{
    return size;
}