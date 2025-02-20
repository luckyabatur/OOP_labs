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

    void addObserver(Observer* obs);

    void addNPC(std::unique_ptr<NPC> npc);

    void save(const std::string& filename);
    void load(const std::string& filename);

    void printAll();

    void battle(double range);

private:
    std::vector<std::unique_ptr<NPC>> m_npcs;
    std::vector<Observer*> m_observers;
};
