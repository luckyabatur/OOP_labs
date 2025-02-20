#include "../include/npc.h"
#include "../include/visitor.h"
#include <random>
#include <ctime>
#include <cmath>
#include <thread>

static std::mt19937& rng()
{
    // Каждый поток получает свой thread_local mt19937
    static thread_local std::mt19937 gen(
            (unsigned)std::time(nullptr)
            ^ std::hash<std::thread::id>{}(std::this_thread::get_id())
    );
    return gen;
}

void NPC::moveRandom()
{
    if (m_dead) return; // мёртвый не двигается

    double dist = getMoveDistance();
    if (dist < 0.001) return;

    std::uniform_real_distribution<double> angleDist(0.0, 2.0 * M_PI);
    double angle = angleDist(rng());
    double dx = dist * std::cos(angle);
    double dy = dist * std::sin(angle);

    m_x += dx;
    m_y += dy;

    // ограничим [0..100]
    if (m_x<0.0)   m_x=0.0;
    if (m_x>100.0) m_x=100.0;
    if (m_y<0.0)   m_y=0.0;
    if (m_y>100.0) m_y=100.0;
}

// Bear
void Bear::accept(Visitor& v, NPC& other)
{
    v.visitBear(*this, other);
}

// Werewolf
void Werewolf::accept(Visitor& v, NPC& other)
{
    v.visitWerewolf(*this, other);
}

// Rogue
void Rogue::accept(Visitor& v, NPC& other)
{
    v.visitRogue(*this, other);
}
