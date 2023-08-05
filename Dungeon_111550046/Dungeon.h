#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

//#include <string>
//#include <exception>
#include <iostream>
#include <vector>
#include <stdlib.h>
//#include <cctype>
#include "Monster.h"
#include "Player.h"
#include "NPC.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Dungeon{
private:
    Player* player;
    Boss* boss;
    int stage=1;
    int replayTimes=0;
    vector<Room*> rooms;
    vector<Item*> defaultItems;
    vector<Player*> players;
    vector<Monster*> monsters;
    vector<NPC*> npcs;
    vector<Item*> items;
    string bossName[5];
    vector<Boss*> bosses;
    void initPlayers();
    void initDefaultItems();
    void initMonsters();
    void initNPCs();
    void initBoss();
    void setBoss();
    void nextStage();

public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    void handleMovement();

    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    int checkGameLogic();

    /* Deal with the whole game process */
    void runDungeon();
};


#endif // DUNGEON_H_INCLUDED
