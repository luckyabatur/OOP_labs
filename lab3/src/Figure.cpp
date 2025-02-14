
#include <iostream>
#include "../include/Point.h"
#include "../include/Figure.h"
#include <limits>
#include <algorithm>
#include "../include/double_equal.h"

Figure::Figure(const int vertices_number)
{
    coords = new Point[vertices_number];
}

Figure::Figure(Point* arr, const int vertices_number)
{

    if (!check_and_reorder(arr, vertices_number))
        throw std::invalid_argument("Невозможно построить правильный пятиугольник");

    coords = new Point[vertices_number];
    for (int i{0}; i < vertices_number; i++)
        coords[i] = arr[i];
}

Figure::Figure(const Figure& other)
{
    int v_n = other.get_vertices_number();
    coords = new Point[v_n];
    for (int i{0}; i < v_n; i++)
        coords[i] = other.coords[i];
}

Figure::Figure(Figure&& other) noexcept
{
    coords = other.coords;
    other.coords = nullptr;
}

Figure::~Figure()
{
    delete [] coords;
    coords = nullptr;
}

bool operator==(const Figure& fig1, const Figure& fig2)
{
    if (fig1.get_type() != fig2.get_type())
        return false;

    Point cent1 = fig1.geomc();
    Point cent2 = fig2.geomc();

    if (cent1 == cent2 && double_equal(distance(fig1.coords[0], cent1), distance(fig2.coords[0], cent2)))
        return true;

    return false;
}

std::ostream& operator<<(std::ostream& os, const Figure& fig)
{
    return fig.output(os);
}

std::istream& operator>>(std::istream& is, Figure& fig)
{
    return fig.input(is);
}

bool Figure::check_and_reorder(Point* arr, int point_number)
{
    Point center = dop_geomc(arr, point_number);
    double rad = distance(center, arr[0]);

    if (double_equal(rad, 0.0))
        return false;

    for (int i{1}; i < point_number; i++)
        if (!double_equal(distance(center, arr[i]), rad))
            return false;

    double min_d = std::numeric_limits<double>::infinity();
    int sec_v{0};

    for (int i{1}; i < point_number; i++)
        if (distance(arr[0], arr[i]) < min_d)
        {
            min_d = distance(arr[0], arr[i]);
            sec_v = i;
        }

    std::swap(arr[1], arr[sec_v]);

    bool flag = false;
    for (int i{1}; i < point_number-1; i++)
    {
        flag = false;
        for (int j{i + 1}; j < point_number; j++)
            if (double_equal(distance(arr[i], arr[j]), min_d))
            {
                std::swap(arr[i+1], arr[j]);
                flag = true;
                break;
            }
       if (!flag)
           return false;
    }

    if (!double_equal(distance(arr[point_number - 1], arr[0]), min_d))
        return false;

    return true;
}

Point Figure::dop_geomc(Point* arr, int point_number)
{
    double x{0};
    for (int i{0}; i < point_number; i++)
        x += arr[i].get_x();

    x /= point_number;

    double y{0};
    for (int i{0}; i < point_number; i++)
        y += arr[i].get_y();

    y /= point_number;

    return Point{x, y};
}
