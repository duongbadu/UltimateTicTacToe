#pragma once
#include "cocos2d.h"
#include "GameScene.h"

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void initMenu();
	virtual void menuStartGame(cocos2d::Ref* sender);
    virtual void menuStartGameAi(cocos2d::Ref* sender);
    virtual void menuStartGameAiOnly(cocos2d::Ref* sender);
    virtual void menuCloseCallback(cocos2d::Ref* pSender);

	//implement the "static create()" function manually
	CREATE_FUNC(MainMenu);
};
