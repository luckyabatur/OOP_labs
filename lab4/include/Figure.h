#pragma once

#include <iostream>
#include "./Point.h"
#include "./double_equal.h"
#include <memory>
#include <limits>

template <Number T>
class Figure
{
protected:
    enum FIGURE_TYPE {PENTAGON, HEXAGON, OCTAGON};

    std::shared_ptr<std::unique_ptr<Point<T>>[]> coords{nullptr};

    virtual std::ostream& output(std::ostream& os) const = 0 ;
    virtual std::istream& input(std::istream& is) = 0;

    static bool check_and_reorder(std::shared_ptr<std::unique_ptr<Point<T>>[]>& arr, int point_number);
    static Point<double> dop_geomc(std::shared_ptr<std::unique_ptr<Point<T>>[]>& arr, int point_number);

public:
    using value_type = T;

    Figure() = default;
    explicit Figure(const int vertices_number);
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;

    [[nodiscard]] virtual Point<double> geomc() = 0;
    virtual explicit operator double() const = 0;

    [[nodiscard]] virtual FIGURE_TYPE get_type() const = 0;
    [[nodiscard]] virtual int get_vertices_number() const = 0;

    friend bool operator==(const Figure& fig1, const Figure& fig2)
    {
        if (fig1.get_type() != fig2.get_type())
            return false;
        Point<double> cent1 = fig1.geomc();
        Point<double> cent2 = fig2.geomc();
        if (cent1 == cent2 && double_equal(distance(*fig1.coords[0], cent1),
                                           distance(*fig2.coords[0], cent2)))
            return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig)
    {
        return fig.output(os);
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig)
    {
        return fig.input(is);
    }

    virtual ~Figure() = default;
};

template <Number T>
Figure<T>::Figure(const int vertices_number)
{
    auto tmp = new std::unique_ptr<Point<T>>[vertices_number];
    for(int i = 0; i < vertices_number; i++){
        tmp[i] = std::make_unique<Point<T>>();
    }
    coords = std::shared_ptr<std::unique_ptr<Point<T>>[]>(tmp);
}

template <Number T>
Figure<T>::Figure(const Figure& other)
{
    int v_n = other.get_vertices_number();
    auto tmp = new std::unique_ptr<Point<T>>[v_n];
    for(int i = 0; i < v_n; i++){
        tmp[i] = std::make_unique<Point<T>>(*other.coords[i]);
    }
    coords = std::shared_ptr<std::unique_ptr<Point<T>>[]>(tmp);
}

template <Number T>
Figure<T>::Figure(Figure&& other) noexcept
{
    coords = std::move(other.coords);
}

template <Number T>
bool Figure<T>::check_and_reorder(std::shared_ptr<std::unique_ptr<Point<T>>[]>& arr, int point_number)
{
    Point<double> center = dop_geomc(arr, point_number);
    double rad = distance(center, *arr[0]);
    if (double_equal(rad, 0.0))
        return false;

    for (int i{1}; i < point_number; i++)
        if (!double_equal(distance(center, *arr[i]), rad))
            return false;

    double min_d = std::numeric_limits<double>::infinity();
    int sec_v{0};

    for (int i{1}; i < point_number; i++)
    {
        double dist_0i = distance(*arr[0], *arr[i]);
        if (dist_0i < min_d)
        {
            min_d = dist_0i;
            sec_v = i;
        }
    }

    std::swap(arr[1], arr[sec_v]);

    bool flag = false;
    for (int i{1}; i < point_number - 1; i++)
    {
        flag = false;
        for (int j{i + 1}; j < point_number; j++)
        {
            if (double_equal(distance(*arr[i], *arr[j]), min_d))
            {
                std::swap(arr[i+1], arr[j]);
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }

    if (!double_equal(distance(*arr[point_number - 1], *arr[0]), min_d))
        return false;

    return true;
}

template <Number T>
Point<double> Figure<T>::dop_geomc(std::shared_ptr<std::unique_ptr<Point<T>>[]>& arr, int point_number)
{
    double x{0};
    double y{0};
    for (int i{0}; i < point_number; i++)
    {
        x += arr[i]->get_x();
        y += arr[i]->get_y();
    }
    x /= point_number;
    y /= point_number;
    return Point<double>{x, y};
}
