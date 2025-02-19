#include "../include/array_func.h"
//#include <variant>


template <typename T>
int menu(T& v)
{
    char choice{0};
    input(v);
    while(choice != '7')
    {

        std::cout << "Выберите действие(введите цифру):\n"
                     "1 - Вывести координаты фигур\n"
                     "2 - Вывести координаты геометрических центров\n"
                     "3 - Вывести площади фигур\n"
                     "4 - Вывести суммарную площаь фигур\n"
                     "5 - Удалить элемент по индексу\n"
                     "6 - Ввести другой массив\n"
                     "7 - Выход" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
            case ('1'):
                output(v);
                break;
            case ('2'):
                print_geomc(v);
                break;
            case ('3'):
                print_square(v);
                break;
            case ('4'):
                std::cout << square_sum(v) << std::endl;
                break;
            case ('5'):
                std::cout << "Введите индекс" << std::endl;
                int index;
                std::cin.ignore(100000, '\n');
                std::cin >> index;
                if (!v.del(index))
                    std::cout << "Некорректный индекс" << std::endl;
                break;
            case ('6'):
                return 1;
            case ('7'):
                return 0;
            default:
                std::cout << "Сделайте корректный выбор" << std::endl;
        }
        std::cout << "------------------------------" << std::endl;
        std::cin.ignore(100000, '\n');
    }
    return 2;
}



int main(void)
{
    char choice{-1};

    while (choice != 0)
    {

        char arr_choice{0};

        std::cout << "С каким массивом вы собираетесь работать?:\n"
                     "1 - в массиве любые фигуры:\n"
                     "2 - в массиве только пятиугольники\n"
                     "3 - в массиве только шестиугольники\n"
                     "4 - в массиве только восьмиугольники" << std::endl;



        Array<std::shared_ptr<Figure<double>>> v1;
        Array<std::shared_ptr<Pentagon<double>>> v2;
//        Array<std::shared_ptr<Hexagon<double>>> v3;
//        Array<std::shared_ptr<Octagon<double>>> v4;

        std::cin >> arr_choice;

        switch (arr_choice)
        {
            case '1':
                choice = menu(v1);
                break;
            case '2':
                choice = menu(v2);
                break;
            case '3':
//              choice = menu(v3);
                break;
            case '4':
//              choice = menu(v4);
                break;
            default:
                std::cout << "Некорректный выбор" << std::endl;
        }
    }
    return 0;
}