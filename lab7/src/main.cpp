#include "../include/game.h"
#include "../include/observer.h"
#include <iostream>
#include <random>
#include <ctime>

int main()
{
    // Создаём Game
    Game game;
    // Добавляем консольный логгер
    ConsoleLogger clog;
    game.addObserver(&clog);

    // Создаём 50 случайных NPC
    // Тип: Bear/Werewolf/Rogue
    // Координаты: uniform [0..100]
    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> distXY(0.0, 100.0);
    std::uniform_int_distribution<int> distType(0,2); // 0->Bear, 1->Werewolf, 2->Rogue

    for (int i=0; i<50; i++){
        double x = distXY(gen);
        double y = distXY(gen);
        int type = distType(gen);

        if (type==0) {
            game.addNPC(std::make_unique<Bear>("Bear"+std::to_string(i), x,y));
        }
        else if (type==1) {
            game.addNPC(std::make_unique<Werewolf>("Wolf"+std::to_string(i), x,y));
        }
        else {
            game.addNPC(std::make_unique<Rogue>("Rogue"+std::to_string(i), x,y));
        }
    }

    // Запуск
    game.run(); // 30c

    // По завершении run() напечатает survivors
    return 0;
}
