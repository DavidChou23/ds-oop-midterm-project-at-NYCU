#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
//#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
//#include <typeinfo>

using namespace std;

class Player;

class Item: public Object
{
private:
    string type; //weapon or shield
    int health,attack,defense,price;  //Buy Item price=price*2
public:
    Item();
    Item(string name, int health, int attack, int defense, int price , string type);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object*);
    virtual string getDescription();
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getPrice();
    string getType();
};

class Weapon: public Item{
    public:
        Weapon(string name, int health, int attack, int price);
        string getDescription();
};

class Shield: public Item{
    public:
        Shield(string name, int health, int defense, int price);
        string getDescription();
};

//does harm to monster(50%), recover health(50%), recover health(90%), prevent one attack(50%), recover MP(100%)
class Special: public Item{
    private:
        string discription;
    public:
        Special(string name, int health, int attack, int defense, int price, string discription);
        string getDescription();
        bool SpecialEffect(Player*);
};

#endif // ITEM_H_INCLUDED
