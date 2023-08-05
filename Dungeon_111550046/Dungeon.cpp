#include "Dungeon.h"
//have 5 stages
/*
first stage have 10 rooms linked together
[r7][r8][r9][r10]
[r4][r5][r6]
[r1][r2][r3]
*/

/*1 room have 1 npc @giver
  giver give player 1 weapon and 1 shield
  giver always at the first room of each stage,where player start
*/

/*1 room have 1 npc @seller
  seller have 6 items to sell, 3 weapon and 3 shield
  seller at r5, r6, r7, r8 in random
  item price is 1/2 of the item's attack or defense
  and the price will increase for each stage
  all item can be bought by player
*/

/*7 room have 1 monster
  Item reward occur in 3/8 chance
  Item reward for monster is 1 weapon or 1 shield player can only choose one of them
  weapon has half of the monster's attack
  shield has the monster's defense
  Coin and Exp reward occur every time, the amount is in the monster's status
*/


/*last room of each stage have 1 boss
  when player beat the boss,
  he/she can choose to go to the next stage or
  go back to the first room of the stage and play this stage again.

  if player choose to go to the next stage,
  he/she will go to the first room of the next stage
  next stage will have 1 more room
  and there're 1 giver, 1 seller, 8 monster and 1 boss
  all things in the room will be different
  and monster will be stronger, but also have better reward.

  if player choose to play this stage again,
  he/she will go to the first room of this stage
  every thing in the room will be reset
  and there's only 1 seller and 8 monster
  and 1 boss.
  replace the old seller and monster with new one
  and the new seller and monster will have new item
  Coin and Exp reward will be decreased.
*/

Dungeon::Dungeon(){
    initPlayers();
    createPlayer();
}

void Dungeon::initDefaultItems(){
    Weapon* defaultweapon_Warrier = new Weapon("Sword", 0, 10, 0);
    Weapon* defaultweapon_Mage = new Weapon("Staff", 0, 10, 0);
    Weapon* defaultweapon_Thief = new Weapon("Dagger", 0, 10, 0);
    Shield* defaultshield = new Shield("Shield", 0, 10, 0);
    this->defaultItems.push_back(defaultweapon_Warrier);
    this->defaultItems.push_back(defaultweapon_Mage);
    this->defaultItems.push_back(defaultweapon_Thief);
    this->defaultItems.push_back(defaultshield);
}

//call at begining of the game
void Dungeon::initPlayers(){
    initDefaultItems();
    Player* Warrior = new Player("Warrior", 80, 20, 10, 5, 0, 10, 5);
    Warrior->setAttackMultiplier(1.5);
    Player* Mage = new Player("Mage", 90, 10, 10, 5, 0, 12, 5);
    Player* Thief = new Player("Thief", 90, 10, 10, 10, 0, 10, 5);
    Thief->setDefMultiplier(1.5);

    Warrior->addItem(defaultItems[0]);
    Warrior->addItem(defaultItems[3]);
    Mage->addItem(defaultItems[1]);
    Mage->addItem(defaultItems[3]);
    Thief->addItem(defaultItems[2]);
    Thief->addItem(defaultItems[3]);
    this->players.push_back(Warrior);
    this->players.push_back(Mage);
    this->players.push_back(Thief);
}

//call at begining of each stage
void Dungeon::initNPCs(){
    npcs.clear();
    vector<Item*> giverItems; //give player 1 weapon and 1 shield
    Weapon* weapongive= new Weapon("Sword", 0, stage*10, 0);
    Shield* shieldgive= new Shield("Shield", 0, stage*10, 0);
    giverItems.push_back(weapongive);
    giverItems.push_back(shieldgive);
    if(stage==1){
        NPC* giver = new NPC("Giver", "Hello, welcome to the dungeon!\nThese things are free to you", giverItems);
        this->npcs.push_back(giver);
    }
    else{
        //concat string
        string s = "Hello, welcome to stage:";
        s += stage;
        s += "\nThese things are free to you";
        NPC* giver = new NPC("Giver", s, giverItems);
        this->npcs.push_back(giver);
    }
    vector<Item*> sellerItems; //have 3 items to sell, random how many of them are weapon and how many of them are shield
    int w = rand() % 2 + 1; //random 1 or 2
    for(int i = 0; i < w; i++){
        Weapon* weapon= new Weapon("Sword", 0, stage*10+rand() % 10 + 1, stage*7.5+rand() % 10 + 1);
        sellerItems.push_back(weapon);
    }
    for(int i = 0; i < 3-w; i++){
        Shield* shield= new Shield("Shield", 0, stage*10+rand() % 10 + 1, stage*7.5+rand() % 10 + 1);
        sellerItems.push_back(shield);
    }
    NPC* seller = new NPC("Seller", "Hello, welcome to the dungeon!\nThese are the items I have for sale", sellerItems);
    this->npcs.push_back(seller);
}

//call at begining of the game
//choose job
void Dungeon::createPlayer(){
    cout << "Please choose your job(number):" << endl;
    for(int i = 0; i < int(players.size()); i++){
        cout << i+1 << ". " << players[i]->getName() << endl;
    }
    char jobt;
    cin >> jobt;
    int job;
    if(isdigit(jobt)){
        job = jobt-48;  //ascii
    }else{
        job=-1;
        cout << "Invalid input, please choose again." << endl;
        createPlayer();
        return;
    }
    if(job>=1 && job<=int(players.size())){
        player = players[job-1];
        cout << "You are a " << player->getName() << endl;
        system("pause");
        return;
    }else{
            cout << "Invalid input, please choose again." << endl;
            createPlayer();
    }
}

//call at begining of each stage
void Dungeon::initMonsters(){
    monsters.clear();
    int numMonster=7+(replayTimes?1:0);
    for(int i = 0; i < numMonster; i++){
        Monster* monster = new Monster("Monster", stage*10+player->getAttack(), stage*10+rand() % 10 + 1, stage*7.5+rand() % 5 + 1, stage*5+rand() % 10 + 1, stage*7.5+rand() % 10 + 1, rand() % 2, rand() % 2+1);
        this->monsters.push_back(monster);
    }
}

//call at begining of the game
//respect to battle-cats
void Dungeon::initBoss(){
        bossName[0]="Crazed Cat";
        bossName[1]="Tank Cat";
        bossName[2]="Titan Cat";
        bossName[3]="Lizard Cat";
        bossName[4]="UFO";
        bosses.push_back(new Boss(bossName[0],200,20,10, 20, 30,3,0,1));
        bosses.push_back(new Boss(bossName[1],400,11,10, 35, 60,3,0,2));
        bosses.push_back(new Boss(bossName[2],400,20,10, 65,120,3,0,4));
        bosses.push_back(new Boss(bossName[3],300,15,10, 50, 90,3,0,3));
        bosses.push_back(new Boss(bossName[4],200,20,25,100,150,3,0,5));
}

//call at begining of each stage
void Dungeon::setBoss(){
    initBoss();
    this->boss= this->bosses[stage-1];
}

//call at begining of each stage
void Dungeon::createMap(){
    rooms.clear();
    initMonsters();
    initNPCs();
    setBoss();
    Room* r1;
    if(replayTimes==0){ //have giver
        r1=new Room(1,vector<Object*>{npcs[0]});
    }
    else{ //don't have giver, monster[8] instead
        r1=new Room(1,vector<Object*>{monsters[8]});
    }
    Room* r5=new Room(5,vector<Object*>{npcs[1]});  //seller
    Room* r10=new Room(10,vector<Object*>{boss});  //boss

    //randomly put monsters in rooms
    vector<int> monsterIndex;
    for(int i = 0; i < int(monsters.size()); i++){
        monsterIndex.push_back(i);
    }
    for(int i=1;i<=int(monsters.size()+2); i++){
        if(i==1){
            rooms.push_back(r1);
            continue;
        }else if(i==5){
            rooms.push_back(r5);
            continue;
        }
        int index = rand() % monsterIndex.size();
        Room* r=new Room(i,vector<Object*>{monsters[monsterIndex[index]]});
        monsterIndex.erase(monsterIndex.begin()+index);
        rooms.push_back(r);
    }
    rooms.push_back(r10);
    rooms[0]->setUpRoom(rooms[3]);
    rooms[0]->setRightRoom(rooms[1]);
    rooms[1]->setLeftRoom(rooms[0]);
    rooms[1]->setRightRoom(rooms[2]);
    rooms[1]->setUpRoom(rooms[4]);
    rooms[2]->setLeftRoom(rooms[1]);
    rooms[2]->setUpRoom(rooms[5]);
    rooms[3]->setDownRoom(rooms[0]);
    rooms[3]->setRightRoom(rooms[4]);
    rooms[3]->setUpRoom(rooms[6]);
    rooms[4]->setLeftRoom(rooms[3]);
    rooms[4]->setRightRoom(rooms[5]);
    rooms[4]->setDownRoom(rooms[1]);
    rooms[4]->setUpRoom(rooms[7]);
    rooms[5]->setLeftRoom(rooms[4]);
    rooms[5]->setDownRoom(rooms[2]);
    rooms[5]->setUpRoom(rooms[8]);
    rooms[6]->setDownRoom(rooms[3]);
    rooms[6]->setRightRoom(rooms[7]);
    rooms[7]->setLeftRoom(rooms[6]);
    rooms[7]->setRightRoom(rooms[8]);
    rooms[7]->setDownRoom(rooms[4]);
    rooms[8]->setLeftRoom(rooms[7]);
    rooms[8]->setDownRoom(rooms[5]);
    rooms[8]->setRightRoom(rooms[9]);
    rooms[9]->setLeftRoom(rooms[8]);
    player->setCurrentRoom(rooms[0]);
    return;
}

void Dungeon::handleMovement(){
    system("cls");
    //list all valid rooms
    vector<string> validDirection=player->getCurrentRoom()->getValidDirection();
    cout<<"You can go to the following direction:"<<endl;
    for(int i=0;i<int(validDirection.size());i++)
    {
        cout<<i<<". Go "<<validDirection[i]<<endl;
    }
    cout<<validDirection.size()<<". Stay here"<<endl;
    while(1){
        cout<<"Please enter the number of the direction you want to go:"<<endl;
        char choicet;
        cin>>choicet;
        int choice;
        if(isdigit(choicet)){
            choice= choicet-48;  //char to int, by use ascii code
        }else{
            continue;
        }

        if(choice>=0&&choice<=int(validDirection.size()))
        {
            if(choice==int(validDirection.size())){
                break;
            }else if(validDirection[choice]=="UP")
            {
                player->changeRoom(player->getCurrentRoom()->getUpRoom());
                break;
            }
            else if(validDirection[choice]=="DOWN")
            {
                player->changeRoom(player->getCurrentRoom()->getDownRoom());
                break;
            }
            else if(validDirection[choice]=="LEFT")
            {
                player->changeRoom(player->getCurrentRoom()->getLeftRoom());
                break;
            }
            else if(validDirection[choice]=="RIGHT")
            {
                player->changeRoom(player->getCurrentRoom()->getRightRoom());
                break;
            }
        }
        else
        {
            cout<<"Invalid input, please try again."<<endl;
        }
    }
}

void Dungeon::handleEvent(Object* _){
    system("cls");
    vector<Object*> roomobj = player->getCurrentRoom()->getObjects();
    //action list
    vector<string> actionList;
    actionList.push_back("Move");
    actionList.push_back("Check status");
    actionList.push_back("Equip item");
    /*
    actionList.push_back("Save game");
    */
    if(player->getCurrentRoom()->getIndex()==10){  //boss room
        if(roomobj.size()==0){
            actionList.push_back("Door to next stage");
        }else if(roomobj[0]==boss){
            actionList.push_back("Fight with boss");
        }else{
            actionList.push_back("Door to next stage");
        }
    }
    if(roomobj.size()==0)
    {
       //do nothing
    }
    else
    {
        if(roomobj[0]->getTag()=="Item")
        {
            actionList.push_back("Pick up item");
        }else if(roomobj[0]->getTag()=="GameCharacter"){
            //if the game character is a monster
            string name=roomobj[0]->getName();
            if(name=="Monster")
            {
                actionList.erase(actionList.begin());  //remove "Move"
                actionList.push_back("Fight with monster");
            }else if(name=="Seller"||name=="Giver"){
                actionList.push_back("Talk with NPC");
            }
        }
    }
    actionList.push_back("Quit game.");
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
                handleMovement();
                return;
            }
            else if(actionList[choice]=="Check status")
            {
                player->showStatus(nullptr);
                return;
            }
            else if(actionList[choice]=="Equip item")
            {
                player->equipItem();
                return;
            }
            /*
            else if(actionList[choice]=="Save game")
            {
                saveGame();
                return;
            }
            */
            else if(actionList[choice]=="Pick up item")
            {
                for(int i=0;i<int(roomobj.size());i++)
                {
                    if(roomobj[i]->getTag()=="Item")
                    {
                        Item *item = dynamic_cast<Item*>(roomobj[i]);
                        player->addItem(item);
                        player->getCurrentRoom()->popObject(item);
                        cout<<"You picked up "<<item->getName()<<"."<<endl;
                    }
                }
                system("pause");
                return;
            }
            else if(actionList[choice]=="Fight with monster"||actionList[choice]=="Fight with boss")
            {
                Monster *monster = dynamic_cast<Monster*>(roomobj[0]);
                if(monster->triggerEvent(player)){ //if the player wins
                    vector<Object*> dropItem = monster->getDropItem();
                    player->getCurrentRoom()->popObject(monster);
                    player->getCurrentRoom()->setObjects(dropItem);
                }else { //player retreat
                }
                return;
            }
            else if(actionList[choice]=="Door to next stage")
            {
                nextStage();
                return;
            }
            else if(actionList[choice]=="Talk with NPC")
            {
                NPC *npc = dynamic_cast<NPC*>(roomobj[0]);
                npc->triggerEvent(player);
                if(int(npc->getCommodity().size())==0){
                    player->getCurrentRoom()->popObject(roomobj[0]);
                }
                return;
            }else if(actionList[choice]=="Quit game."){
                //record game progress
                exit(0);
            }
        }
        else
        {
            cout<<"Invalid input, please try again."<<endl;
        }
    }
}

int Dungeon::checkGameLogic(){
    if(player->getLevel()>=4||player->getMoney()>=100){
        return 1;  //win
    }else if(player->getMoney()<=0){
        cout<<"If you have no money in your pocket, you will loss."<<endl;
        system("pause");
        if(player->sellItem()==false){
            cout<<"You have no money to move."<<endl;
            cout<<"you are trapped in this room, and loss."<<endl;
            return 0;  //loss
        }else{
            return checkGameLogic();
        }
    }
    //player died when fighting have be handle in Monster class
    return 2;  //nothing
}


void Dungeon::startGame(){
    createMap();
    while(1){
        handleEvent(nullptr);
        if(checkGameLogic()==1){
            cout<<"You win!"<<endl;
            exit(0);
        }else if(checkGameLogic()==0){
            cout<<"You lose!"<<endl;
            exit(0);
        }else{
            //do nothing
            continue;
        }
    }
}


void Dungeon::runDungeon(){
    this->startGame();
}

void Dungeon::nextStage(){
    cout<<"You pass this stage"<<endl;
    cout<<"Do you want to go to next stage? (Y/N)"<<endl;
    while(1){
        string choice;
        cin>>choice;
        if(choice=="Y"||choice=="y"){
            stage+=1;
            createMap();
            break;
        }else if(choice=="N"||choice=="n"){
            replayTimes+=1;
            createMap();
            break;
        }else{
            cout<<"Invalid input, please try again."<<endl;
        }
    }
}
