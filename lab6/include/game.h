#pragma once
#include <vector>
#include <memory>
#include <string>
#include "npc.h"
#include "observer.h"

class Game
{
public:
    Game();
    ~Game();

    // Добавить наблюдателя
    void addObserver(Observer* obs);

    // Добавить нового NPC (уже созданного)
    void addNPC(std::unique_ptr<NPC> npc);

    // Сохранить/загрузить
    void save(const std::string& filename);
    void load(const std::string& filename);

    // Печать NPC
    void printAll();

    // Запуск боевого режима
    //   range - радиус, в пределах которого NPC могут драться
    void battle(double range);

private:
    // Внутренний метод "убить NPC"
    void removeNPC(NPC* victim);

private:
    std::vector<std::unique_ptr<NPC>> m_npcs;
    std::vector<Observer*> m_observers;
};
