#pragma once
#include <string>
#include <vector>
#include <memory>
#include "npc.h"


class NPCFactory
{
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type,
                                          const std::string& name,
                                          double x, double y);


    static void saveToFile(const std::string& filename,
                           const std::vector<std::unique_ptr<NPC>>& npcs);


    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename);
};
