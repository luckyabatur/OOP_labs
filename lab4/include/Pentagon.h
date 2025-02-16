#pragma once


#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

template<Number T>
class Pentagon: public Figure<T>
{
    const static int point_count{5};
    const static Figure<T>::FIGURE_TYPE type{Figure<T>::PENTAGON};
public:
    Pentagon();
    explicit Pentagon(Point<T>* arr);
    Pentagon(const Pentagon&  other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    [[nodiscard]] Point<T> geomc() const override;
    explicit operator double() const override;

    [[nodiscard]] Figure<T>::FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;


    ~Pentagon() override = default;
};









