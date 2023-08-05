#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <vector>
#include "GameCharacter.h"
#include "Item.h"

using namespace std;

class Item;

class NPC: public GameCharacter
{
private:
    string script;
    vector<Item*> commodity;
    int getEquipmentAttack();  //0
    int getEquipmentDefense();  //0
public:
    NPC();
    NPC(string name, string script, vector<Item*> commodity);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    vector<Item*> getCommodity();
};


#endif // NPC_H_INCLUDED
