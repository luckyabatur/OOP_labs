#pragma once
#include <string>
#include <vector>
#include <memory>
#include "npc.h"

// Простая фабрика: умеет создавать NPC по строковому типу ("Bear", "Werewolf", "Rogue").
class NPCFactory
{
public:
    // Создать объект по типу
    static std::unique_ptr<NPC> createNPC(const std::string& type,
                                          const std::string& name,
                                          double x, double y);

    // Сохранение списка NPC в файл
    static void saveToFile(const std::string& filename,
                           const std::vector<std::unique_ptr<NPC>>& npcs);

    // Загрузка NPC из файла
    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename);
};
