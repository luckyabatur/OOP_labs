#include "../include/game.h"
#include "../include/visitor.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>

// Локальный класс BattleVisitor для double-dispatch
class BattleVisitor : public Visitor
{
public:
    BattleVisitor(NPC* attacker, NPC* defender, Game* game)
            : m_attacker(attacker), m_defender(defender), m_game(game) {}

    void visitBear(Bear& bear, NPC& other) override
    {
        // Bear убивает Werewolf
        if (other.getType()=="Werewolf") {
            m_game->doKill(bear, other);
        }
    }
    void visitWerewolf(Werewolf& ww, NPC& other) override
    {
        // Werewolf убивает Rogue
        if (other.getType()=="Rogue") {
            m_game->doKill(ww, other);
        }
    }
    void visitRogue(Rogue& rg, NPC& other) override
    {
        // Rogue убивает Bear
        if (other.getType()=="Bear") {
            m_game->doKill(rg, other);
        }
    }

private:
    NPC* m_attacker;
    NPC* m_defender;
    Game* m_game;
};

static double distanceBetween(const NPC& a, const NPC& b)
{
    double dx = a.getX()-b.getX();
    double dy = a.getY()-b.getY();
    return std::sqrt(dx*dx + dy*dy);
}

Game::Game()
{
}

Game::~Game()
{
    // Остановка потоков
    m_stop.store(true);
    if (m_moveThread.joinable()) {
        m_moveThread.join();
    }
    {
        std::unique_lock<std::mutex> lk(m_battleMutex);
        m_battleCV.notify_all();
    }
    if (m_battleThread.joinable()) {
        m_battleThread.join();
    }
    if (m_printThread.joinable()) {
        m_printThread.join();
    }
}

void Game::addObserver(Observer* obs)
{
    m_observers.push_back(obs);
}

void Game::addNPC(std::unique_ptr<NPC> npc)
{
    std::unique_lock lock(m_npcMutex);
    m_npcs.push_back(std::move(npc));
}

void Game::run()
{
    // Запуск потоков
    m_moveThread   = std::thread(&Game::movementThreadFunc, this);
    m_battleThread = std::thread(&Game::battleThreadFunc, this);
    m_printThread  = std::thread(&Game::printingThreadFunc, this);

    // Ждём 30с
    std::this_thread::sleep_for(std::chrono::seconds(30));
    m_stop.store(true);

    if (m_moveThread.joinable())  m_moveThread.join();
    {
        std::unique_lock<std::mutex> lk(m_battleMutex);
        m_battleCV.notify_all();
    }
    if (m_battleThread.joinable()) m_battleThread.join();
    if (m_printThread.joinable())  m_printThread.join();

    // По окончании печатаем итоговый список выживших
    {
        std::shared_lock lock(m_npcMutex);
        std::cout << "\n*** 30 секунд прошло. Итоговый список выживших: ***\n";
        for (auto &npc : m_npcs) {
            if (npc && !npc->isDead()) {
                std::cout << npc->getType()
                          << "("<<npc->getName()<<") at ["
                          << npc->getX()<<", "<<npc->getY()<<"]\n";
            }
        }
    }
    std::cout << "*** Конец. ***\n";
}

void Game::doKill(NPC& killer, NPC& victim)
{
    victim.kill();
    // Уведомляем наблюдателей
    for (auto obs : m_observers) {
        obs->onKill(killer, victim);
    }
}

void Game::pushBattleTask(NPC* a, NPC* b)
{
    {
        std::unique_lock<std::mutex> lk(m_battleMutex);
        m_battleQueue.push({a,b});
    }
    m_battleCV.notify_one();
}

// Поток движения
void Game::movementThreadFunc()
{
    using namespace std::chrono_literals;
    while(!m_stop.load())
    {
        {
            std::unique_lock lock(m_npcMutex);

            // Движение
            for (auto &npc : m_npcs) {
                if (npc && !npc->isDead()) {
                    npc->moveRandom();
                }
            }
            // Проверка пар
            for (size_t i=0; i<m_npcs.size(); i++){
                NPC* a = m_npcs[i].get();
                if (!a || a->isDead()) continue;
                for (size_t j=i+1; j<m_npcs.size(); j++){
                    NPC* b = m_npcs[j].get();
                    if (!b || b->isDead()) continue;

                    double dist = distanceBetween(*a, *b);
                    if (dist <= a->getKillDistance()
                        || dist <= b->getKillDistance())
                    {
                        // Добавляем задачу боя
                        pushBattleTask(a,b);
                    }
                }
            }
        }
        std::this_thread::sleep_for(500ms);
    }
}

// Поток боя
void Game::battleThreadFunc()
{
    while(!m_stop.load())
    {
        BattleTask task;
        {
            std::unique_lock<std::mutex> lk(m_battleMutex);
            if (m_battleQueue.empty()) {
                // ждем
                m_battleCV.wait(lk, [this]{
                    return m_stop.load() || !m_battleQueue.empty();
                });
                if (m_stop.load()) break;
            }
            if (m_battleQueue.empty()) continue;

            task = m_battleQueue.front();
            m_battleQueue.pop();
        }
        if (!task.attacker || task.attacker->isDead()) continue;
        if (!task.defender || task.defender->isDead()) continue;

        // Бросаем d6
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dice(1,6);

        int attackRoll  = dice(gen);
        int defenseRoll = dice(gen);

        // Если attack >= defense => attacker побеждает
        if (attackRoll >= defenseRoll) {
            BattleVisitor visitor(task.attacker, task.defender, this);
            task.attacker->accept(visitor, *task.defender);
        }
        else {
            // defense > attack => defender убивает attacker
            BattleVisitor visitor(task.defender, task.attacker, this);
            task.defender->accept(visitor, *task.attacker);
        }
    }
}

// Поток вывода
void Game::printingThreadFunc()
{
    using namespace std::chrono_literals;
    while(!m_stop.load())
    {
        {
            std::shared_lock lock(m_npcMutex);
            std::cout << "\n=== Состояние карты ===\n";
            for (auto &npc : m_npcs) {
                if (npc && !npc->isDead()) {
                    std::cout << npc->getType()
                              << "("<<npc->getName()<<") at ["
                              << npc->getX()<<", "<<npc->getY()<<"]\n";
                }
            }
        }
        std::this_thread::sleep_for(2s);
    }
}
