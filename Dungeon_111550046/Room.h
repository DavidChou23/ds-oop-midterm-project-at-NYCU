#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
//#include <string>
//#include <vector>
#include "Object.h"

using namespace std;

class Room
{
private:
    Room* upRoom=nullptr;
    Room* downRoom=nullptr;
    Room* leftRoom=nullptr;
    Room* rightRoom=nullptr;
    int index;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(int num, vector<Object*> obj);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/
    vector<string> getValidDirection(); /*return a vector of valid way can move*/
    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIndex(int);
    void setObjects(vector<Object*>);
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
};

#endif // ROOM_H_INCLUDED
