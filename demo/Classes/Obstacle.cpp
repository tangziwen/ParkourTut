#include "Obstacle.h"
using namespace cocos2d;
#include "DemoUtility.h"
#include "ObstacleAction.h"
Obstacle::Obstacle()
	:obstacle_sprite(nullptr)
{
	
}

void Obstacle::initByFile(const char * file_name)
{

}

void Obstacle::initDefault(Player * player,Node * render_node)
{
	this->obstacle_sprite = Sprite3D::create("model/piglet.c3b");
    obstacle_sprite->setTexture("model/zhu0928.jpg");
	obstacle_sprite->retain();
	obstacle_sprite->setZOrder(100);
	obstacle_sprite->setScale(0.1);
	auto aabb = obstacle_sprite->getAABB();
	auto action = new ObstacleAction(player,render_node);
	obstacle_sprite->runAction(action);
	this->length=1;

    
    auto aniamtion =Animation3D::create("model/piglet.c3b");
    auto animate =Animate3D::createWithFrames(aniamtion,135,147);
    obstacle_sprite->runAction(RepeatForever::create (animate));
    
}

cocos2d::Sprite3D * Obstacle::getSprite()
{
	return this->obstacle_sprite;
}

void Obstacle::bindTo(cocos2d::Node * render_node)
{
	render_node->addChild(this->obstacle_sprite);
	render_node->setCameraMask(2);
}

void Obstacle::setLength(int new_length)
{
	this->length=new_length;
}

int Obstacle::getLength()
{
	return this->length;
}

void Obstacle::update(float delta)
{
	/*
	this->setPosition3D(0,0,delta);
	this->setPosition3D(DemoUtility::translateRelative(this->getPosition3D(),this->getRotation3D(),Vec3(0,0,-1*delta)));
	CCLOG("update");
	*/
}

