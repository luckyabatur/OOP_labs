#pragma once

#include "Figure.h"
#include "Array.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"

template <typename T>
concept OneTypeFig = std::is_same_v<T, Pentagon<typename T::value_type>> || std::is_same_v<T, Hexagon<typename T::value_type>> || std::is_same_v<T, Octagon<typename T::value_type>>;


template <typename T>
concept Fig = std::is_same_v<T, Figure<typename T::value_type>> || std::is_same_v<T, Pentagon<typename T::value_type>> || std::is_same_v<T, Hexagon<typename T::value_type>> || std::is_same_v<T, Octagon<typename T::value_type>>;



template <typename T>
void input(Array<std::shared_ptr<Figure<T>>>& v)
{

    if (!v.empty())
        return;

    while (true)
    {
        std::cin.ignore(100000, '\n');
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
                fptr = std::make_shared<Pentagon<T>>();
                break;
            case '2':
                fptr = std::make_shared<Hexagon<T>>();
                break;
            case '3':
                fptr = std::make_shared<Octagon<T>>();
                break;
            default:
                return;
        }

        std::cin.ignore(100000, '\n');
        std::cout << "Введие координаты в виде: 0 1 2 3 4 5 6 7 8 9 (пример для пятиугольника)\n"
                     "Чтобы функция проверки на правильный многоугольник не отбраковала фигуру, вводите достаточно точные значения\n"
                     "Для корректных действий с вещественными числами вводите фигуры с радиусом описанной окружности от ~5 до ~25" << std::endl;


        try
        {
            std::cin >> *fptr;
            v.push_back(fptr);
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        std::cout << "Хотите продолжить ввод?\n"
                     "1 - да\n"
                     "другое значение - нет" << std::endl;

        choice = '1';

        std::cin >> choice;

        if (choice != '1')
            return;
    }
}

template <Fig T>
void output(Array<std::shared_ptr<T>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (int i{0}; i < v.get_size(); i++)
        std::cout << *v[i] << std::endl;
}

template <Fig T>
void print_square(Array<std::shared_ptr<T>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (int i{0}; i < v.get_size(); i++)
        std::cout << (double) *v[i] << std::endl;

}

template <Fig T>
void print_geomc(Array<std::shared_ptr<T>>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (int i{0}; i < v.get_size(); i++)
        std::cout << v[i]->geomc() << std::endl;
}

template <Fig T>
double square_sum(Array<std::shared_ptr<T>>& v)
{
    double sum{0};
    for (int i{0}; i < v.get_size(); i++)
        sum += (double) *v[i];

    return sum;
}


template <OneTypeFig T>
void input(Array<std::shared_ptr<T>>& v)
{
    if (!v.empty())
        return;

    while(true)
    {
        std::shared_ptr<T> fptr = std::make_shared<T>();
        int point_count = T::point_count;

        switch (point_count)
        {
            case 5:
                std::cout << "Введите координаты пятиугольника" << std::endl;
                break;
            case 6:
                std::cout << "Введите координаты шестиугольника" << std::endl;
                break;
            case 8:
                std::cout << "Введите координаты восьмиугольника" << std::endl;
                break;
        }
        try
        {
            std::cin >> *fptr;
            v.push_back(fptr);
        }
        catch (std::invalid_argument& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        std::cout << "Хотите продолжить ввод?\n"
                     "1 - да\n"
                     "другое значение - нет" << std::endl;
        char choice{'1'};
        std::cin >> choice;

        if (choice != '1')
            return;

    }
}



