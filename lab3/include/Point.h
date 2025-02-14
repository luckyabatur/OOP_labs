#pragma once

#include <iostream>
#include "./double_equal.h"

class Point
{
    double x{0}, y{0};

public:
    Point() = default;
    Point(double x, double y);
    Point(const Point& other);

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

    friend bool operator==(const Point& p1, const Point& p2);

    friend double distance(const Point& p1, const Point& p2);

    [[nodiscard]] double get_x() const;
    [[nodiscard]] double get_y() const;
};

double distance(const Point& p1, const Point& p2);