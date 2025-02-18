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
//    explicit Pentagon(Point<T>* arr);
    Pentagon(const Pentagon&  other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    [[nodiscard]] Point<double> geomc() const override;
    explicit operator double() const override;

    [[nodiscard]] Figure<T>::FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;


    ~Pentagon() override = default;
};

template<Number T>
Pentagon<T>::Pentagon() : Figure<T>(point_count) {};

//template<Number T>
//Pentagon<T>::Pentagon(Point<T>* arr) : Figure<T>(arr, point_count) {};

template<Number T>
Pentagon<T>::Pentagon(const Pentagon<T>& other) : Figure<T>(other) {};

template<Number T>
Pentagon<T>::Pentagon(Pentagon<T>&& other) noexcept: Figure<T>(std::move(other)) {};

template<Number T>
Figure<T>::FIGURE_TYPE Pentagon<T>::get_type() const
{
    return type;
}

template<Number T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other)
{
    if (*this == other)
        return *this;

    for (int i{0}; i < point_count; i++)
        Figure<T>::coords[i] = other.coords[i];

    return *this;
}

template<Number T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& other) noexcept
{
    if (*this == other)
        return *this;

    Figure<T>coords = other.coords;
    other.coords = nullptr;

    return *this;
}

template<Number T>
Point<double> Pentagon<T>::geomc() const
{
    return Figure<T>::dop_geomc(Figure<T>::coords, point_count);
}

template<Number T>
Pentagon<T>::operator double() const
{
    return 1.7204774005889671 * std::pow(distance(Figure<T>::coords[0], Figure<T>::coords[1]), 2);
}

template<Number T>
std::istream& Pentagon<T>::input(std::istream& is)
{
    for (int i{0}; i < point_count; i++)
        is >> Figure<T>::coords[i];

    if (!check_and_reorder(Figure<T>::coords, point_count))
    {
        throw std::invalid_argument("Невозможно построить правильный пятиугольник");
    }

    return is;
}

template<Number T>
std::ostream& Pentagon<T>::output(std::ostream& os) const
{
    os << "Пятиугольник: ";

    for (int i{0}; i < point_count; i++)
        os << Figure<T>::coords[i] << ' ';

    return os;
}

template<Number T>
int Pentagon<T>::get_vertices_number() const
{
    return point_count;
}








