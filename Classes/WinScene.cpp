#include "WinScene.h"
USING_NS_CC;

cocos2d::Scene* WinScene::createScene(int winner)
{
    cocos2d::Scene* scene = Scene::create();
    auto layer = WinScene::create(winner);
    
    scene->addChild(layer);
    
    return scene;
}

WinScene* WinScene::create(int winner){
    WinScene* ws = new WinScene();
    if (ws && ws->init(winner))
    {
        ws->autorelease();
        return ws;
    }else
    {
        delete ws;
        ws = NULL;
        return NULL;
    }
}

bool WinScene::init(int newWinner)
{
    winner = newWinner;
    initMenu();
    
    if (!Layer::init())
    {
        return false;
    }
    return true;
}

void WinScene::initMenu(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cocos2d::Label* label = Label::createWithTTF("Winner", "fonts/Marker Felt.ttf", 70);
    label->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 5 * 4)));
    this->addChild(label, 2);
    
    if (winner == 1){
        label->setString("X WON");
    }
    else {
        label->setString("O WON");
    }
    MenuItemFont* mainMenu = MenuItemFont::create("Main menu",
                                                    CC_CALLBACK_1(WinScene::menuMainMenu, this));
    
    
    MenuItemFont* exit = MenuItemFont::create("Quit",
                                              CC_CALLBACK_1(WinScene::menuCloseCallback, this));
    
    cocos2d::Menu* menu = Menu::create(mainMenu, exit, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 5 * 2)));
    this->addChild(menu, 1);
}

void WinScene::menuMainMenu(cocos2d::Ref* sender){
    Director::getInstance()->replaceScene(MainMenu::createScene());
}

void WinScene::menuCloseCallback(cocos2d::Ref*pSender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
