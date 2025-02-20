#pragma once
#include "npc.h"

// Интерфейс наблюдателя
class Observer
{
public:
    virtual ~Observer() = default;
    // Сообщить, что killer убил victim
    virtual void onKill(NPC& killer, NPC& victim) = 0;
};

// Два Observer'а — в файл, на экран.

// 1) Вывод в лог (log.txt)
class FileLogger : public Observer
{
public:
    FileLogger(const std::string& filename);
    void onKill(NPC& killer, NPC& victim) override;
private:
    std::string m_filename;
};

// 2) Вывод в консоль
class ConsoleLogger : public Observer
{
public:
    void onKill(NPC& killer, NPC& victim) override;
};
