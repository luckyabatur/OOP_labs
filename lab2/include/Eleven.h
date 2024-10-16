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
    Eleven add(const Eleven& other);
    Eleven remove(const Eleven& other);
    bool equals(const Eleven& other) const;
    std::ostream& print(std::ostream& os);
private:
    sise_t _size;
    unsigned char *_array;
    static int to_ten[] {['0'] = 0, ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4, ['5'] = 5,
                         ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9, ['A'] = 10};
    static unsigned char to_eleven[] {'0', '1', '2', '3', '4',
                                      '5', '6', '7', '8', '9',
                                      'A', '0', '1', '2', '3',
                                      '4', '5', '6', '7', '8', '9'};
};

//
//class Eleven
//{
//public:
//    Eleven();
//    Eleven(const size_t & n, unsigned char t = 0);
//    Eleven(const std::initializer_list< unsigned char> &t);
//    Eleven(const std::string &t);
//    Eleven(const Eleven& other);
//    Eleven(Eleven&& other) noexcept;
//
//
//
//
//    virtual ~Eleven() noexcept;
//private:
//    size_t _size;
//    unsigned char *_array;
//};


