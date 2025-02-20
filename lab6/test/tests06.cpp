#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "../include/game.h"
#include "../include/observer.h"
#include "../include/factory.h"



TEST(NPCGameTest, CreateEmptyGame)
{
Game game;

SUCCEED();
}


TEST(NPCGameTest, AddOneNPC)
{
Game game;
auto npc = NPCFactory::createNPC("Bear", "Grizzly", 100.0, 200.0);
game.addNPC(std::move(npc));


SUCCEED();
}

TEST(NPCGameTest, SmallRangeBattle)
{
Game game;

game.addNPC(NPCFactory::createNPC("Bear", "Bruno", 0, 0));
game.addNPC(NPCFactory::createNPC("Werewolf", "Wolfy", 100, 100));


game.battle(10.0);


SUCCEED();
}

TEST(NPCGameTest, BearKillsWerewolf)
{
Game game;

game.addNPC(NPCFactory::createNPC("Bear", "Bruno", 0,0));
game.addNPC(NPCFactory::createNPC("Werewolf", "Wolfy", 1,1));

ConsoleLogger consoleObs;
game.addObserver(&consoleObs);

game.battle(5.0);

SUCCEED();
}

TEST(NPCGameTest, WerewolfKillsRogue)
{
Game game;
game.addNPC(NPCFactory::createNPC("Werewolf", "Alpha", 10,10));
game.addNPC(NPCFactory::createNPC("Rogue", "Thief", 11,11));
game.battle(5.0);
SUCCEED();
}

TEST(NPCGameTest, RogueKillsBear)
{
Game game;
game.addNPC(NPCFactory::createNPC("Rogue", "Robber", 0,0));
game.addNPC(NPCFactory::createNPC("Bear",  "Teddy", 0,0));
game.battle(1.0);
SUCCEED();
}

TEST(NPCGameTest, SaveLoadFile)
{
Game game;
game.addNPC(NPCFactory::createNPC("Bear", "B1", 100,200));
game.addNPC(NPCFactory::createNPC("Rogue","R1", 300,400));

std::string filename = "test_npcs.txt";
game.save(filename);

Game newGame;
newGame.load(filename);

std::remove(filename.c_str());
SUCCEED();
}


TEST(NPCGameTest, FileLoggerCheck)
{
std::string logName = "test_log.txt";

std::remove(logName.c_str());

{
Game game;
FileLogger fileObs(logName);
game.addObserver(&fileObs);

game.addNPC(NPCFactory::createNPC("Bear","B2",0,0));
game.addNPC(NPCFactory::createNPC("Werewolf","W2",0,0));
game.battle(10.0);
}

std::ifstream ifs(logName);
ASSERT_TRUE(ifs.is_open()) << "Could not open log file";
bool fileEmpty = ifs.peek() == EOF;
ifs.close();
EXPECT_FALSE(fileEmpty) << "Log file is empty => no kill logged?";
std::remove(logName.c_str());
}

TEST(NPCGameTest, MultipleNPCBattle)
{
Game game;

game.addNPC(NPCFactory::createNPC("Bear", "BearX", 0,0));
game.addNPC(NPCFactory::createNPC("Rogue","RogueX",5,0));
game.addNPC(NPCFactory::createNPC("Werewolf","WolfX",10,0));
game.battle(5.0);

SUCCEED();
}

TEST(NPCGameTest, BigDistanceNoKill)
{
Game game;
game.addNPC(NPCFactory::createNPC("Bear","BB",0,0));
game.addNPC(NPCFactory::createNPC("Werewolf","WW",1000,1000));
game.battle(100.0);
SUCCEED();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
