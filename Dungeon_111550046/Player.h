#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"

using namespace std;

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item*> inventory;
    //array of equipment, length = 3
    Item* equipment[3];
    int money;
    int exp;
    int level;
    int magicPoint;
    int MaxMagicPoint;
    int MaxLevel;
    void showCurrentEquipment();
    int getEquipmentAttack();
    int getEquipmentDefense();
public:
    Player();
    Player(string name, int maxHealth, int Attack, int Defense, int money, int exp, int MaxMagicPoint, int MaxLevel);
    void addItem(Item*);
    void changeRoom(Room* next);  //movement list
    void levelUp();
    /*sellItem only be called when money is not enough*/
    /*when called list all Items and their price ask what to sell*/
    /*loop until player quit this function*/
    bool sellItem();
    /*exchangeMagicPoint can only be called when magicPoint is not enough*/
    /*when called check MagicPoint and MaxMagicPoint*/
    /*don't let magicPoint>MaxMagicPoint*/
    /*ask player how much money to spend for magicPoint (1 money = 1 magicPoint)*/
    bool exchangeMagicPoint();
    void showStatus(Object* object);
    void equipItem();

    /* Virtual function that you need to complete   */
    /* In Player, this function should print        */
    /* action list.                                  */
    bool triggerEvent(Object* object);

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setMoney(int);
    void setExp(int);
    void setLevel(int);
    void setMagicPoint(int);
    void setMaxMagicPoint(int);
    void setMaxLevel(int);
    void setEquipment(Item*);  //only for equipment[2]
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    Item* getEquipment();
    int getMoney();
    int getExp();
    int getLevel();
    int getMagicPoint();
    int getMaxMagicPoint();
    int getMaxLevel();

};

#endif // PLAYER_H_INCLUDED
