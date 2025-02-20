#include "../include/npc.h"
#include "../include/visitor.h"

// Реализация accept(...), где происходит двойная диспетчеризация

void Bear::accept(Visitor& v, NPC& other)
{
    // "this" = Bear, "other" - неизвестен
    v.visitBear(*this, other);
}

void Werewolf::accept(Visitor& v, NPC& other)
{
    v.visitWerewolf(*this, other);
}

void Rogue::accept(Visitor& v, NPC& other)
{
    v.visitRogue(*this, other);
}
