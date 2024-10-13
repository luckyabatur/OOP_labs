#include "Eleven.h"

Eleven::Eleven() : _size(0), _array{nullptr}
{
    std::cout << "Default constructor" << std::endl;
}

Eleven::Eleven(const size_t &n, unsigned char t)
{
    std::cout << "Fill constructor" << std::endl;
    _array = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
        _array[i] = t;
    _size = n;
}

Eleven::Eleven(const std::initializer_list<unsigned char> &t)
{
    std::cout << "Initializer list constructor" << std::endl;
    _array = new unsigned char[t.size()];
    size_t i{0};
    for (auto &c : t)
        _array[i++] = c;
    _size = t.size();
}

Eleven::Eleven(const std::string &t)
{
    std::cout << "Copy string constructor" << std::endl;
    _array = new unsigned char[t.size()];
    _size  = t.size();

    for(size_t i{0};i<_size;++i) _array[i] = t[i];
}

Eleven::Eleven(const Eleven &other)
{
    std::cout << "Copy constructor" << std::endl;
    _size  = other._size;
    //delete _array;
    _array = new unsigned char[_size];

    for(size_t i{0};i<_size;++i) _array[i] = other._array[i];
}

Eleven::Eleven(Eleven &&other) noexcept
{
std::cout << "Move constructor" << std::endl;
_size = other._size;
_array = other._array;

other._size = 0;
other._array = nullptr;
}

Eleven Eleven::add(const Eleven &other)
{
    return Eleven(this->_size+other._size,'1');
}
Eleven Eleven::remove(const Eleven &other)
{

    if(_size<other._size) throw std::logic_error("dash Eleven can't be negative");

    _size -= other._size;

    return *this;
}

bool Eleven::equals(const Eleven &other) const
{
    return _size==other._size;
}

std::ostream &Eleven::print(std::ostream &os)
{
    for (size_t i = 0; i < _size; ++i)
        os << _array[i];
    return os;
}

Eleven::~Eleven() noexcept
{
std::cout << "destructor" << std::endl;
if (_size > 0)
{
_size = 0;
delete[] _array;
_array = nullptr;
}
}