#pragma once
#include <string>
#include <random>
#include <time.h>
#include "cocos2d.h"
#include "GameTile.h"
#include "MainMenu.h"
#include "WinScene.h"

class GameScene : public cocos2d::Layer
{
public:
	//--------------------------------------------------------
	//				SCENE CREATION/DELETION
	//--------------------------------------------------------
	~GameScene();
	static cocos2d::Scene* createScene(int AI);
    static GameScene* create(int AI);
	virtual bool init(int AI);
	virtual void initBackground();
	virtual void initMenu();
	virtual void initTiles();

	//--------------------------------------------------------
	//				TILES update
	//--------------------------------------------------------
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event * event) override;

    bool ai_game();
    void ai_computerTurn();
    int ai_selectBestPosition();
    
    void updateActiveTiles(int lastSelectd);
    void setActive(int startingPos);
    void setSquareWon(int startingPos);

    
    int checkVictory();
    int checkVictorySmallGrid(int startingPos);

	//--------------------------------------------------------
	//				BUTTON CALLBACKS
	//--------------------------------------------------------
	virtual void mainMenu(cocos2d::Ref* sender);

private:
	GameTile* tile = nullptr;

	//array of the positions on the window tiles need to be in
	cocos2d::Vec2* position = nullptr; 

    bool turn = true;
    int aiActiveN;
    
    int ai_activeSquare = 0;
    
	int tilesH = 9; //number of tiles in height
	int tilesW = 9; //number of tiles in width
    
    int squareWon[10];
    GameTile squareWonX[9];
    GameTile squareWonO[9];
    
};
