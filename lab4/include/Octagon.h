#pragma once

#include "./Point.h"
#include "./Figure.h"
#include "./double_equal.h"

template<Number T>
class Octagon: public Figure<T>
{
    const static typename Figure<T>::FIGURE_TYPE type{Figure<T>::OCTAGON};
public:
    const static int point_count{8};

    using value_type = T;
    Octagon();
    Octagon(const Octagon&  other);
    Octagon(Octagon&& other) noexcept;

    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;

    [[nodiscard]] Point<double> geomc() override;
    explicit operator double() const override;

    [[nodiscard]] typename Figure<T>::FIGURE_TYPE get_type() const override;
    [[nodiscard]] int get_vertices_number() const override;

    std::istream& input(std::istream& is) override;
    std::ostream& output(std::ostream& os) const override;

    ~Octagon() override = default;
};

template<Number T>
Octagon<T>::Octagon() : Figure<T>(point_count) {}

template<Number T>
Octagon<T>::Octagon(const Octagon<T>& other) : Figure<T>(other) {}

template<Number T>
Octagon<T>::Octagon(Octagon<T>&& other) noexcept : Figure<T>(std::move(other)) {}

template<Number T>
typename Figure<T>::FIGURE_TYPE Octagon<T>::get_type() const
{
    return type;
}

template<Number T>
Octagon<T>& Octagon<T>::operator=(const Octagon<T>& other)
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
Octagon<T>& Octagon<T>::operator=(Octagon<T>&& other) noexcept
{
    if (this == &other)
        return *this;
    this->coords = other.coords;
    other.coords = nullptr;
    return *this;
}

template<Number T>
Point<double> Octagon<T>::geomc()
{
    double x = ((this->coords[0])->get_x() + (this->coords[4])->get_x()) / 2;
    double y = ((this->coords[0])->get_y() + (this->coords[4])->get_y()) / 2;

    return Point{x, y};
}

template<Number T>
Octagon<T>::operator double() const
{
    return 4.828427124746190097
           * std::pow(distance(*this->coords[0], *this->coords[1]), 2);
}

template<Number T>
std::istream& Octagon<T>::input(std::istream& is)
{
    for (int i{0}; i < point_count; i++)
    {
        is >> *this->coords[i];
    }
    if (!this->check_and_reorder(this->coords, point_count))
    {
        throw std::invalid_argument("Невозможно построить восьмиугольник");
    }
    return is;
}

template<Number T>
std::ostream& Octagon<T>::output(std::ostream& os) const
{
    os << "Восьмиугольник: ";
    for (int i{0}; i < point_count; i++)
    {
        os << *this->coords[i] << ' ';
    }
    return os;
}

template<Number T>
int Octagon<T>::get_vertices_number() const
{
    return point_count;
}
