#pragma once
#include "cocos2d.h"
#include "MainMenu.h"
#include "GameScene.h"

class WinScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene(int winner);
    static WinScene* create(int winner);
    virtual bool init(int newWinner);
    virtual void initMenu();
    
    virtual void menuMainMenu(cocos2d::Ref* sender);
    virtual void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
    int winner;
};
