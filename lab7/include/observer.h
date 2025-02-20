#pragma once
#include <mutex>

class NPC;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onKill(NPC& killer, NPC& victim) = 0;
};

// Пример: ConsoleLogger
class ConsoleLogger : public Observer
{
public:
    void onKill(NPC& killer, NPC& victim) override;

private:
    static std::mutex m_coutMutex;
};
