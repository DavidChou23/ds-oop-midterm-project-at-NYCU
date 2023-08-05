#include "Item.h"

Item::Item():Object(),health(0),attack(0),defense(0),price(0),type(""){};
Item::Item(string name, int health, int attack, int defense, int price , string type):Object(name,"Item"),type(type),health(health),attack(attack),defense(defense),price(price){};

//pick up item
bool Item::triggerEvent(Object* obj)
{   
    Player* player = dynamic_cast<Player*>(obj);
    if(player != nullptr)
    {
        player->addItem(this);
        return true;
    }
    return false;
}
string Item::getDescription(){
    return "";
}


int Item::getHealth(){return this->health;}
int Item::getAttack(){return this->attack;}
int Item::getDefense(){return this->defense;}
int Item::getPrice(){return this->price;}
string Item::getType(){return this->type;}

Weapon::Weapon(string name, int health, int attack, int price):Item(name,health,attack,0,price,"weapon"){};
string Weapon::getDescription(){
    return "";
}

Shield::Shield(string name, int health, int defense, int price):Item(name,health,0,defense,price,"shield"){};
string Shield::getDescription(){
    return "";
}

Special::Special(string name, int health, int attack, int defense, int price, string discription):Item(name,health,attack,defense,price,"special"),discription(discription){};
string Special::getDescription(){
    return this->discription;
}

bool Special::SpecialEffect(Player* player){
    if(this->getDescription()=="does harm to one monster(50%)"){
        if(typeid(player->getCurrentRoom()->getObjects()[0])==typeid(Monster)||typeid(player->getCurrentRoom()->getObjects()[0])==typeid(Boss)){
            Monster *monster = dynamic_cast<Monster*>(player->getCurrentRoom()->getObjects()[0]);
            monster->setCurrentHealth(monster->getCurrentHealth()-monster->getMaxHealth()*0.5);
            return true;
        }else{
            cout<<"there's no monster in this room"<<endl;
            return false;
        }
    }else if(this->getDescription()=="recover health(50%)"){
        cout<<"your current health is "<<player->getCurrentHealth()<<endl;
        cout<<"do you want to recover health?(y/n)"<<endl;
        char c;
        cin>>c;
        if(c=='y'||c=='Y'){
            cout<<"recover health"<<endl;
            player->setCurrentHealth(min<int>(player->getCurrentHealth()+player->getMaxHealth()*0.5,player->getMaxHealth()));
            return true;
        }else{
            cout<<"you don't recover health"<<endl;
            return false;
        }
    }else if(this->getDescription()=="recover health(90%)"){
        cout<<"your current health is "<<player->getCurrentHealth()<<endl;
        cout<<"do you want to recover health?(y/n)"<<endl;
        char c;
        cin>>c;
        if(c=='y'){
            cout<<"recover health"<<endl;
            player->setCurrentHealth(min<int>(player->getCurrentHealth()+player->getMaxHealth()*0.9,player->getMaxHealth()));
            return true;
        }else{
            cout<<"you don't recover health"<<endl;
            return false;
        }
    }
    else if(this->getDescription()=="prevent one attack(50%)"){
        if(typeid(player->getCurrentRoom()->getObjects()[0])==typeid(Monster)||typeid(player->getCurrentRoom()->getObjects()[0])==typeid(Boss)){
            Monster *monster = dynamic_cast<Monster*>(player->getCurrentRoom()->getObjects()[0]);
            player->setTmpDefense(monster->getAttack()*0.5);
            return true;
        }else{
            cout<<"there's no monster in this room"<<endl;
            return false;
        }
    }
    else if(this->getDescription()=="recover MP(100%)"){
        player->setMagicPoint(player->getMaxMagicPoint());
    }
}