#include <iostream>
#include <string>
#include "../include/fixed_block_resource.h"
#include "../include/pmr_dlist.h"

struct MyData {
    int x;
    double y;
    MyData(int xx = 0, double yy = 0.0) : x(xx), y(yy) {}
    friend std::ostream& operator<<(std::ostream& os, const MyData& md)
    {
        return os << "[x=" << md.x << ", y=" << md.y << "]";
    }
};

int main()
{
    FixedBlockResource myResource(1024);

    PmrDList<int>    dlistInt(&myResource);
    PmrDList<MyData> dlistData(&myResource);

    bool useInt = true;

    char choice = '0';
    while (choice != '7')
    {
        std::cout << "\nВыберите действие:\n"
                     "1 - Переключить тип (int / MyData)\n"
                     "2 - Добавить элемент\n"
                     "3 - Вывести все элементы\n"
                     "4 - Очистить контейнер\n"
                     "5 - Пересоздать FixedBlockResource (очистка памяти)\n"
                     "6 - Увеличить \"блок\" памяти\n"
                     "7 - Выход\n"
                     "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
            case '1':
            {
                useInt = !useInt;
                std::cout << (useInt ? "Тип: int.\n" : "Тип: MyData.\n");
                break;
            }
            case '2':
            {
                if (useInt)
                {
                    std::cout << "Введите int: ";
                    int val{};
                    std::cin >> val;
                    dlistInt.push_back(val);
                }
                else
                {
                    std::cout << "Введите MyData (int x, double y): ";
                    int xx{};
                    double yy{};
                    std::cin >> xx >> yy;
                    dlistData.push_back(MyData(xx, yy));
                }
                break;
            }
            case '3':
            {
                if (useInt)
                {
                    std::cout << "Содержимое dlistInt:\n";
                    for (auto it = dlistInt.begin(); it != dlistInt.end(); ++it)
                        std::cout << *it << ' ';
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "Содержимое dlistData:\n";
                    for (auto it = dlistData.begin(); it != dlistData.end(); ++it)
                        std::cout << *it << ' ';
                    std::cout << std::endl;
                }
                break;
            }
            case '4':
            {
                if (useInt)
                {
                    dlistInt.clear();
                    std::cout << "dlistInt: очищен.\n";
                }
                else
                {
                    dlistData.clear();
                    std::cout << "dlistData: очищен.\n";
                }
                break;
            }
            case '5':
            {
                std::cout << "Пересоздаём ресурс (размер = 1024)\n";
                dlistInt.clear();
                dlistData.clear();

                dlistInt.~PmrDList<int>();
                dlistData.~PmrDList<MyData>();

                myResource.~FixedBlockResource();
                new(&myResource) FixedBlockResource(1024);

                new(&dlistInt)    PmrDList<int>(&myResource);
                new(&dlistData)   PmrDList<MyData>(&myResource);

                std::cout << "Готово.\n";
                break;
            }
            case '6':
            {
                std::cout << "Увеличим блок до 2048\n";
                dlistInt.clear();
                dlistData.clear();

                dlistInt.~PmrDList<int>();
                dlistData.~PmrDList<MyData>();

                myResource.~FixedBlockResource();
                new(&myResource) FixedBlockResource(2048);

                new(&dlistInt)  PmrDList<int>(&myResource);
                new(&dlistData) PmrDList<MyData>(&myResource);

                std::cout << "Готово.\n";
                break;
            }
            case '7':
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Некорректный выбор.\n";
                break;
        }
    }

    return 0;
}
