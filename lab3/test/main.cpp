
#include "../include/array_func.h"



int main(void)
{
    char choice{0};
    
    while (choice != '7')
    {
        std::cout << "Вводите фигуры в вектор:" << std::endl;
        std::vector<Figure*> v;
        try
        {
            input(v);
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << ex.what() << std::endl;
            continue;
        }

        choice = 0;

        while (choice != '6' && choice != '7')
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
                    del(v, index);
                    break;
                case ('6'):
                    break;
                case ('7'):
                    break;
                default:
                    std::cout << "Сделайте корректный выбор" << std::endl;
            }
            std::cout << "------------------------------" << std::endl;
            std::cin.ignore(100000, '\n');
        }
        for (Figure* &fptr : v)
            delete fptr;
    }


    return 0;
}
