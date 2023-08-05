#include "NPC.h"

// Constructor
NPC::NPC(): GameCharacter()
{
    script = "";
    commodity = vector<Item*>();
}

// Constructor
NPC::NPC(string name, string script, vector<Item*> commodity): GameCharacter(name, 0, 0, 0),commodity(commodity)
{
    this->script = script;
    //this->commodity = commodity;
}

// Print all the Item in this NPC
void NPC::listCommodity()
{
    cout << "Commodity List:" << endl;
    printf("%-5s%-20s%-10s%-10s%-10s%-10s\n", "No.","Name", "Type", "Attack", "Defense","Price");
    for(int i=0;i<int(commodity.size());i++)
    {
        if(commodity[i]->getType()=="weapon")
        {
            printf("%-5d%-20s%-10s%-10d%-10d%-10d\n",i, commodity[i]->getName().c_str(), commodity[i]->getType().c_str(), commodity[i]->getAttack(), 0,commodity[i]->getPrice());
        }
        else if(commodity[i]->getType()=="shield")
        {
            printf("%-5d%-20s%-10s%-10d%-10d%-10d\n",i, commodity[i]->getName().c_str(), commodity[i]->getType().c_str(), 0, commodity[i]->getDefense(), commodity[i]->getPrice());
        }else if(commodity[i]->getType()=="special")
        {
            printf("%-5d%-20s%-10s%-10d%-10d%-10d*/\n", commodity[i]->getName().c_str(), commodity[i]->getType().c_str(), commodity[i]->getAttack(), commodity[i]->getDefense(), commodity[i]->getPrice());
            cout<<"/*"<<commodity[i]->getDescription()<<"*/"<<endl;
        }else{
            printf("%-5d%-20s%-10s%-10d%-10d%-10d\n", commodity[i]->getName().c_str(), commodity[i]->getType().c_str(), commodity[i]->getAttack(), commodity[i]->getDefense(), commodity[i]->getPrice());
        }
    }
    cout<<commodity.size()<<".    buy nothing."<<endl;
}

// Virtual function that you need to complete
// In NPC, this function should deal with the
// transaction in easy implementation
bool NPC::triggerEvent(Object* object)
{
    Player* player = dynamic_cast<Player*>(object);
    if (player == NULL)
    {
        return false;
    }
    cout << script << endl;
    listCommodity();
    cout << "What do you want to buy?(number)" << endl;
    cout<<"You have "<<player->getMoney()<<" money."<<endl;
    while(1){
        int num;
        cin >> num;
        if(num==int(commodity.size())){
            return false;
        }else if(num<0||num> int(commodity.size())){
            cout<<"invalid input."<<endl;
            cout<<"please try again"<<endl;
            continue;
        }

        if (player->getMoney() >= commodity[num]->getPrice())
        {
            player->addItem(commodity[num]);
            player->setMoney(player->getMoney() - commodity[num]->getPrice());
            commodity.erase(commodity.begin()+num);
            cout << "You bought " << commodity[num]->getName() << endl;
            return true;
        }
        else
        {
            cout << "You don't have enough money." << endl;
            cout<<"You have "<<player->getMoney()<<" money."<<endl;
            cout<<"Do you want to sell something?(y/n)"<<endl;
            while(1){
                char c;
                cin>>c;
                if(c=='y'||c=='Y'){
                    player->sellItem();
                    break;
                }else if(c=='n'||c=='N'){
                    break;
                }else{
                    cout<<"invalid input."<<endl;
                    cout<<"please try again"<<endl;
                    continue;
                }
            }
            return false;
        }
        cout << "There is no such item." << endl;
        return false;
    }
}

// Set & Get function
vector<Item*> NPC::getCommodity()
{
    return commodity;
}

int NPC::getEquipmentAttack(){return 0;}
int NPC::getEquipmentDefense(){return 0;}