#include "../include/Pentagon.h"

Pentagon::Pentagon() : Figure(point_count) {};

Pentagon::Pentagon(Point* arr) : Figure(arr, point_count) {};

Pentagon::Pentagon(const Pentagon& other) : Figure(other) {};

Pentagon::Pentagon(Pentagon&& other) noexcept: Figure(std::move(other)) {};

Figure::FIGURE_TYPE Pentagon::get_type() const
{
    return type;
}

Pentagon& Pentagon::operator=(const Pentagon& other)
{
    if (*this == other)
        return *this;

    for (int i{0}; i < point_count; i++)
        coords[i] = other.coords[i];

    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept
{
    if (*this == other)
        return *this;

    delete [] coords;
    coords = other.coords;
    other.coords = nullptr;

    return *this;
}

Point Pentagon::geomc() const
{
    return Figure::dop_geomc(coords, point_count);
}

Pentagon::operator double() const
{
    return 1.7204774005889671 * std::pow(distance(coords[0], coords[1]), 2);
}

std::istream& Pentagon::input(std::istream& is)
{
    for (int i{0}; i < point_count; i++)
        is >> coords[i];

    if (!check_and_reorder(coords, point_count))
    {
        throw std::invalid_argument("Невозможно построить правильный пятиугольник");
    }

    return is;
}

std::ostream& Pentagon::output(std::ostream& os) const
{
    os << "Пятиугольник: ";

    for (int i{0}; i < point_count; i++)
        os << coords[i] << ' ';

    return os;
}

int Pentagon::get_vertices_number() const
{
    return point_count;
}