#include "Coin.h"
#include "CoinAction.h"
USING_NS_CC;
Coin::Coin(Player * player)
{
	this->player=player;
	this->sprite =Sprite3D::create("coin.c3b");
	this->sprite->setRotation3D(Vec3(-90,0,90));
	this->sprite->setScale(0.3);
	auto action = new CoinAction(this->player);
	sprite->runAction(action)  
		; 
}

void Coin::bindToLayer(cocos2d::Node * render_node)
{
	render_node->addChild(this->sprite,10);
	render_node->setCameraMask(2);
} 

cocos2d::Sprite3D * Coin::getSprite()
{
	return this->sprite;
}
