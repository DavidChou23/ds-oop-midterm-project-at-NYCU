#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
//#include "Item.h"
//#include "Object.h"

using namespace std;

class Player;
class Special;

class Monster: public GameCharacter
{
private:
    int dropCoin;
    int cd;
    int cdCount;
    int getEquimentAttack();
    int getEquimentDefense();
protected: //for boss
    int dropExp;
    int dropItemNum=1;
    vector<Object*> dropItem;
public:
    Monster();
    Monster(string name,int maxHealth,int Attack,int Defense,int dropCoin, int dropExp, int dropItemNum, int cd);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    /* You need to implement the combat system      */
    /* in this function.                            */
    /* return true if the player is alive after     */
    bool triggerEvent(Object*);
    virtual bool getReward(Player* player);
    //setter&getter
    int getDropCoin();
    int getDropExp();
    int getDropItemNum();
    vector<Object*> getDropItem();
};

class Boss: public Monster
{
    private:
        int stage;
        static vector<Special*> special;
    public:
        Boss(string name,int maxHealth,int Attack,int Defense,int dropCoin, int dropExp, int dropItemNum, int cd,int stage);
        bool getReward(Player*);
};

#endif // ENEMY_H_INCLUDED
