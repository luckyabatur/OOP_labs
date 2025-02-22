#pragma once

#include <iostream>
#include <cmath>
#include "./double_equal.h"
#include <concepts>
#include <type_traits>

template <typename T>
concept Number = std::is_arithmetic_v<T>;

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept Float_point = std::is_floating_point_v<T>;


template <Number T>
class Point
{
    T x{}, y{};

public:
    Point() = default;
    Point(T _x, T _y);
    Point(const Point& other);

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << p.x << ' ' << p.y;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& p)
    {
        is >> p.x >> p.y;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::invalid_argument("Некорректные значения");; // дописать
        }
        return is;
    }

    friend bool operator==(const Point& p1, const Point& p2) requires Integral<T>
    {
        if (p1.x != p2.x || p1.y != p2.y)
            return false;

        return true;
    }

    friend bool operator==(const Point& p1, const Point& p2) requires Float_point<T>
    {
        if (!double_equal(p1.x, p2.x) || !double_equal(p1.y, p2.y))
            return false;

        return true;
    }


    friend double distance(const Point& p1, const Point& p2)
    {
        return std::sqrt(std::pow(p1.x-p2.x, 2) + std::pow(p1.y-p2.y, 2));
    }

    [[nodiscard]] T get_x() const;
    [[nodiscard]] T get_y() const;
};


template <Number T>
Point<T>::Point(T _x, T _y) : x{_x}, y{_y} {}

template <Number T>
Point<T>::Point(const Point& other) : x{other.x}, y{other.y} {}

template <Number T>
T Point<T>::get_x() const {return x;}

template <Number T>
T Point<T>::get_y() const {return y;}