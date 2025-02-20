#include "../include/game.h"
#include "../include/factory.h"
#include "../include/visitor.h"
#include <cmath>
#include <iostream>
#include <algorithm>

// Объявляем конкретный класс "BattleVisitor" тут же (или используем из visitor.cpp).
// Ниже для удобства пропишем inline.

// Вспомогательная ф-ция: расстояние между 2 NPC
static double distanceNPC(const NPC& a, const NPC& b)
{
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::sqrt(dx*dx + dy*dy);
}

// Конкретный класс BattleVisitor, описанный в visitor.cpp, нужен.
// Скопируем упрощённую версию сюда, чтобы показать логику удаления.

class BattleVisitor : public Visitor
{
public:
    BattleVisitor(std::vector<Observer*>& observers,
                  std::vector<std::unique_ptr<NPC>>& npcsToMarkDead)
            : m_observers(observers)
            , m_npcsToMarkDead(npcsToMarkDead)
    {}

    void visitBear(Bear& bear, NPC& other) override
    {
        if (other.getType() == "Werewolf") {
            notifyKill(bear, other);
        }
    }
    void visitWerewolf(Werewolf& ww, NPC& other) override
    {
        if (other.getType() == "Rogue") {
            notifyKill(ww, other);
        }
    }
    void visitRogue(Rogue& rogue, NPC& other) override
    {
        if (other.getType() == "Bear") {
            notifyKill(rogue, other);
        }
    }

private:
    std::vector<Observer*>& m_observers;
    // Контейнер, где будем помечать victim
    std::vector<std::unique_ptr<NPC>>& m_npcsToMarkDead;

    void notifyKill(NPC& killer, NPC& victim)
    {
        for (auto obs : m_observers) {
            obs->onKill(killer, victim);
        }
        // Пометим victim для удаления
        // Не можем сразу удалить: идёт итерация.
        // Тогда используем "флаг" (например, nullptr)
        // или запомним указатель.
        // Здесь сделаем: ищем victim в m_npcsToMarkDead, зануляем
        for (auto &p : m_npcsToMarkDead) {
            if (p.get() == &victim) {
                p.reset(); // убираем из памяти
                break;
            }
        }
    }
};


Game::Game()
{
}

Game::~Game()
{
}

void Game::addObserver(Observer* obs)
{
    m_observers.push_back(obs);
}

void Game::addNPC(std::unique_ptr<NPC> npc)
{
    m_npcs.push_back(std::move(npc));
}

void Game::save(const std::string& filename)
{
    NPCFactory::saveToFile(filename, m_npcs);
}

void Game::load(const std::string& filename)
{
    auto loaded = NPCFactory::loadFromFile(filename);
    // Вставим в конец
    for (auto &npc : loaded) {
        m_npcs.push_back(std::move(npc));
    }
}

void Game::printAll()
{
    std::cout << "=== NPC List ===\n";
    for (auto &n : m_npcs) {
        if (n) {
            std::cout << n->getType()
                      << " \"" << n->getName() << "\""
                      << " (" << n->getX() << "," << n->getY() << ")\n";
        }
    }
}

void Game::battle(double range)
{
    // Идём попарно:
    //   - проверяем distance(npcs[i], npcs[j]) <= range?
    //   - если да, npc[i].accept(visitor, *npc[j]) + npc[j].accept(visitor, *npc[i])
    //     (т.к. бой идёт "каждый с каждым").
    // При этом удаляем "умерших" NPC, стараясь аккуратно.

    // Создаём BattleVisitor, которому дадим список observers, а также
    // ссылку на m_npcs (чтобы при убийстве victim удалять).
    BattleVisitor visitor(m_observers, m_npcs);

    // Двойной цикл
    for (size_t i = 0; i < m_npcs.size(); i++)
    {
        if (!m_npcs[i]) continue; // уже убит
        for (size_t j = i+1; j < m_npcs.size(); j++)
        {
            if (!m_npcs[j]) continue;
            double dist = distanceNPC(*m_npcs[i], *m_npcs[j]);
            if (dist <= range)
            {
                // Обоюдная атака
                m_npcs[i]->accept(visitor, *m_npcs[j]);
                // Могли убить m_npcs[j], проверим:
                if (!m_npcs[j]) // j убит
                    continue; // no second

                m_npcs[j]->accept(visitor, *m_npcs[i]);
                // возможно убит i
                if (!m_npcs[i])
                    break;
            }
        }
    }

    // Удаляем обнулённые
    m_npcs.erase(
            std::remove_if(m_npcs.begin(), m_npcs.end(),
                           [](std::unique_ptr<NPC>& ptr){
                               return (ptr == nullptr);
                           }),
            m_npcs.end()
    );
}

void Game::removeNPC(NPC* victim)
{
    // Не используется выше, т.к. мы делаем reset() напрямую.
}
