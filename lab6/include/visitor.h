#pragma once
#include "npc.h"

// Интерфейс "Visitor", который объявляет методы для каждой комбинации:
class Visitor
{
public:
    virtual ~Visitor() = default;

    // Каждая "visitXxx" принимает конкретный класс + второй NPC
    // и решает, кто кого убьёт (если вообще).
    virtual void visitBear(Bear& bear, NPC& other) = 0;
    virtual void visitWerewolf(Werewolf& ww, NPC& other) = 0;
    virtual void visitRogue(Rogue& rogue, NPC& other) = 0;
};

// Кто с кем дерётся: вариант 5
//   Оборотень (Werewolf) убивает Разбойника (Rogue)
//   Разбойник (Rogue) убивает Медведя (Bear)
//   Медведь (Bear) убивает Оборотня (Werewolf)
