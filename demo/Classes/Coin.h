#ifndef COIN_H
#define COIN_H 
#include "Player.h"
#include "cocos2d.h"
class Coin{
public:
	Coin(Player * player,cocos2d::Node * render_node);
	void bindToLayer(cocos2d::Node * render_node);
	cocos2d::Sprite3D * getSprite();
private:
	cocos2d::Sprite3D * sprite;
	Player * player;
};


#endif // !COIN_H
