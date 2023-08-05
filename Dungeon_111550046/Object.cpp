#include "Object.h"

Object::Object()=default;
Object::Object(string name,string tag)
{
    this->name = name;
    this->tag = tag;
}

string Object::getName()
{
    return this->name;
}
string Object::getTag()
{
    return this->tag;
}  