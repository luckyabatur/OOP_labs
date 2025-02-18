#pragma once

#include "Figure.h"
#include "Array.h"
#include "Pentagon.h"
//#include "Hexagon.h"
//#include "Octagon.h"

template <typename T>
void input(Array<std::shared_ptr<Figure<T>>>& v)
{
    if (!v.empty())
        return;

    while(true)
    {
        std::cout << "Выберите фигуру:\n"

                     "1 - пятиугольник\n"
                     "2 - шестиугольник\n"
                     "3 - восьмиугольник\n\n"
                     "Чтобы завершить ввод, введите любое другое значение" << std::endl;

        char choice{0};
        std::cin >> choice;

        std::shared_ptr<Figure<T>> fptr{nullptr};

        switch (choice)
        {
            case '1':
                fptr = new Pentagon;
                break;
            case '2':
                fptr = new Hexagon;
                break;
            case '3':
                fptr = new Octagon;
                break;
            default:
                return;
        }

        std::cin.ignore(100000, '\n');
        std::cout << "Введие координаты в виде: 0 1 2 3 4 5 6 7 8 9 (пример для пятиугольника)\n"
                     "Чтобы функция проверки на правильный пятиугольник не отбраковала фигуру, вводите достаточно точные значения\n"
                     "Для корректных действий с вещественными числами вводите фигуры с радиусом описанной окружности от ~5 до ~25" << std::endl;
        std::cin >> *fptr;

        v.push_back(fptr);
    }
}

template <typename  T>
void output(Array<std::shared_ptr<T>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (auto &fptr: v)
        std::cout << *fptr << std::endl;
}

template <typename  T>
void print_square(Array<std::shared_ptr<Figure<T>>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (Figure* &fptr: v)
        std::cout << (double)*fptr << std::endl;

}

template <typename  T>
void print_geomc(Array<std::shared_ptr<Figure<T>>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (auto &fptr: v)
        std::cout << fptr->geomc() << std::endl;
}

template <typename  T>
double square_sum(Array<std::shared_ptr<Figure<T>>>& v)
{
    double sum{0};
    for (auto &fptr: v)
        sum += (double)*fptr;

    return sum;
}

//bool del(std::vector<Figure*>& v, int index)
//{
//    if (index < 0 || index >= v.size())
//        return false;
//
//    delete v[index];
//    v.erase(v.begin()+index);
//    return true;
//}
