
#include "../include/array_func.h"

#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"

void input(std::vector<Figure*>& v)
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

        Figure *fptr{nullptr};

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
        std::cout << "Введие координаты в виде: 0 1 2 3 4 5 6 7 8 9 (пример для пятиугольника)" << std::endl;
        std::cin >> *fptr;

        v.push_back(fptr);
    }
}


void output(std::vector<Figure*>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (Figure *&fptr: v)
        std::cout << *fptr << std::endl;
}

void print_square(std::vector<Figure*>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (Figure* &fptr: v)
        std::cout << (double)*fptr << std::endl;

}

void print_geomc(std::vector<Figure*>& v)
{
    if (v.empty())
    {
        std::cout << "Фигур нет" << std::endl;
        return;
    }

    for (Figure *&fptr: v)
        std::cout << fptr->geomc() << std::endl;
}

double square_sum(std::vector<Figure*>& v)
{
    double sum{0};
    for (Figure* &fptr: v)
        sum += (double)*fptr;

    return sum;
}

bool del(std::vector<Figure*>& v, int index)
{
    if (index < 0 || index >= v.size())
        return false;

    delete v[index];
    v.erase(v.begin()+index);
    return true;
}
