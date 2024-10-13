#pragma once

#include <string>
#include <iostream>

class Eleven
{
public:
    Eleven();
    Eleven(const size_t & n, unsigned char t = 0);
    Eleven(const std::initializer_list< unsigned char> &t);
    Eleven(const string &t);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    virtual ~Eleven() noexcept;
private:
    sise_t _size;
    unsigned char *_array;
};


class Eleven
{
public:
    Eleven();
    Eleven(const size_t & n, unsigned char t = 0);
    Eleven(const std::initializer_list< unsigned char> &t);
    Eleven(const std::string &t);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;

    Eleven add(const Eleven& other);
    Eleven remove(const Eleven& other);
    bool      equals(const Eleven& other) const;
    std::ostream&   print(std::ostream& os);

    virtual ~Eleven() noexcept;
private:
    size_t _size;
    unsigned char *_array;
};


