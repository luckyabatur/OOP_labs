#pragma once

class Bear;
class Werewolf;
class Rogue;
class NPC;

// Visitor (двойная диспетчеризация)
class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visitBear(Bear& bear, NPC& other) = 0;
    virtual void visitWerewolf(Werewolf& ww, NPC& other) = 0;
    virtual void visitRogue(Rogue& rg, NPC& other) = 0;
};
