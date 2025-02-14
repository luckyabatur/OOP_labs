#pragma once

#include <iostream>
#include <cmath>

#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

class Octagon: public Figure
{
    const static int point_count{8};
    const static FIGURE_TYPE type{OCTAGON};
public:
    Octagon();
    explicit Octagon(Point* arr);
    Octagon(const Octagon&  other);
    Octagon(Octagon&& other) noexcept;

    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;

    [[nodiscard]] Point geomc() const override;
    explicit operator double() const override;

    [[nodiscard]] FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;


    ~Octagon() override = default;
};








