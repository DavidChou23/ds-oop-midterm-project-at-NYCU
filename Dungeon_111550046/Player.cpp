#include "Player.h"

//constructor
Player::Player():GameCharacter(),currentRoom(nullptr),previousRoom(nullptr),inventory(),money(0),exp(0),level(0),magicPoint(0),MaxMagicPoint(0),MaxLevel(0){};
//constructor
Player::Player(string name, int maxHealth, int Attack, int Defense, int money, int exp, int MaxMagicPoint, int MaxLevel):GameCharacter(name,maxHealth,Attack,Defense),currentRoom(nullptr),previousRoom(nullptr),inventory(),money(money),exp(exp),level(0),magicPoint(MaxMagicPoint),MaxMagicPoint(MaxMagicPoint),MaxLevel(MaxLevel){};


/* Set & Get function*/
void Player::setCurrentRoom(Room* room){this->currentRoom=room;}
void Player::setPreviousRoom(Room* room){this->previousRoom=room;}
void Player::setMoney(int money){this->money=money;}
void Player::setExp(int exp){this->exp=exp;}
void Player::setLevel(int level){this->level=level;}
void Player::setMagicPoint(int magicPoint){this->magicPoint=magicPoint;}
void Player::setMaxMagicPoint(int MaxMagicPoint){this->MaxMagicPoint=MaxMagicPoint;}
void Player::setMaxLevel(int MaxLevel){this->MaxLevel=MaxLevel;}
Room* Player::getCurrentRoom(){  return this->currentRoom;}
Room* Player::getPreviousRoom(){return this->previousRoom;}
int Player::getMoney(){return this->money;}
int Player::getExp(){return this->exp;}
int Player::getLevel(){return this->level;}
int Player::getMagicPoint(){return this->magicPoint;}
int Player::getMaxMagicPoint(){return this->MaxMagicPoint;}
int Player::getMaxLevel(){return this->MaxLevel;}

//put item into inventory
void Player::addItem(Item* item){this->inventory.push_back(item);}


//movement list
void Player::changeRoom(Room* next){  //with 2 dollar toll
    if(this->money>=2){
        this->money-=2;
        cout<<"You have paid 2 dollar toll."<<endl;
        this->previousRoom=this->currentRoom;
        this->currentRoom=next;
        cout<<"You have moved to the next room."<<endl;
        system("pause");
        return;
    }else{
        cout<<"You don't have enough money to pay the toll."<<endl;
        cout<<"You can't move to the next room."<<endl;
        system("pause");
        //ask y/n, use while loop to handle invalid input
        char choice;
        while(1){
            cout<<"do you want to sell some items to get money?(y/n)"<<endl;
            cin>>choice;
            if(choice=='y'||choice=='Y'){
                sellItem();
                return;
            }else if(choice=='n'||choice=='N'){
                return;
            }else{
                cout<<"Invalid input, please enter again."<<endl;
            }
        }
    }
}

//level up
void Player::levelUp()
{
    if(exp>=(level+1)*20){
        this->exp=this->exp-level*30;
        this->level++;
        this->setMaxHealth(this->getMaxHealth()+10);
        this->setCurrentHealth(this->getCurrentHealth()+10);
        this->setAttack(this->getAttack()+5);
        this->setDefense(this->getDefense()+5);
        this->MaxMagicPoint+=5;
        this->magicPoint=this->MaxMagicPoint;
        cout<<"You have leveled up!"<<endl;
        cout<<"Your current status:"<<endl;
        showStatus(nullptr);
    }
    if(exp>=(level+1)*20){
        levelUp();
    }
}

//show status
void Player::showStatus(Object* object)
{
    cout<<"Player's status:"<<endl;
    cout<<"Name: "<<this->getName()<<endl;
    cout<<">Health: "<<this->getCurrentHealth()<<"/"<<this->getMaxHealth()<<endl;
    cout<<">Attack: "<<this->getAttack()<<endl;
    cout<<">Defense: "<<this->getDefense()<<endl;
    cout<<">Money: "<<this->money<<endl;
    cout<<">Exp: "<<this->exp<<"/"<<(level+1)*20<<endl;
    cout<<">Magic Point(MP): "<<this->magicPoint<<"/"<<this->getMaxMagicPoint()<<endl;
    cout<<">Level: "<<this->level<<"/"<<this->getMaxLevel()<<endl;
    system("pause");
}


bool Player::sellItem(){
    system("cls");
    if (this->inventory.size() == 0){
        cout << "You have nothing to sell." << endl;
        return false;
    }else{
        while(1){
            cout << "You have the following items can be sold:" << endl;
            for (int i = 0; i < int(this->inventory.size()); i++){
                cout << i << ". " << this->inventory[i]->getName()<<" attact: "<<inventory[i]->getAttack()<<" defence: "<<inventory[i]->getDefense()<< " (Price: " << int(this->inventory[i]->getPrice()/3) << ")" << endl;
            }
            cout<<this->inventory.size()<<". Quit"<<endl;
            int choice;
            cout << "Please enter the number of the item you want to sell: ";
            cin >> choice;
            if (choice == int(this->inventory.size())){
                return true;
            }else if (choice >= 0 && choice < int(this->inventory.size())){
                this->money += int(this->inventory[choice]->getPrice()/3);
                for(int i=0;i<3;i++){
                    if(equipment[i]==this->inventory[choice])
                        equipment[i]=nullptr;
                }
                this->inventory.erase(this->inventory.begin() + choice);
                cout << "You have sold the item." << endl;
            }else{
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }
}

bool Player::exchangeMagicPoint(){
    system("cls");
    if (this->magicPoint == this->MaxMagicPoint){
        cout << "You have already reached the maximum MP." << endl;
        return true;
    }else{
        int Maxamount = this->MaxMagicPoint - this->magicPoint;
        int amount;
        cout << "You have " << this->money << " dollars." << endl;
        cout << "You can exchange up to " << Maxamount << " MP." << endl;
        cout << "Please enter the amount of MP you want to exchange: ";
        while(1){
            cin >> amount;
            if (amount > Maxamount){
                cout << "You can only exchange up to " << Maxamount << " MP." << endl;
                cout << "Please enter the amount of MP you want to exchange: ";
            }else if (amount < 0){
                cout << "Invalid input. Please try again." << endl;
                cout << "Please enter the amount of MP you want to exchange: ";
            }else if(amount == 0){
                return true;
            }else{
                if(this->money < amount){
                    cout << "You don't have enough money to exchange." << endl;
                    return false;
                }else{
                    this->money -= amount;
                    this->magicPoint += amount;
                    cout << "You have exchanged " << amount << " MP." << endl;
                    return true;
                }
            }
        }
    }
}
//print out the current equipment
void Player::showCurrentEquipment(){
    if(equipment[0]==nullptr&&equipment[1]==nullptr&&equipment[2]==nullptr){ //at the begining, nothing is equiped
        cout<<"You're current equiment is empty."<<endl;
        return;
    }
    cout << "Here is your current equipment:" << endl;
    printf("/***************************************************\n");
    printf("*%-20s%-10s%-10s%-10s*\n", "Name", "Type", "Attack", "Defense");

    for(int i=0;i<int(size(equipment));i++)
    {
        if(equipment[i]!=nullptr){
            if(equipment[i]->getType()=="weapon")
            {
                printf("*%-20s%-10s%-10d%-10d*\n", equipment[i]->getName().c_str(), equipment[i]->getType().c_str(), equipment[i]->getAttack(), 0);
            }
            else if(equipment[i]->getType()=="shield")
            {
                printf("*%-20s%-10s%-10d%-10d*\n", equipment[i]->getName().c_str(), equipment[i]->getType().c_str(), 0, equipment[i]->getDefense());
            }else if(equipment[i]->getType()=="special")
            {
                printf("/*%-20s%-10s%-10d%-10d*\n", equipment[i]->getName().c_str(), equipment[i]->getType().c_str(), equipment[i]->getAttack(), equipment[i]->getDefense());
                cout<<"*"<<equipment[i]->getDescription()<<"*/"<<endl;
            }else{
                printf("*%-20s%-10s%-10d%-10d*\n", equipment[i]->getName().c_str(), equipment[i]->getType().c_str(), equipment[i]->getAttack(), equipment[i]->getDefense());
            }
        }
    }
    printf("***************************************************/\n\n");
}


void Player::equipItem(){
    system("cls");
    vector<Item*> weaponList;
    vector<Item*> shieldList;
    vector<Item*> itemNotEquip;
    for(int i=0;i<int(this->inventory.size());i++)
    {
        if(this->inventory[i]->getType()=="weapon")
        {
            weaponList.push_back(this->inventory[i]);
        }
        else if(this->inventory[i]->getType()=="shield")
        {
            shieldList.push_back(this->inventory[i]);
        }
    }
    if(this->inventory.size()==0)
    {
        cout<<"You have no item to equip."<<endl;
        system("pause");
    }
    else
    {
        system("cls");
        this->showCurrentEquipment();
        cout<<"You can equip 3 items (1 weapon, 1 shield, 1 freedom item)."<<endl<<endl;
        cout<<"You have the following weapons:"<<endl;
        //show weapon list in grid(number, name, attack)
        printf("%-5s%-20s%-10s\n","No.","Name","Attack");
        for(int i=0;i<int(weaponList.size());i++){
            printf("%-5d%-20s%-10d\n",i,weaponList[i]->getName().c_str(),weaponList[i]->getAttack());
        }
        cout<<weaponList.size()<<".    Make it empty."<<endl;
        cout<<weaponList.size()+1<<".    skip equip new weapon."<<endl;
        cout<<weaponList.size()+2<<".    Quit"<<endl;
        while(1){
            cout<<"Please enter the number of the weapon you want to equip: ";
            char choicet;
            cin>>choicet;
            int choice;
            if(isdigit(choicet)){
               choice= choicet-48;  //char to int, by use ascii code
            }else{
                continue;
            }
            if(choice==int(weaponList.size())){
                this->equipment[0]=nullptr;
                break;
            }else if(choice==int(weaponList.size()+1)){
                break;
            }else if(choice==int(weaponList.size()+2)){
                return;
            }else if(choice>=0&&choice<int(weaponList.size())){
                this->equipment[0]=weaponList[choice];
                cout<<"You have equipped "<<weaponList[choice]->getName()<<"."<<endl;
                break;
            }else{
                cout<<"Invalid input, please try again."<<endl;
            }
        }

        system("cls");
        this->showCurrentEquipment();
        //show shield list in grid(number, name, defense)
        cout<<"You have the following shields:"<<endl;
        printf("%-5s%-20s%-10s\n","No.","Name","Defense");
        for(int i=0;i<int(shieldList.size());i++)
        {
            printf("%-5d%-20s%-10d\n",i,shieldList[i]->getName().c_str(),shieldList[i]->getDefense());
        }
        cout<<shieldList.size()<<".    Make it empty."<<endl;
        cout<<shieldList.size()+1<<".    skip equip new shield."<<endl;
        cout<<shieldList.size()+2<<".    Quit"<<endl;
        while(1){
            cout<<"Please enter the number of the shield you want to equip: ";
            char choicet;
            cin>>choicet;
            int choice;
            if(isdigit(choicet)){
               choice= choicet-48;  //char to int, by use ascii code
            }else{
                continue;
            }
            if(choice==int(shieldList.size())){
                equipment[1]=nullptr;
                break;
            }else if(choice==int(shieldList.size()+1)){
                break;
            }else if(choice==int(shieldList.size()+2)){
                return;
            }else if(choice>=0&&choice<int(shieldList.size())){
                this->equipment[1]=shieldList[choice];
                cout<<"You have equipped "<<shieldList[choice]->getName()<<"."<<endl;
                break;
            }else{
                cout<<"Invalid input, please try again."<<endl;
            }
        }

        for(int i=0;i<int(this->inventory.size());i++){
            //all item not in equipment
            if(this->inventory[i]!=this->equipment[0]&&this->inventory[i]!=this->equipment[1]){
                itemNotEquip.push_back(this->inventory[i]);
            }
        }
        system("cls");
        this->showCurrentEquipment();
        cout<<"You have the following items, choose them in your freedom:"<<endl;
        //show item list in grid(number, name,type, attack, defense)
        printf("%-5s%-20s%-10s%-10s%-10s\n","No.","Name","Type","Attack","Defense");
        for(int i=0;i<int(itemNotEquip.size());i++)
        {
            if(itemNotEquip[i]->getType()=="weapon")
            {
                printf("%-5d%-20s%-10s%-10d%-10s\n",i,itemNotEquip[i]->getName().c_str(),"Weapon",itemNotEquip[i]->getAttack(),"N/A");
            }
            else if(itemNotEquip[i]->getType()=="shield")
            {
                printf("%-5d%-20s%-10s%-10s%-10d\n",i,itemNotEquip[i]->getName().c_str(),"Shield","N/A",itemNotEquip[i]->getDefense());
            }else if(itemNotEquip[i]->getType()=="special")
            {
                printf("%-5d%-20s%-10s%-10d%-10d%s\n",i,itemNotEquip[i]->getName().c_str(),"Special",itemNotEquip[i]->getAttack(),itemNotEquip[i]->getDefense(),itemNotEquip[i]->getDescription().c_str());
            }
            else{
                printf("%-5d%-20s%-10s%-10d%-10d\n",i,itemNotEquip[i]->getName().c_str(),itemNotEquip[i]->getType().c_str(),itemNotEquip[i]->getAttack(),itemNotEquip[i]->getDefense());
            }
        }
        cout<<itemNotEquip.size()<<".    Make it empty."<<endl;
        cout<<itemNotEquip.size()+1<<".    skip equip new item"<<endl;
        cout<<itemNotEquip.size()+2<<".    Quit"<<endl;
        while(1){
            cout<<"Please enter the number of the item you want to equip: ";
            char choicet;
            cin>>choicet;
            int choice;
            if(isdigit(choicet)){
                choice= choicet-48;  //char to int, by use ascii code
            }else{
                continue;
            }
            if(choice==int(itemNotEquip.size())){
                equipment[2]=nullptr;
                break;
            }else if(choice==int(itemNotEquip.size()+1)){
                break;
            }else if(choice==int(itemNotEquip.size()+2)){
                return;
            }else if(choice>=0&&choice<int(itemNotEquip.size())){
                this->equipment[2]=itemNotEquip[choice];
                cout<<"You have equipped "<<itemNotEquip[choice]->getName()<<"."<<endl;
                break;
            }else{
                cout<<"Invalid input, please try again."<<endl;
            }
        }
    }
}


Item* Player::getEquipment(){
    return this->equipment[2];
}

void Player::setEquipment(Item* item){
    this->equipment[2]=item;
}

//should not be used
bool Player::triggerEvent(Object* _){
    system("cls");
    vector<Object*> roomobj = currentRoom->getObjects();
    //action list
    vector<string> actionList;
    actionList.push_back("Move");
    actionList.push_back("Check status");
    actionList.push_back("Equip item");
    if(roomobj.size()==0)
    {
       //do nothing
    }
    else
    {
        if(roomobj[0]->getTag()=="Item")
        {
            actionList.push_back("Pick up item");
        }
        else if(roomobj[0]->getTag()=="GameCharacter"){
            //if the game character is a monster
            if(roomobj[0]->getName()=="Monster")
            {
                actionList.erase(actionList.begin());  //remove "Move"
                actionList.push_back("Fight with monster");
            }else if(roomobj[0]->getName()=="NPC"){
                actionList.erase(actionList.begin());  //remove "Move"
                actionList.push_back("Talk with NPC");
            }else{
                throw "Invalid game character";
            }
        }
    }
    cout<<"What do you want to do?"<<endl;
    for(int i=0;i<int(actionList.size());i++)
    {
        cout<<i<<". "<<actionList[i]<<endl;
    }
    while(1){
        char choicet;
        cin>>choicet;
        int choice;
        if(isdigit(choicet)){
            choice= choicet-48;  //char to int, by use ascii code
        }else{
            continue;
        }
        if(choice>=0&&choice<int(actionList.size()))
        {
            if(actionList[choice]=="Move")
            {
                changeRoom(previousRoom);
                return true;
            }
            else if(actionList[choice]=="Check status")
            {
                showStatus(nullptr);
                triggerEvent(nullptr);
                return true;
            }
            else if(actionList[choice]=="Equip item")
            {
                equipItem();
                return true;
            }
            else if(actionList[choice]=="Pick up item")
            {
                Item *item = dynamic_cast<Item*>(roomobj[0]);
                addItem(item);
                return true;
            }
            else if(actionList[choice]=="Fight with monster")
            {
                Monster *monster = dynamic_cast<Monster*>(roomobj[0]);
                if(monster->triggerEvent(this)){
                    cout<<"You died."<<endl;
                    cout<<"Game over."<<endl;
                    exit(0);
                }else{
                    triggerEvent(nullptr);
                }
                return true;
            }
            else if(actionList[choice]=="Talk with NPC")
            {
                NPC *npc = dynamic_cast<NPC*>(roomobj[0]);
                npc->triggerEvent(this);
                return true;
            }
        }
        else
        {
            cout<<"Invalid input, please try again."<<endl;
        }
    }
}


int Player::getEquipmentAttack(){
    int equipmentAttack=0;
    for(int i=0;i<3;i++){
        if(equipment[i]!=nullptr){
            equipmentAttack+=equipment[i]->getAttack();
        }
    }
    return equipmentAttack;
}

int Player::getEquipmentDefense(){
    int equipmentDefense=0;
    for(int i=0;i<3;i++){
        if(equipment[i]!=nullptr){
            equipmentDefense+=equipment[i]->getDefense();
        }
    }
    return equipmentDefense;
}