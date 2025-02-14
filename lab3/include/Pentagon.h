#pragma once

#include <iostream>
#include <cmath>

#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

class Pentagon: public Figure
{
    const static int point_count{5};
    const static FIGURE_TYPE type{PENTAGON};
public:
    Pentagon();
    explicit Pentagon(Point* arr);
    Pentagon(const Pentagon&  other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    [[nodiscard]] Point geomc() const override;
    explicit operator double() const override;

    [[nodiscard]] FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;


    ~Pentagon() override = default;
};








