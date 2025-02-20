#pragma once
#include "npc.h"


class Observer
{
public:
    virtual ~Observer() = default;

    virtual void onKill(NPC& killer, NPC& victim) = 0;
};


class FileLogger : public Observer
{
public:
    FileLogger(const std::string& filename);
    void onKill(NPC& killer, NPC& victim) override;
private:
    std::string m_filename;
};

class ConsoleLogger : public Observer
{
public:
    void onKill(NPC& killer, NPC& victim) override;
};
