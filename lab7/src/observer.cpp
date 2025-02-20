#include "../include/observer.h"
#include "../include/npc.h"
#include <iostream>

std::mutex ConsoleLogger::m_coutMutex;

void ConsoleLogger::onKill(NPC& killer, NPC& victim)
{
    std::lock_guard<std::mutex> lock(m_coutMutex);
    std::cout << "[LOG] " << killer.getType() << "("<<killer.getName()
              << ") убил "
              << victim.getType()<<"("<<victim.getName()
              << ")\n";
}
