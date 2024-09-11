#include "../include/delete_letters.h"

TYPE check_char(char ch) {
    if (ch >= 48 && ch <= 57)
        return DIGIT;

    if (ch >= 65 && ch <= 90 || \
    ch >= 97 && ch <= 122)
        return LETTER;

    return OTHER;
}


std::string delete_letters(std::string str)
{
    TYPE type;
    char state = 0;
    std::string result;

    for (char ch: str) {
        type = check_char(ch);

        if (type == OTHER)
            return {};

        switch (state) {
            case 0:
                if (type == DIGIT) {
                    state = 1;
                    result.push_back(ch);
                }
                break;
            case 1:
                if (type == DIGIT) {
                    state = 1;
                    result.push_back(ch);
                } else {
                    state = 0;
                    result.push_back(' ');
                }
                break;
        }
    }
    return result;
}
