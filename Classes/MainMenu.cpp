#include "MainMenu.h"
USING_NS_CC;

cocos2d::Scene* MainMenu::createScene()
{
	cocos2d::Scene* scene = Scene::create();
	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	initMenu();

	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void MainMenu::initMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Sprite *title = Sprite::create("Title.png");
	//title->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 5 * 4)));
	//this->addChild(title, 2);

	cocos2d::Label* label = Label::createWithTTF("ULTIMATE TicTacToe", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 5 * 4)));
	this->addChild(label, 2);

	MenuItemFont* mainMenuStartGameAi = MenuItemFont::create(
		"SinglePlayer",
		CC_CALLBACK_1(MainMenu::menuStartGameAi, this));
    MenuItemFont* mainMenuStartGame = MenuItemFont::create(
        "Multiplayer",
        CC_CALLBACK_1(MainMenu::menuStartGame, this));
    MenuItemFont* mainMenuStartGameAiOnly = MenuItemFont::create(
        "AI Only",
        CC_CALLBACK_1(MainMenu::menuStartGameAiOnly, this));
	MenuItemFont* mainMenuExit = MenuItemFont::create(
		"Quit",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	cocos2d::Menu* menu = Menu::create(mainMenuStartGameAiOnly, mainMenuStartGameAi, mainMenuStartGame, mainMenuExit, nullptr);
	menu->alignItemsVertically();
    menu->setPosition(Vec2((origin.x + visibleSize.width / 2), (origin.y + visibleSize.height / 5 * 2)));
	this->addChild(menu, 1);
}



void MainMenu::menuCloseCallback(cocos2d::Ref*pSender)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenu::menuStartGame(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene(0));
}

void MainMenu::menuStartGameAi(cocos2d::Ref* sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene(1));
}


void MainMenu::menuStartGameAiOnly(cocos2d::Ref* sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene(2));
}