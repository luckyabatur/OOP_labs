#pragma once

#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

template<Number T>
class Hexagon: public Figure<T>
{
    const static typename Figure<T>::FIGURE_TYPE type{Figure<T>::HEXAGON};
public:
    const static int point_count{6};

    using value_type = T;
    Hexagon();
    Hexagon(const Hexagon&  other);
    Hexagon(Hexagon&& other) noexcept;

    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;

    [[nodiscard]] Point<double> geomc() override;
    explicit operator double() const override;

    [[nodiscard]] typename Figure<T>::FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;

    ~Hexagon() override = default;
};

template<Number T>
Hexagon<T>::Hexagon() : Figure<T>(point_count) {}

template<Number T>
Hexagon<T>::Hexagon(const Hexagon<T>& other) : Figure<T>(other) {}

template<Number T>
Hexagon<T>::Hexagon(Hexagon<T>&& other) noexcept : Figure<T>(std::move(other)) {}

template<Number T>
typename Figure<T>::FIGURE_TYPE Hexagon<T>::get_type() const
{
    return type;
}

template<Number T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon<T>& other)
{
    if (this == &other)
        return *this;
    for (int i{0}; i < point_count; i++)
    {
        *this->coords[i] = *other.coords[i];
    }
    return *this;
}

template<Number T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon<T>&& other) noexcept
{
    if (this == &other)
        return *this;
    this->coords = other.coords;
    other.coords = nullptr;
    return *this;
}

template<Number T>
Point<double> Hexagon<T>::geomc()
{
    double x = ((this->coords[0])->get_x() + (this->coords[3])->get_x()) / 2;
    double y = ((this->coords[0])->get_y() + (this->coords[3])->get_y()) / 2;

    return Point{x, y};
}

template<Number T>
Hexagon<T>::operator double() const
{
    return 2.59807621135331594
           * std::pow(distance(*this->coords[0], *this->coords[1]), 2);
}

template<Number T>
std::istream& Hexagon<T>::input(std::istream& is)
{
    for (int i{0}; i < point_count; i++)
    {
        is >> *this->coords[i];
    }
    if (!this->check_and_reorder(this->coords, point_count))
    {
        throw std::invalid_argument("Невозможно построить шестиугольник");
    }
    return is;
}

template<Number T>
std::ostream& Hexagon<T>::output(std::ostream& os) const
{
    os << "Шестиугольник: ";
    for (int i{0}; i < point_count; i++)
    {
        os << *this->coords[i] << ' ';
    }
    return os;
}

template<Number T>
int Hexagon<T>::get_vertices_number() const
{
    return point_count;
}
