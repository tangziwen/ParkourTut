#ifndef PLAYER_H
#define PLAYER_H 
#include "cocos2d.h"
class Player{
public:
	Player();
	cocos2d::Sprite3D * getPlayer();
private:
	cocos2d::Sprite3D * player;

};
#endif