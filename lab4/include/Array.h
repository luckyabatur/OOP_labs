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
    bool empty();
    int get_size();

    Array() = default;
    Array(const std::initializer_list<T> &t);
    Array(const Array &other);
    Array(Array &&other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);

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
    if (this == &other)
        return;

    size = capacity = other.size;
    array = std::shared_ptr<T[]>(new T[size]);

    for (size_t i{0}; i < size; ++i)
        array[i] = other.array[i];
}

template <typename T>
Array<T>::Array(Array &&other) noexcept
{
    size = other.size;
    capacity = other.capacity;

    array = std::move(other.array);

    other.size = other.capacity = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    size = capacity = other.size;
    array = std::shared_ptr<T[]>(new T[size]);

    for (size_t i{0}; i < size; ++i)
        array[i] = other.array[i];

    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
    size = other.size;
    capacity = other.capacity;

    array = std::move(other.array);

    other.size = other.capacity = 0;

    return *this;
}


template <typename T>
T& Array<T>::operator[](size_t index)
{
    assert(index < size);
    return array[index];
}

template <typename T>
bool Array<T>::empty()
{
    return !size;
}

template <typename T>
int Array<T>::get_size()
{
    return size;
}