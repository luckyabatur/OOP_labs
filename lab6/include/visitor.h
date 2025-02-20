#pragma once
#include "npc.h"


class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visitBear(Bear& bear, NPC& other) = 0;
    virtual void visitWerewolf(Werewolf& ww, NPC& other) = 0;
    virtual void visitRogue(Rogue& rogue, NPC& other) = 0;
};
