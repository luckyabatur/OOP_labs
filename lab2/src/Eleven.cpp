#include "../include/Eleven.h"

Eleven::Eleven() : _size(0), _array{nullptr} {}

Eleven::Eleven(const size_t &n, unsigned char t)
{
    if (!(t >= '0' && t <= '9' || t == 'A') || (n <= 0) ||( (n > 1) && t == '0'))
    {
        delete[] _array;
        throw std::invalid_argument("Char constructor error");
    }
    _array = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
        _array[i] = t;
    _size = n;
}

Eleven::Eleven(const std::initializer_list<unsigned char> &t)
{
    if (empty(t))
    {
        return;
    }

    int count{0};
    bool flag{true};
    size_t i{0};

    for (auto &c : t)
    {
        if (c == '0' && flag)
        {
            count++;
            continue;
        }
        else if (flag)
        {
            flag = false;
            _array = new unsigned char[t.size()-count];
            i = t.size()-count-1;
        }
        if (!(c >= '0' && c <= '9' || c == 'A'))
        {
            delete[] _array;
            throw std::invalid_argument("Initializer list constructor error");
        }
        _array[i--] = c;
    }

    _size = t.size()-count;
    if (count > 0 && count == t.size())
    {
        _size++;
        _array = new unsigned char []{'0'};
    }
}

Eleven::Eleven(std::string t)
{
    if (empty(t))
    {
        return;
    }

    int count{0};
    while (t[count] == '0')
        count++;
    t.erase(0, count);

    if (empty(t))
    {
        _size = 1;
        _array = new unsigned char[]{'0'};
        return;
    }

    _array = new unsigned char[t.size()];
    _size  = t.size();

    for(size_t i{0}; i < _size;++i)
    {
        int j = _size - 1 - i;
        if (!(t[j] >= '0' && t[j] <= '9' || t[j] == 'A'))
        {
            delete[] _array;
            throw std::invalid_argument("String constructor error");
        }
        _array[i] = t[j];
    }
}

Eleven::Eleven(const Eleven &other)
{
    _size  = other._size;
    _array = new unsigned char[_size];

    for(size_t i{0};i<_size;++i) _array[i] = other._array[i];
}

Eleven::Eleven(Eleven &&other) noexcept
{
    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr;
}

Eleven Eleven::add(const Eleven &other)
{
    int t{0};
    const  bool first_bigger = _size > other._size;
    const size_t max_size = (first_bigger ? _size : other._size);
    const size_t min_size = (!first_bigger ? _size : other._size);

    size_t new_size = max_size;
    int temp[max_size + 1];

    for (int i = 0; i < max_size; i++)
    {
        temp[i] = t;
        t = 0;
        if (i < min_size)
            temp[i] += to_ten(_array[i]) + to_ten(other._array[i]);
        else if (first_bigger)
            temp[i] += to_ten(_array[i]);
        else
            temp[i] += to_ten(other._array[i]);
        if (temp[i] > 10)
        {
            t = 1;
        }
    }
    if (temp[max_size-1] > 10)
    {
        temp[max_size-1] = temp[max_size-1] - 11;
        temp[max_size] = 1;
        new_size++;
    }

    delete [] _array;
    _array = new unsigned char[new_size];
    _size = new_size;
    for (int i = new_size-1; i >= 0; i--)
        _array[i] = to_eleven[temp[i]];
    return *this;
}

Eleven Eleven::remove(const Eleven &other)
{
    if((*this).lt(other)) throw std::logic_error("Eleven can't be negative");

    int temp[_size];
    int t{0};
    size_t new_size{_size};

    for (int i = 0; i < _size; i++)
    {
        int a = to_ten(_array[i]);
        int b = (i < other._size) ? to_ten(other._array[i]) : 0;

        if (a - t < b)
        {

            temp[i] = 11 - t - b + a;
            t = 1;
        }
        else
        {
            temp[i] = a - t - b;
            t = 0;
        }
    }

    int j = _size-1;
    while (temp[j--] == 0)
    {
        new_size--;
    }

    delete [] _array;
    _array = new unsigned char [new_size];
    _size = new_size;
    for (int i = new_size - 1; i >= 0; i--)
        _array[i] = to_eleven[temp[i]];
    return *this;
}

bool Eleven::equals(const Eleven &other) const
{
    if(_size!=other._size)
        return false;

    for (int i = 0; i < _size; i++)
        if (_array[i] != other._array[i])
            return false;

    return true;
}

bool Eleven::lt(const Eleven& other) const
{
    return (*this).compare(other, LESS);
}


bool Eleven::mt(const Eleven& other) const
{
    return (*this).compare(other, MORE);
}

bool Eleven::compare(const Eleven &other, Eleven::COMPARE_TYPE type) const
{
    if (_size < other._size)
        return type;
    else if (_size > other._size)
        return !type;

    for (int i = _size - 1; i >= 0; i--)
    {
        if (_array[i] < other._array[i])
            return type;
        else if (_array[i] > other._array[i])
            return !type;
    }

    return false;
}
std::ostream &Eleven::print(std::ostream &os)
{
    for (int i = _size - 1; i >= 0; i--)
        os << _array[i];

    return os;
}

Eleven::~Eleven() noexcept
{
    if (_size > 0)
    {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}