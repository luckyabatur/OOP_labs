#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include "npc.h"
#include "observer.h"

struct BattleTask
{
    NPC* attacker;
    NPC* defender;
};

class Game
{
public:
    Game();
    ~Game();

    void addObserver(Observer* obs);
    void addNPC(std::unique_ptr<NPC> npc);

    void run();

    void doKill(NPC& killer, NPC& victim);

private:
    void movementThreadFunc();
    void battleThreadFunc();
    void printingThreadFunc();

    std::vector<std::unique_ptr<NPC>> m_npcs;
    std::shared_mutex m_npcMutex;

    std::vector<Observer*> m_observers;

    std::queue<BattleTask> m_battleQueue;
    std::mutex m_battleMutex;
    std::condition_variable m_battleCV;

    std::atomic<bool> m_stop{false};
    std::thread m_moveThread;
    std::thread m_battleThread;
    std::thread m_printThread;

    void pushBattleTask(NPC* a, NPC* b);
};
