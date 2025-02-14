#pragma once

#include <iostream>
#include <cmath>

#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

class Hexagon: public Figure
{
    const static int point_count{6};
    const static FIGURE_TYPE type{HEXAGON};
public:
    Hexagon();
    explicit Hexagon(Point* arr);
    Hexagon(const Hexagon&  other);
    Hexagon(Hexagon&& other) noexcept;

    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;

    [[nodiscard]] Point geomc() const override;
    explicit operator double() const override;

    [[nodiscard]] FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;


    ~Hexagon() override = default;
};








