#include "../include/Hexagon.h"

Hexagon::Hexagon() : Figure(point_count) {};

Hexagon::Hexagon(Point* arr) : Figure(arr, point_count) {};

Hexagon::Hexagon(const Hexagon& other) : Figure(other) {};

Hexagon::Hexagon(Hexagon&& other) noexcept : Figure(std::move(other)) {};

Figure::FIGURE_TYPE Hexagon::get_type() const
{
    return type;
}

Hexagon& Hexagon::operator=(const Hexagon& other)
{
    if (*this == other)
        return *this;

    for (int i{0}; i < point_count; i++)
        coords[i] = other.coords[i];

    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept
{
    if (*this == other)
        return *this;

    delete [] coords;
    coords = other.coords;
    other.coords = nullptr;

    return *this;
}

Point Hexagon::geomc() const
{
    double x = (coords[0].get_x() + coords[3].get_x()) / 2;
    double y = (coords[0].get_y() + coords[3].get_y()) / 2;

    return Point{x, y};
}

Hexagon::operator double() const
{
    return 2.59807621135331594 * std::pow(distance(coords[0], coords[1]), 2);
}

std::istream& Hexagon::input(std::istream& is)
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

std::ostream& Hexagon::output(std::ostream& os) const
{
    os << "Шестиугольник: ";
    for (int i{0}; i < point_count; i++)
        os << coords[i] << ' ';

    return os;
}

int Hexagon::get_vertices_number() const
{
    return point_count;
}
