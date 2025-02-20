#include "../include/visitor.h"
#include "../include/observer.h"
#include <vector>
#include <string>

class BattleVisitor : public Visitor
{
public:
    BattleVisitor(std::vector<Observer*>& observers)
            : m_observers(observers) {}

    void visitBear(Bear& bear, NPC& other) override
    {
        if (other.getType() == "Werewolf")
        {
            notifyKill(bear, other);
        }
    }

    void visitWerewolf(Werewolf& ww, NPC& other) override
    {
        if (other.getType() == "Rogue")
        {
            notifyKill(ww, other);
        }
    }

    void visitRogue(Rogue& rogue, NPC& other) override
    {
        if (other.getType() == "Bear")
        {
            notifyKill(rogue, other);
        }
    }

private:
    std::vector<Observer*>& m_observers;

    void notifyKill(NPC& killer, NPC& victim)
    {
        for (auto obs : m_observers)
        {
            obs->onKill(killer, victim);
        }
    }
};