#include "../include/factory.h"
#include <fstream>
#include <stdexcept>

#include <iostream>

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type,
                                           const std::string& name,
                                           double x, double y)
{
    if (type == "Bear")
    {
        return std::make_unique<Bear>(name, x, y);
    }
    else if (type == "Werewolf")
    {
        return std::make_unique<Werewolf>(name, x, y);
    }
    else if (type == "Rogue")
    {
        return std::make_unique<Rogue>(name, x, y);
    }
    else
    {
        throw std::runtime_error("Unknown NPC type: " + type);
    }
}

void NPCFactory::saveToFile(const std::string& filename,
                            const std::vector<std::unique_ptr<NPC>>& npcs)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        throw std::runtime_error("Cannot open file for save: " + filename);
    }
    for (auto& ptr : npcs)
    {
        ofs << ptr->getType() << " "
            << ptr->getName() << " "
            << ptr->getX() << " "
            << ptr->getY() << "\n";
    }
}

std::vector<std::unique_ptr<NPC>>
NPCFactory::loadFromFile(const std::string& filename)
{
    std::vector<std::unique_ptr<NPC>> result;
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        throw std::runtime_error("Cannot open file for load: " + filename);
    }
    while (!ifs.eof())
    {
        std::string type, name;
        double x{}, y{};
        ifs >> type >> name >> x >> y;
        if (!ifs.fail())
        {
            auto npc = createNPC(type, name, x, y);
            result.push_back(std::move(npc));
        }
    }
    return result;
}
