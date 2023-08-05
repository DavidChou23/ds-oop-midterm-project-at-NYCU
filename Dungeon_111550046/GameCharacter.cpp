#include "GameCharacter.h"

GameCharacter::GameCharacter():Object(),currentHealth(0),Attack(0),Defense(0),maxHealth(0){};
GameCharacter::GameCharacter(string name, int maxHealth, int Attack, int Defense):Object(name,"GameCharacter"),currentHealth(maxHealth),Attack(Attack),Defense(Defense),maxHealth(maxHealth){};

bool GameCharacter::checkIsDead()
{
    if(this->currentHealth<=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int GameCharacter::takeDamage(int damage)
{
    this->currentHealth-=(damage-this->getDefense()>0?damage-this->getDefense():0);
    return this->currentHealth;
}

void GameCharacter::setMaxHealth(int maxHealth){this->maxHealth=maxHealth;}
void GameCharacter::setCurrentHealth(int currentHealth){this->currentHealth=currentHealth;}
void GameCharacter::setAttack(int Attack){this->Attack=Attack;}
void GameCharacter::setDefense(int Defense){this->Defense=Defense;}
void GameCharacter::setAttackMultiplier(int attackmultiplier){this->attackmultiplier=attackmultiplier;}
void GameCharacter::setDefMultiplier(int defmultiplier){this->defmultiplier=defmultiplier;}
void GameCharacter::setTmpDefense(int tmpDefense){this->tmpDefense=tmpDefense;}
int GameCharacter::getMaxHealth(){return this->maxHealth;}
int GameCharacter::getCurrentHealth(){return this->currentHealth;}
int GameCharacter::getAttack(){return attackmultiplier*(Attack+getEquipmentAttack());}
int GameCharacter::getDefense(){return defmultiplier*(Defense+tmpDefense+getEquipmentDefense());}
int GameCharacter::getTmpDefense(){
    int tmp=this->tmpDefense;
    this->tmpDefense=0;
    return tmp;
}


int GameCharacter::getEquipmentAttack(){return 0;}
int GameCharacter::getEquipmentDefense(){return 0;}