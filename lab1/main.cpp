#include <iostream>
#include "include/delete_letters.h"


int main()
{
    std::string lettnum, result;
    std::cout << "Input your string: " << std::flush;
    std::cin >> lettnum;

    result = delete_letters(lettnum);

    if (result.empty())
        std::cout << "There are no numbers in the string or it contains invalid characters" << std::endl;
    else
        std::cout << "The numbers of your string: " << result << std::endl;



    return 0;
}
