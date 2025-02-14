#include "../include/Octagon.h"

Octagon::Octagon() : Figure(point_count) {};

Octagon::Octagon(Point* arr) : Figure(arr, point_count) {};

Octagon::Octagon(const Octagon& other) : Figure(other) {};

Octagon::Octagon(Octagon&& other) noexcept: Figure(std::move(other)) {};

Figure::FIGURE_TYPE Octagon::get_type() const
{
    return type;
}

Octagon& Octagon::operator=(const Octagon& other)
{
    if (*this == other)
        return *this;

    for (int i{0}; i < point_count; i++)
        coords[i] = other.coords[i];

    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept
{
    if (*this == other)
        return *this;

    delete [] coords;
    coords = other.coords;
    other.coords = nullptr;

    return *this;
}

Point Octagon::geomc() const
{
    double x = (coords[0].get_x() + coords[4].get_x()) / 2;
    double y = (coords[0].get_y() + coords[4].get_y()) / 2;

    return Point{x, y};
}

Octagon::operator double() const
{
    return 4.828427124746190097 * std::pow(distance(coords[0], coords[1]), 2);
}

std::istream& Octagon::input(std::istream& is)
{
    for (int i{0}; i < point_count; i++)
        is >> coords[i];

    if (!check_and_reorder(coords, point_count))
    {
        coords = nullptr;
        throw std::invalid_argument("Невозможно построить правильный пятиугольник");
    }

    return is;
}

std::ostream& Octagon::output(std::ostream& os) const
{
    os << "Восьмиугольник: ";

    for (int i{0}; i < point_count; i++)
        os << coords[i] << ' ';

    return os;
}

int Octagon::get_vertices_number() const
{
    return point_count;
}