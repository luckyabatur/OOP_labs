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

// Задача боя
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

    // Запуск на 30с + финальный вывод
    void run();

    // Вызывается Visitor'ом при убийстве
    void doKill(NPC& killer, NPC& victim);

private:
    // Потоки
    void movementThreadFunc();
    void battleThreadFunc();
    void printingThreadFunc();

    // Список NPC
    std::vector<std::unique_ptr<NPC>> m_npcs;
    std::shared_mutex m_npcMutex;

    // Observer
    std::vector<Observer*> m_observers;

    // Очередь боёв
    std::queue<BattleTask> m_battleQueue;
    std::mutex m_battleMutex;
    std::condition_variable m_battleCV;

    // Потоковые объекты
    std::atomic<bool> m_stop{false};
    std::thread m_moveThread;
    std::thread m_battleThread;
    std::thread m_printThread;

    void pushBattleTask(NPC* a, NPC* b);
};
