#pragma once

#include <iostream>
#include "./Point.h"
#include "./double_equal.h"


class Figure
{
protected:
    enum FIGURE_TYPE {PENTAGON, HEXAGON, OCTAGON} ;
    Point* coords{nullptr};

    virtual std::ostream& output(std::ostream& os) const = 0 ;
    virtual std::istream& input(std::istream& is) = 0;

    static bool check_and_reorder(Point* arr, int point_number);
    static Point dop_geomc(Point* arr, int point_number);

public:

    Figure() = default;
    explicit Figure(const int vertices_number);
    Figure(Point* arr, const int vertices_number);
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;

    [[nodiscard]] virtual Point geomc() const = 0;
    virtual explicit operator double() const = 0;

    [[nodiscard]] virtual FIGURE_TYPE get_type() const = 0;
    [[nodiscard]] virtual int get_vertices_number() const = 0;

    friend bool operator==(const Figure& fig1, const Figure& fig2);

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);

    virtual ~Figure();
};
