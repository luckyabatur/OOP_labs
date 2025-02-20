#include "../include/npc.h"
#include "../include/visitor.h"


void Bear::accept(Visitor& v, NPC& other)
{
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
