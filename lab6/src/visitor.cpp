#include "../include/visitor.h"
#include "../include/npc.h"
#include "../include/observer.h"
#include <iostream>
#include <vector>
#include <string>

// Тут не хватает реализации Visitor,
// мы хотим «двойную диспетчеризацию».
// Чаще создают конкретный класс, напр. `BattleVisitor`:

class BattleVisitor : public Visitor
{
public:
    // Конструктор принимает вектор/список Observer'ов
    // чтобы оповещать о событиях (убийствах).
    BattleVisitor(std::vector<Observer*>& observers)
            : m_observers(observers) {}

    // Bear vs other
    void visitBear(Bear& bear, NPC& other) override
    {
        // Bear убивает Werewolf
        if (other.getType() == "Werewolf") {
            notifyKill(bear, other);
        }
        // Иначе Bear никого не трогает
    }

    // Werewolf vs other
    void visitWerewolf(Werewolf& ww, NPC& other) override
    {
        // Werewolf убивает Rogue
        if (other.getType() == "Rogue") {
            notifyKill(ww, other);
        }
    }

    // Rogue vs other
    void visitRogue(Rogue& rogue, NPC& other) override
    {
        // Rogue убивает Bear
        if (other.getType() == "Bear") {
            notifyKill(rogue, other);
        }
    }

private:
    std::vector<Observer*>& m_observers;

    void notifyKill(NPC& killer, NPC& victim)
    {
        // Обновляем всех наблюдателей
        for (auto obs : m_observers) {
            obs->onKill(killer, victim);
        }
        // "Удалить" victim из мира - см. где это делать - см. Game.cpp
        // Или пометить victim как "dead"
        // Но в данном примере Visitor не удаляет сам — делаем это в Game.
    }
};

// Чтобы не плодить cpp/h- пару, часто BattleVisitor объявляют в visitor.h.
// Здесь для наглядности вынесено.
