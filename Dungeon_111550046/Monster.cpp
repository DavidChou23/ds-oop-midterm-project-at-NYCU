#include "Monster.h"

Monster::Monster():GameCharacter("Monster",100,20,20)
{
    dropCoin = 10;
    dropExp = 10;
    cd = 1;
    cdCount = 0;
    //dropItem ha
    //dropItem = Item()
};

Monster::Monster(string name,int maxHealth,int Attack,int Defense,int dropCoin, int dropExp, int dropItemNum,int cd):GameCharacter(name,maxHealth,Attack,Defense)
{
    this->dropCoin = dropCoin;
    this->dropExp = dropExp;
    this->dropItemNum = dropItemNum;
    this->cd = cd;
    cdCount = 0;
};//end constructor

//combat system
bool Monster::triggerEvent(Object* obj)
{
    static Monster backup = *this;
    Player* player = dynamic_cast<Player*>(obj);
    cout << "You encounter a " << getName() << endl;
    system("cls");
    //if(typeid(obj) == typeid(Player))

    {
        attack:
        if(cdCount == cd)  //monster can attack
        {
            cout << "You have " << player->getCurrentHealth() << " health left" << endl;
            cout << "You have " << player->getMagicPoint() << " MP left" << endl;
            cout << "You have " << player->getAttack() << " attack" << endl;
            cout << "You have " << player->getDefense() << " defense" << endl;
            cout<<endl;
            if(player->getMagicPoint()<=0){
                cout<<"You don't have enough MP to attack"<<endl;
                cout<<"do you want to exchange money for MP? (y/n)"<<endl;
                char choice;
                cin>>choice;
                if(choice=='y'||choice=='Y'){
                    player->exchangeMagicPoint();
                    goto attack;
                }
                else{
                    cout<<"You can't attack"<<endl;
                    goto fight;
                }
            }
            player->setMagicPoint(player->getMagicPoint()-1);
            takeDamage(player->getAttack());
            cout<<"You does "<<(player->getAttack()-this->getDefense()>0?player->getAttack()-this->getDefense():0)<<" attack to monster."<<endl;
            cdCount=0;
            if(checkIsDead())  //monster is dead
            {
                cout << "You killed the " << getName() << endl;
                getReward(player);
                cout<<"Remember to pick up the item dropped by the monster."<<endl;
                system("pause");
                return true;
            }//end if
            else //player take damage  //monster is alive
            {
                player->takeDamage(getAttack());
                cout<<"Monster attack you."<<endl;
                if(player->checkIsDead())  //player is dead
                {
                    //cout << "You died" << endl;
                    return false;
                }//end if
                else  //player is alive
                {
                    cout << "You have " << player->getCurrentHealth() << " health left" << endl;
                    cout << "You have " << player->getMagicPoint() << " MP left" << endl;
                    cout << "You have " << player->getAttack() << " attack" << endl;
                    cout << "You have " << player->getDefense() << " defense" << endl;
                    cout<<endl;
                    goto fight;
                }//end else
                cdCount++;
            }//end else
        }
        else  //monster can't attack
        {
            cout << "You have " << player->getCurrentHealth() << " health left" << endl;
            cout << "You have " << player->getMagicPoint() << " MP left" << endl;
            cout << "You have " << player->getAttack() << " attack" << endl;
            cout << "You have " << player->getDefense() << " defense" << endl;
            cout<<endl;
            if(player->getMagicPoint()<=0){
                cout<<"You don't have enough MP to attack"<<endl;
                cout<<"do you want to exchange money for MP? (y/n)"<<endl;
                char choice;
                cin>>choice;
                if(choice=='y'||choice=='Y'){
                    player->exchangeMagicPoint();
                    goto attack;
                }
                else{
                    cout<<"You can't attack"<<endl;
                    goto fight;
                }
            }
            takeDamage(player->getAttack());
            player->setMagicPoint(player->getMagicPoint()-1);
            cdCount++;
            cout<<"You does "<<(player->getAttack()-this->getDefense()>0?player->getAttack()-this->getDefense():0)<<" attack to monster."<<endl;
            if(checkIsDead())  //monster is dead
            {
                cout << "You killed the " << getName() << endl;
                getReward(player);
                cout<<"Remember to pick up the item dropped by the monster."<<endl;
                system("pause");
                return true;
            }//end if
        }//end else

        fight:
        vector<string> tmpaction={};
        if(player->getEquipment()!=nullptr &&  player->getEquipment()->getType()=="special"){
            tmpaction.push_back("use item");
        }
        tmpaction.push_back("retreat");
        if(player->getMagicPoint()<0){
            tmpaction.push_back("exchange money for MP");
        }else{
            tmpaction.push_back("attack");
        }
        for(int i=0;i<int(tmpaction.size());i++){
            cout<<i+1<<". "<<tmpaction[i]<<endl;
        }
        char choicet;
        cin>>choicet;
        int choice;
        if(isdigit(choicet)){
            choice= choicet-48;  //char to int, by use ascii code
        }else{
            cout<<"invalid input."<<endl;
            goto fight;
        }
        if(choice<1 || choice>int(tmpaction.size())){
            cout<<"invalid input."<<endl;
            goto fight;
        }
        if(tmpaction[choice-1]=="use item"){
            Special* tmp = dynamic_cast<Special*>(player->getEquipment());
            //ask y/n, and handle invalid input
            while(true){
                cout<<"Are you sure to use "<<tmp->getName()<<"? (y/n)"<<endl;
                char choice;
                cin>>choice;
                if(choice=='y'||choice=='Y'){
                    tmp->SpecialEffect(player);
                    player->setEquipment(nullptr);
                    goto fight;
                }else if(choice=='n'||choice=='N'){
                    goto fight;
                }else{
                    cout<<"invalid input."<<endl;
                }
            }
        }else if(tmpaction[choice-1]=="retreat"){
            *this = backup;
            player->changeRoom(player->getPreviousRoom());
            return false;
        }else if(tmpaction[choice-1]=="exchange money for MP"){
            player->exchangeMagicPoint();
            goto attack;
        }else if(tmpaction[choice-1]=="attack"){
            goto attack;
        }
    }//end if
    return false;
}//end triggerEvent

bool Monster::getReward(Player* player)
{
    vector<Object*> drop;
    cout << "You get " << dropCoin << " coins" << endl;
    cout << "You get " << dropExp << " exp" << endl;
    cout << "You get " << int(dropExp/3) << " MP" << endl;
    player->setMoney(player->getMoney()+dropCoin);
    player->setExp(player->getExp()+dropExp);
    player->setMagicPoint((player->getMagicPoint()+int(dropExp/3))>player->getMaxMagicPoint()?player->getMagicPoint():player->getMagicPoint()+int(dropExp/3));
    player->levelUp();  //ckeck exp is enough is in levelUp()
    if(dropItemNum>0)
    {
        cout << "Monster drop " << dropItemNum << " items" << endl;
        for(int i=0;i<dropItemNum;i++)
        {
            int ws=rand()%2;
            if(ws==0){
                Shield* shield= new Shield("Monster Shield",0,getDefense(),0);
                drop.push_back(shield);
            }else if(ws==1){
                Weapon* weapon =new Weapon("Monster Weapon",0,getAttack()/5,0);
                drop.push_back(weapon);
            }
        }//end for
    }//end if
    dropItem=drop;
    return true;  //success
}//end getReward

int Monster::getDropCoin()
{
    return dropCoin;
}//end getDropCoin

int Monster::getDropExp()
{
    return dropExp;
}//end getDropExp

int Monster::getDropItemNum()
{
    return dropItemNum;
}//end getDropItemNum


vector<Special*> Boss::special={
    new Special("lighting!!",0,0,0,0,"does harm to one monster(50%)"),
    new Special("Beverage:)",0,0,0,0,"recover health(50%)"),
    new Special("Beverage!!",0,0,0,0,"recover health(90%)"),
    new Special("Non-Newtonian fluid",0,0,0,0,"prevent one attack(50%)"),
    new Special("Magic Water!!",0,0,0,0,"recover MP(100%)")
};

Boss::Boss(string name,int maxHealth,int Attack,int Defense,int dropCoin, int dropExp, int dropItemNum,int cd,int stage):Monster(name,maxHealth,Attack,Defense,dropCoin,dropExp,dropItemNum,cd),stage(stage){}
bool Boss::getReward(Player* player)
{
    vector<Object*> drop;
    int d=0;
    cout << "You get " << getDropCoin() << " coins" << endl;
    cout << "You get " << getDropExp() << " exp" << endl;
    cout << "You get " << int(dropExp/3) << " MP" << endl;
    player->setMoney(player->getMoney()+getDropCoin());
    player->setExp(player->getExp()+getDropExp());
    player->setMagicPoint((player->getMagicPoint()+int(dropExp/3))>player->getMaxMagicPoint()?player->getMagicPoint():player->getMagicPoint()+int(dropExp/3));
    player->levelUp();  //ckeck exp is enough is in levelUp()
    cout << "You get " << getDropItemNum() << " items" << endl;
    //dropItemNum>0 ?
    if(dropItemNum>0)
    {
        if(int(special.size())==5-stage+1){
            d=1;
            int tmprandom=rand()%special.size();
            Item* tmpspecial=special[tmprandom];
            cout << "Boss drop " << tmpspecial->getName() << endl;
            cout<<tmpspecial->getDescription()<<endl;
            drop.push_back(tmpspecial);
            special.erase(special.begin()+tmprandom);
        }else{
            d=0;
        }
        
        for(int i=0;i<getDropItemNum()-d;i++)
        {
            int ws=rand()%2;
            if(ws==0){
                Shield* shield=new Shield("Boss Shield",0,getDefense(),0);
                drop.push_back(shield);
            }else if(ws==1){
                Weapon* weapon= new Weapon("Boss Weapon",0,getAttack()/5,0);
                drop.push_back(weapon);
            }
        }//end for
    dropItem=drop;
    }//end if
    return true;
}//end getReward

vector<Object*> Monster::getDropItem()
{
    return dropItem;
}//end getDropItem
int Monster::getEquimentAttack(){return 0;}
int Monster::getEquimentDefense(){return 0;}