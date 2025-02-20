#include <iostream>
#include <string>
#include <memory>
#include "../include/game.h"
#include "../include/observer.h"
#include "../include/factory.h"

int main()
{
    Game game;

    // Создаём двух наблюдателей:
    // 1) FileLogger -> "log.txt"
    // 2) ConsoleLogger
    FileLogger fileObs("log.txt");
    ConsoleLogger consoleObs;

    // Регистрируем их
    game.addObserver(&fileObs);
    game.addObserver(&consoleObs);

    char choice = '0';
    while (choice != '6')
    {
        std::cout << "\nМеню:\n"
                  << "1 - Добавить NPC\n"
                  << "2 - Печать списка\n"
                  << "3 - Сохранить в файл\n"
                  << "4 - Загрузить из файла\n"
                  << "5 - Запустить бой\n"
                  << "6 - Выход\n"
                  << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
            case '1':
            {
                std::cout << "Введите тип (Bear, Werewolf, Rogue), имя, x, y:\n";
                std::string type, name;
                double x{}, y{};
                std::cin >> type >> name >> x >> y;
                // проверим границы 0..500
                if (x < 0) x=0; if (x>500) x=500;
                if (y < 0) y=0; if (y>500) y=500;

                try {
                    auto npc = NPCFactory::createNPC(type, name, x, y);
                    game.addNPC(std::move(npc));
                } catch(std::exception& ex) {
                    std::cout << "Ошибка: " << ex.what() << "\n";
                }
                break;
            }
            case '2':
            {
                game.printAll();
                break;
            }
            case '3':
            {
                std::cout << "Введите имя файла для сохранения: ";
                std::string fname;
                std::cin >> fname;
                try {
                    game.save(fname);
                    std::cout << "Сохранено.\n";
                } catch(std::exception& ex) {
                    std::cout << "Ошибка: " << ex.what() << "\n";
                }
                break;
            }
            case '4':
            {
                std::cout << "Введите имя файла для загрузки: ";
                std::string fname;
                std::cin >> fname;
                try {
                    game.load(fname);
                    std::cout << "Загружено.\n";
                } catch(std::exception& ex) {
                    std::cout << "Ошибка: " << ex.what() << "\n";
                }
                break;
            }
            case '5':
            {
                std::cout << "Введите дистанцию боя: ";
                double rng{};
                std::cin >> rng;
                game.battle(rng);
                std::cout << "Бой завершён.\n";
                break;
            }
            case '6':
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Некорректный выбор.\n";
                break;
        }
    }

    return 0;
}
