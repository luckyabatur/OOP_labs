#pragma once

#include <string>

typedef enum {LETTER, DIGIT, OTHER} TYPE;

TYPE check_char(char ch);
std::string delete_letters(std::string str);