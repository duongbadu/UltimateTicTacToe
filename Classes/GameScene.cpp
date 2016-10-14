#include "GameScene.h"
#define WH w + (h*tilesW)
USING_NS_CC;

//--------------------------------------------------------
//				SCENE CREATION/DELETION
//--------------------------------------------------------
GameScene::~GameScene()
{
    delete[] tile;
    delete[] position;
}

cocos2d::Scene* GameScene::createScene(int AI)
{
    cocos2d::Scene* scene = Scene::create();
    auto layer = GameScene::create(AI);
    scene->addChild(layer);
    return scene;
}

GameScene* GameScene::create(int AI)
{
    GameScene *gs = new(std::nothrow) GameScene();
    if (gs && gs->init(AI))
    {
        gs->autorelease();
        return gs;
    }
    else
    {
        delete gs;
        gs = nullptr;
        return nullptr;
    }
}

bool GameScene::init(int AI)
{
    aiActiveN = AI;
    srand(time(NULL));
    initBackground();
    initTiles();
    initMenu();
    return true;
}

void GameScene::initBackground()
{
    auto backdrop = Sprite::create("BG.png");
    float tempH = backdrop->getBoundingBox().size.height;
    float screenH = Director::getInstance()->getVisibleSize().height;
    float scale = screenH / tempH;
    backdrop->setScale(scale);
    backdrop->setAnchorPoint(Vec2(0, 0));
    auto origin = Director::getInstance()->getVisibleOrigin();
    backdrop->setPosition(origin);
    backdrop->setTag(0);
    this->addChild(backdrop, -1);
}

void GameScene::initMenu()
{
    float bgWidth = this->getChildByTag(0)->getBoundingBox().size.width;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    MenuItemFont* mainMenu = MenuItemFont::create(
                                                  "Main \nMenu",
                                                  CC_CALLBACK_1(GameScene::mainMenu, this));
    
    cocos2d::Menu* menu = Menu::create(mainMenu, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(origin.x + bgWidth+((visibleSize.width-bgWidth)/2),origin.y + visibleSize.height/2));
    this->addChild(menu, 1);
}

void GameScene::initTiles()
{
    tile = new GameTile[tilesW*tilesH];
    position = new Vec2[tilesW*tilesH];
    
    // background size divided in 9 x 9
    Rect bgSize = this->getChildByTag(0)->getBoundingBox();
    Vec2 singleTileSize = Vec2(bgSize.size.width/tilesW, bgSize.size.height/tilesH);
    
    for (int h = 0; h < tilesH; h++)
    {
        for (int w = 0; w < tilesW; w++)
        {
            //create an image with and set its scale to imgSize/singleTileSize
            tile[WH].sprite = Sprite::create("empty.png");
            tile[WH].sprite->setAnchorPoint(Vec2(0, 0));
            float scaleW = singleTileSize.x/tile[WH].sprite->getBoundingBox().size.width;
            float scaleH = singleTileSize.y/tile[WH].sprite->getBoundingBox().size.height;
            scaleW = (scaleW*85)/100;
            scaleH = (scaleH*85)/100;
            tile[WH].sprite->setScale(scaleW, scaleH);
            //set position to be singleTileSize*w, singeTileSize*h
            
            Vec2 positionCurrentTile = Vec2(singleTileSize.x*w, singleTileSize.y*h);
            positionCurrentTile.add(Director::getInstance()->getVisibleOrigin());
            positionCurrentTile.add(Vec2(5, 5));
            position[WH] = positionCurrentTile;
            tile[WH].sprite->setPosition(position[WH]);
            tile[WH].sprite->setTag(1);
            
            //Listener for when the tile is touched
            auto touchListener = EventListenerTouchOneByOne::create();
            touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, tile[WH].sprite);
            
            this->addChild(tile[WH].sprite);
        }
    }
    for (int i = 0; i < 9; i++){
        Rect bgSize = this->getChildByTag(0)->getBoundingBox();
        Vec2 singleSquareSize = Vec2(bgSize.size.width/tilesW *3, bgSize.size.height/tilesH *3);
        
        squareWonO[i].sprite = Sprite::create("o.png");
        squareWonO[i].sprite->setAnchorPoint(Vec2(0, 0));
        float scaleWO = singleSquareSize.x/squareWonO[i].sprite->getBoundingBox().size.width;
        float scaleHO = singleSquareSize.y/squareWonO[i].sprite->getBoundingBox().size.height;
        scaleWO = (scaleWO*85)/100;
        scaleHO = (scaleHO*85)/100;
        squareWonO[i].sprite->setScale(scaleWO, scaleHO);
        squareWonO[i].sprite->setOpacity(0);
        
        squareWonX[i].sprite = Sprite::create("x.png");
        squareWonX[i].sprite->setAnchorPoint(Vec2(0, 0));
        float scaleWX = singleSquareSize.x/squareWonX[i].sprite->getBoundingBox().size.width;
        float scaleHX = singleSquareSize.y/squareWonX[i].sprite->getBoundingBox().size.height;
        //scaleWX = (scaleWX*85)/100;
        //scaleHX = (scaleHX*85)/100;
        squareWonX[i].sprite->setScale(scaleWX, scaleHX);
        squareWonX[i].sprite->setOpacity(0);
    }
    squareWonO[0].sprite->setPosition(position[0]);
    squareWonO[1].sprite->setPosition(position[3]);
    squareWonO[2].sprite->setPosition(position[6]);
    
    squareWonO[3].sprite->setPosition(position[27]);
    squareWonO[4].sprite->setPosition(position[30]);
    squareWonO[5].sprite->setPosition(position[33]);

    squareWonO[6].sprite->setPosition(position[54]);
    squareWonO[7].sprite->setPosition(position[57]);
    squareWonO[8].sprite->setPosition(position[60]);
    
    
    squareWonX[0].sprite->setPosition(position[0]);
    squareWonX[1].sprite->setPosition(position[3]);
    squareWonX[2].sprite->setPosition(position[6]);

    squareWonX[3].sprite->setPosition(position[27]);
    squareWonX[4].sprite->setPosition(position[30]);
    squareWonX[5].sprite->setPosition(position[33]);
    
    squareWonX[6].sprite->setPosition(position[54]);
    squareWonX[7].sprite->setPosition(position[57]);
    squareWonX[8].sprite->setPosition(position[60]);
    for (int i = 0; i < 9; i++){
        this->addChild(squareWonX[i].sprite, 3);
        this->addChild(squareWonO[i].sprite, 3);
    }
    if (aiActiveN == 2){
        ai_game();
    }
}

//--------------------------------------------------------
//				TILES update
//--------------------------------------------------------
bool GameScene::onTouchBegan(Touch* touch, Event * event)
{
    //tag to identify sprites
    if (event->getCurrentTarget()->getTag() == 1)
    {
        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);
        for (int h = 0; h < tilesH; h++)
        {
            for (int w = 0; w < tilesW; w++)
            {
                if (tile[WH].sprite->getBoundingBox().containsPoint(location))
                {
                    if(tile[WH].active == true){
                        if(tile[WH].used == false)
                        {
                            tile[WH].used = true;
                            if (turn){
                                tile[WH].selected = 1;
                                tile[WH].sprite->setTexture("x.png");
                                turn = !turn;
                            }
                            else
                            {
                                tile[WH].selected = 2;
                                tile[WH].sprite->setTexture("o.png");
                                turn = !turn;
                            }
                            
                            Rect bgSize = this->getChildByTag(0)->getBoundingBox();
                            Vec2 singleTileSize = Vec2(bgSize.size.width/tilesW, bgSize.size.height/tilesH);
                            float scaleW = tile[WH].sprite->getBoundingBox().size.width/singleTileSize.x;
                            float scaleH = tile[WH].sprite->getBoundingBox().size.height/singleTileSize.y;
                            scaleW = (scaleW*85)/100;
                            scaleH = (scaleH*85)/100;
                            tile[WH].sprite->setScale(scaleH, scaleW);
                            
                            int won = checkVictory();
                            
                            if ( won != 0){
                                Director::getInstance()->replaceScene(WinScene::createScene(won));
                            }
                            updateActiveTiles(WH);
                            if (aiActiveN == 1){
                                ai_computerTurn();
                        
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool GameScene::ai_game(){
    
    ai_computerTurn();
    
    if (checkVictory() == 0){
        auto delay = DelayTime::create(0.25f);
        auto gameAction = CallFunc::create(CC_CALLBACK_0(GameScene::ai_game, this));
        auto seq = Sequence::create(delay, gameAction, NULL);
        this->runAction(seq);
    }
    return true;
}

int GameScene::ai_selectBestPosition(){
    return rand()% (9*9);
}

void GameScene::ai_computerTurn(){
    bool goodTile = false;
    while (goodTile == false){
        int selected;
        if (ai_activeSquare == 0){
            selected = rand()% (9*9);
        }
        else
        {
            selected = ai_selectBestPosition();
        }
        if(tile[selected].active == true){
            if(tile[selected].used == false)
            {
                goodTile = true;
                tile[selected].used = true;
                if (turn){
                    tile[selected].selected = 1;
                    tile[selected].sprite->setTexture("x.png");
                    turn = !turn;
                }
                else
                {
                    tile[selected].selected = 2;
                    tile[selected].sprite->setTexture("o.png");
                    turn = !turn;
                }
                
                Rect bgSize = this->getChildByTag(0)->getBoundingBox();
                Vec2 singleTileSize = Vec2(bgSize.size.width/tilesW, bgSize.size.height/tilesH);
                float scaleW = tile[selected].sprite->getBoundingBox().size.width/singleTileSize.x;
                float scaleH = tile[selected].sprite->getBoundingBox().size.height/singleTileSize.y;
                scaleW = (scaleW*85)/100;
                scaleH = (scaleH*85)/100;
                tile[selected].sprite->setScale(scaleH, scaleW);
                
                int won = checkVictory();
                
                if ( won != 0){
                    Director::getInstance()->replaceScene(WinScene::createScene(won));
                }
                updateActiveTiles(selected);
            }
        }
    }
}


void GameScene::updateActiveTiles(int lastSelected){
    for (int i = 0; i< 9*9; i++){
        tile[i].active = false;
    }
    int temp = lastSelected;
    while (temp >= 27){
        temp = temp -27;
    }
    if (temp > 17){
        while (temp >= 21){
            temp = temp - 3;
        }
    }
    else if(temp > 8){
        while (temp >=12){
            temp = temp-3;
        }
    }
    else
    {
        while (temp >= 3){
            temp = temp-3;
        }
    }
    int startingPos;
    switch (temp){
        case 0:
            startingPos = 0;
            break;
        case 1:
            startingPos = 3;
            break;
        case 2:
            startingPos = 6;
            break;
        case 9:
            startingPos = 27;
            break;
        case 10:
            startingPos = 30;
            break;
        case 11:
            startingPos = 33;
            break;
        case 18:
            startingPos = 54;
            break;
        case 19:
            startingPos = 57;
            break;
        case 20:
            startingPos = 60;
            break;
    }
    ai_activeSquare = temp+1;
    
    setSquareWon(0);
    setSquareWon(3);
    setSquareWon(6);

    setSquareWon(27);
    setSquareWon(30);
    setSquareWon(33);
    
    setSquareWon(54);
    setSquareWon(57);
    setSquareWon(60);

    
    setActive(startingPos);
    for (int i = 0; i< 9*9; i++){
        if(tile[i].active == false){
            if(tile[i].selected == 0){
                tile[i].sprite->setColor(Color3B::RED);
                tile[i].sprite->setOpacity(100);
            }
        }
        else{
            tile[i].sprite->setColor(Color3B::WHITE);
            tile[i].sprite->setOpacity(255);
        }
    }
}

void GameScene::setActive(int startingPos){
    int pos[10];
    pos[1] = startingPos;
    pos[2] = startingPos+1;
    pos[3] = startingPos+2;
    pos[4] = pos[1]+9;
    pos[5] = pos[2]+9;
    pos[6] = pos[3]+9;
    pos[7] = pos[4]+9;
    pos[8] = pos[5]+9;
    pos[9] = pos[6]+9;
    
    for (int i = 1; i < 10; i++){
        //if(squareWon[i] == 0){
            tile[pos[i]].active = true;
        //}
    }
}

void GameScene::setSquareWon(int startingPos){
    int pos[10];
    pos[1] = startingPos;
    pos[2] = startingPos+1;
    pos[3] = startingPos+2;
    pos[4] = pos[1]+9;
    pos[5] = pos[2]+9;
    pos[6] = pos[3]+9;
    pos[7] = pos[4]+9;
    pos[8] = pos[5]+9;
    pos[9] = pos[6]+9;
    
    Rect bgSize = this->getChildByTag(0)->getBoundingBox();
    Vec2 singleTileSize = Vec2(bgSize.size.width/tilesW, bgSize.size.height/tilesH);
    
    for (int i = 1; i < 10; i++){
        if(squareWon[i] == 2){
            if(tile[pos[i]].selected == 0){
                tile[pos[i]].selected = 1;
                tile[pos[i]].used = true;
                tile[pos[i]].sprite->setTexture("x.png");
                tile[pos[i]].sprite->setColor(Color3B::WHITE);
                tile[pos[i]].sprite->setOpacity(255);
                float scaleW = tile[pos[i]].sprite->getBoundingBox().size.width/singleTileSize.x;
                float scaleH = tile[pos[i]].sprite->getBoundingBox().size.height/singleTileSize.y;
                scaleW = (scaleW*85)/100;
                scaleH = (scaleH*85)/100;
                tile[pos[i]].sprite->setScale(scaleH, scaleW);
            }
        }
        else if (squareWon[i] == 1){
            if(tile[pos[i]].selected == 0){
                tile[pos[i]].selected = 2;
                tile[pos[i]].used = true;
                tile[pos[i]].sprite->setTexture("o.png");
                tile[pos[i]].sprite->setColor(Color3B::WHITE);
                tile[pos[i]].sprite->setOpacity(255);
                float scaleW = tile[pos[i]].sprite->getBoundingBox().size.width/singleTileSize.x;
                float scaleH = tile[pos[i]].sprite->getBoundingBox().size.height/singleTileSize.y;
                scaleW = (scaleW*85)/100;
                scaleH = (scaleH*85)/100;
                tile[pos[i]].sprite->setScale(scaleH, scaleW);
            }
        }
    }
    checkVictory();
}

int GameScene::checkVictory(){
    
    squareWon[1] = checkVictorySmallGrid(0);
    squareWon[2] = checkVictorySmallGrid(3);
    squareWon[3] = checkVictorySmallGrid(6);
    
    squareWon[4] = checkVictorySmallGrid(27);
    squareWon[5] = checkVictorySmallGrid(30);
    squareWon[6] = checkVictorySmallGrid(33);
    
    squareWon[7] = checkVictorySmallGrid(54);
    squareWon[8] = checkVictorySmallGrid(57);
    squareWon[9] = checkVictorySmallGrid(60);
    
    for (int i = 1; i < 10; i ++){
     if (squareWon[i] == 1){
         squareWonX[i-1].sprite->setOpacity(255);
     }
     else if (squareWon[i] == 2){
         squareWonO[i-1].sprite->setOpacity(255);
     }
    }
    
    if (squareWon[1] == squareWon[2] && squareWon[2] == squareWon[3] && squareWon[1] != 0)
        return squareWon[1];
    
    else if (squareWon[4] == squareWon[5] && squareWon[5] == squareWon[6]&& squareWon[4] != 0)
        return squareWon[4];
    
    else if (squareWon[7] == squareWon[8] && squareWon[8] == squareWon[9]&& squareWon[7] != 0)
        return squareWon[7];
    
    else if (squareWon[1] == squareWon[4] && squareWon[4] == squareWon[7]&& squareWon[1] != 0)
        return squareWon[1];
    
    else if (squareWon[2] == squareWon[5] && squareWon[5] == squareWon[8]&& squareWon[2] != 0)
        return squareWon[2];
    
    else if (squareWon[3] == squareWon[6] && squareWon[6] == squareWon[9]&& squareWon[3] != 0)
        return squareWon[3];
    
    else if (squareWon[1] == squareWon[5] && squareWon[5] == squareWon[9]&& squareWon[1] != 0)
        return squareWon[1];
    
    else if (squareWon[3] == squareWon[5] && squareWon[5] == squareWon[7]&& squareWon[3] != 0)
        return squareWon[3];
    
    else
        return 0;
}

int GameScene::checkVictorySmallGrid(int startingPos){
    int pos1 = startingPos;
    int pos2 = startingPos+1;
    int pos3 = startingPos+2;
    int pos4 = pos1+9;
    int pos5 = pos2+9;
    int pos6 = pos3+9;
    int pos7 = pos4+9;
    int pos8 = pos5+9;
    int pos9 = pos6+9;
    
    if (tile[pos1].selected == tile[pos2].selected && tile[pos2].selected == tile[pos3].selected){
        if (tile[pos1].selected != 0){
            return tile[pos1].selected;
        }
    }
    if (tile[pos4].selected == tile[pos5].selected && tile[pos5].selected == tile[pos6].selected){
        if (tile[pos4].selected != 0){
            return tile[pos4].selected;
        }
    }
    if (tile[pos7].selected == tile[pos8].selected && tile[pos8].selected == tile[pos9].selected){
        if (tile[pos7].selected != 0){
            return tile[pos7].selected;
        }
    }
    if (tile[pos1].selected == tile[pos4].selected && tile[pos4].selected == tile[pos7].selected){
        if (tile[pos1].selected != 0){
            return tile[pos1].selected;
        }
    }
    if (tile[pos2].selected == tile[pos5].selected && tile[pos5].selected == tile[pos8].selected){
        if (tile[pos2].selected != 0){
            return tile[pos2].selected;
        }
    }
    if (tile[pos3].selected == tile[pos6].selected && tile[pos6].selected == tile[pos9].selected){
        if (tile[pos3].selected != 0){
            return tile[pos3].selected;
        }
    }
    if (tile[pos1].selected == tile[pos5].selected && tile[pos5].selected == tile[pos9].selected){
        if (tile[pos1].selected != 0){
            return tile[pos1].selected;
        }
    }
    if (tile[pos3].selected == tile[pos5].selected && tile[pos5].selected == tile[pos7].selected){
        if (tile[pos3].selected != 0){
            return tile[pos3].selected;
        }
    }
    return 0;
}


//--------------------------------------------------------
//				BUTTON CALLBACKS
//--------------------------------------------------------
void GameScene::mainMenu(cocos2d::Ref* sender)
{
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
