#include "include/Eleven.h"

Eleven* check_and_create11(const std::string &str)
{
    try
    {
       auto number = new Eleven{str};
       return number;
    }
    catch(std::invalid_argument &ex)
    {
        return nullptr;
    }
}


int main()
{
    char choice{0};
    while (choice != '6')
    {
        std::string a, b;
        std::cout << "Введите числа: ";
        std::cin >> a >> b;
        Eleven* n1 = check_and_create11(a);
        Eleven* n2 = check_and_create11(b);
        if (n1 == nullptr || n2 == nullptr)
        {
            std::cout << "Некорректные данные\n";
            continue;
        }
        std::cout << "Выберите действие(введите цифру):\n1 +\n2 -\n3 =\n4 <\n5 >\n6 Выход" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
            case ('1'):
                std::cout << "Результат: ";
                n1->add(*n2).print(std::cout) << std::endl;
                break;
            case('2'):
                std::cout << "Результат: ";
                n1->remove(*n2).print(std::cout) << std::endl;
                break;
            case ('3'):
                std::cout << "Результат: " << (n1->equals(*n2) ? "Верно" : "Неверно") << std::endl;
                break;
            case ('4'):
                std::cout << "Результат: " << (n1->lt(*n2) ? "Верно" : "Неверно") << std::endl;
                break;
            case ('5'):
                std::cout << "Результат: " << (n1->mt(*n2) ? "Верно" : "Неверно") << std::endl;
                break;
            case ('6'):
                break;
            default:
                std::cout << "Сделайте корректный выбор" << std::endl;
        }
        std:: cout << "------------------------------" << std::endl;
        std::cin.ignore(100000, '\n');
//        delete n1;
//        delete n2;
    }
    return 0;
}
