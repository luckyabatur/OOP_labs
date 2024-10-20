#pragma once

#include <string>
#include <iostream>

class Eleven
{
public:
    Eleven();
    Eleven(const size_t & n, unsigned char t = 0);
    Eleven(const std::initializer_list< unsigned char> &t);
    Eleven(std::string t);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    virtual ~Eleven() noexcept;
    Eleven add(const Eleven& other);
    Eleven remove(const Eleven& other);
    bool equals(const Eleven& other) const;
    bool lt(const Eleven& other) const;
    bool mt(const Eleven& other) const;
    std::ostream& print(std::ostream& os);
private:
    size_t _size{0};
    unsigned char *_array{nullptr};
    inline static unsigned char to_eleven[] {'0', '1', '2', '3', '4',
                                      '5', '6', '7', '8', '9',
                                      'A', '0', '1', '2', '3',
                                      '4', '5', '6', '7', '8', '9'};

    inline static int to_ten(unsigned char& number)
    {
        return (number == 'A') ? 10 : number - 48;
    }
    enum COMPARE_TYPE {MORE, LESS};
    bool compare(const Eleven& other, COMPARE_TYPE type) const;
};