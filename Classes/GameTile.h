#pragma once
#include "cocos2d.h"

class GameTile
{
public:
	cocos2d::Sprite* sprite = nullptr;
    bool used = false;
    
    int selected = 0;
    bool active = true;
    
private:
    
};

