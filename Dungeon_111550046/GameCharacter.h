#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    int currentHealth;
    int Attack;
    int Defense;
    int tmpDefense=0;
    int maxHealth;
    int attackmultiplier=1;
    int defmultiplier=1;
    virtual int getEquipmentAttack();  //for player
    virtual int getEquipmentDefense(); //for player

public:
    GameCharacter();
    GameCharacter(string name, int maxHealth, int Attack, int Defense);
    bool checkIsDead();
    int takeDamage(int);
    virtual bool triggerEvent(Object* object)=0;
    /* Set & Get function*/
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    void setTmpDefense(int);
    void setAttackMultiplier(int);
    void setDefMultiplier(int);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getTmpDefense();
};
#endif // GAMECHARACTER_H_INCLUDED
