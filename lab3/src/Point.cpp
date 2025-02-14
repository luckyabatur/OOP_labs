#include "../include/Point.h"
#include <iostream>
#include <cmath>
#include "../include/double_equal.h"


Point::Point(double x, double y) : x{x}, y{y} {}

Point::Point(const Point& other) : x{other.x}, y{other.y} {}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << p.x << ' ' << p.y;
    return os;
}

std::istream& operator>>(std::istream& is, Point& p)
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

bool operator==(const Point& p1, const Point& p2)
{
    if (!double_equal(p1.x, p2.x) || !double_equal(p1.y, p2.y))
        return false;

    return true;
}


double distance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p1.x-p2.x, 2) + std::pow(p1.y-p2.y, 2));
}

double Point::get_x() const {return x;}

double Point::get_y() const {return y;}