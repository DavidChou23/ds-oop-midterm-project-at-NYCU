#include "Room.h"


Room::Room()
{
    //ctor
}

Room::Room(int num, vector<Object*> obj)
{
    this->index = num;
    this->objects = obj;
}

bool Room::popObject(Object* obj)
{
    for(int i=0; i<objects.size(); i++)
    {
        if(objects[i] == obj)
        {
            objects.erase(objects.begin()+i);
            return true;
        }
    }
    return false;
}

vector<string> Room::getValidDirection()
{
    vector<string> validDirection;
    if(upRoom != nullptr)
        validDirection.push_back("UP");
    if(downRoom != nullptr)
        validDirection.push_back("DOWN");
    if(leftRoom != nullptr)
        validDirection.push_back("LEFT");
    if(rightRoom != nullptr)
        validDirection.push_back("RIGHT");
    return validDirection;
}

void Room::setUpRoom(Room* room)
{
    this->upRoom = room;
}

void Room::setDownRoom(Room* room)
{
    this->downRoom = room;
}

void Room::setLeftRoom(Room* room)
{
    this->leftRoom = room;
}

void Room::setRightRoom(Room* room)
{
    this->rightRoom = room;
}

void Room::setIndex(int num)
{
    this->index = num;
}

void Room::setObjects(vector<Object*> obj)
{
    this->objects = obj;
}

int Room::getIndex()
{
    return this->index;
}

vector<Object*> Room::getObjects()
{
    return this->objects;
}

Room* Room::getUpRoom()
{
    return this->upRoom;
}

Room* Room::getDownRoom()
{
    return this->downRoom;
}

Room* Room::getLeftRoom()
{
    return this->leftRoom;
}

Room* Room::getRightRoom()
{
    return this->rightRoom;
}