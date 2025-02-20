#include "../include/observer.h"
#include <fstream>
#include <iostream>

FileLogger::FileLogger(const std::string& filename)
        : m_filename(filename)
{
}

void FileLogger::onKill(NPC& killer, NPC& victim)
{
    std::ofstream ofs(m_filename, std::ios::app);
    if (ofs.is_open()) {
        ofs << killer.getType() << "(" << killer.getName() << ") "
            << "kills "
            << victim.getType() << "(" << victim.getName() << ")\n";
    }
}

void ConsoleLogger::onKill(NPC& killer, NPC& victim)
{
    std::cout << killer.getType() << "(" << killer.getName() << ") "
              << "убивает "
              << victim.getType() << "(" << victim.getName() << ")\n";
}
