#include "PG_Controller.h"

#include <stdlib.h>
#include <time.h>

#include "Obstacle.h"
#include "DecorationAction.h"
#include "Coin.h"
#include "GroundAction.h"

using namespace cocos2d;

#define TRACK_0 0
#define TRACK_1 1
#define TRACK_2 2


PG_Controller::PG_Controller():current_sequence(nullptr)
{
	srand((unsigned int )clock());// initialize the random seed
}

PG_Controller::~PG_Controller()
{
	
}

void PG_Controller::randomGenerate(Player * player,cocos2d::Node * render_node)
{
	generateGround(render_node);
	static int step=0;
	step ++;
	generateObstacle(player,render_node);
	
	if(step >= 2)
	{
		generateTree(player,render_node);
		step=0;
	}
	
}

void PG_Controller::generateTree(Player * player,cocos2d::Node * render_node)
{

	//left side tree 
	auto sprite_left =cocos2d::Sprite3D::create("tree.c3b");
	//sprite_left->setRotation3D(Vec3(-90,0,0));
	sprite_left->setScale(0.1);
	render_node->addChild(sprite_left,10); 
	auto action = new DecorationAction();
	sprite_left->setPosition3D(Vec3(-20,0,-250));
	sprite_left->runAction(action);
	sprite_left->setName("tree");

	//right side tree
	auto sprite_right =cocos2d::Sprite3D::create("tree.c3b");
	//sprite_right->setRotation3D(Vec3(-90,0,0));
	sprite_right->setScale(0.1);
	render_node->addChild(sprite_right,10);
	auto action_2 = new DecorationAction();
	sprite_right->setPosition3D(Vec3(20,0,-250));
	sprite_right->runAction(action_2);
	render_node->setCameraMask(2);
	sprite_right->setName("tree");
}

void PG_Controller::generateObstacle(Player * player,cocos2d::Node * render_node)
{


	auto sequence =pump();
	switch(sequence.L)
	{
	case MONSTER:
		{
			auto a = new Obstacle();
			a->initDefault(player);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (-10,0,-250));
			a->getSprite()->setRotation3D(Vec3(0,180,0));
		}
		break;
	case EMPTY:
		//do nothing 
		break;
	case COIN:
		{
			auto a =new Coin(player);
			a->bindToLayer(render_node);
			a->getSprite()->setPosition3D(Vec3 (-10,0,-250));
			a->getSprite()->setRotation3D(Vec3(90,0,180));
		}
		break;
	}
	
	switch(sequence.M)
	{
	case MONSTER:
		{
			auto a = new Obstacle();
			a->initDefault(player);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (0,0,-250));
			a->getSprite()->setRotation3D(Vec3(0,180,0));
		}
		break;
	case EMPTY:
		// do nothing 
		break;
	case COIN:
		{
			auto a =new Coin(player);
			a->bindToLayer(render_node);
			a->getSprite()->setPosition3D(Vec3 (0,0,-250));
			a->getSprite()->setRotation3D(Vec3(90,0,180));
		}
		break;
	}

	switch(sequence.R)
	{
	case MONSTER:
		{
			auto a = new Obstacle();
			a->initDefault(player);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (10,0,-250));
			a->getSprite()->setRotation3D(Vec3(0,180,0));
		}
		break;
	case EMPTY:
		//do nothing
		break;
	case COIN:
		{
			auto a =new Coin(player);
			a->bindToLayer(render_node);
			a->getSprite()->setPosition3D(Vec3 (10,0,-250));
			a->getSprite()->setRotation3D(Vec3(90,180,180));
		}
		break;
	}
	
}

void PG_Controller::generateCoin(Player * player,cocos2d::Node *render_node)
{

}

void PG_Controller::insertMapSequence(MapSequence * map_sequence)
{
	this->sequence_list.push_back(map_sequence);
}

SequenceInfo PG_Controller::pump()
{
	if(!current_sequence || current_sequence->isEOS())
	{
		if(current_sequence)
		{
			current_sequence->rewind();
			int index= rand()%this->sequence_list.size();
			current_sequence =this->sequence_list[index];
			return pump();
		}
		else
		{
			int index= rand()%this->sequence_list.size();
			current_sequence =this->sequence_list[index];
			return pump();
		}
	}else
	{
		return current_sequence->pump();
	}
}

void PG_Controller::generateGround(cocos2d::Node * render_node)
{
	auto road= Sprite::create("ground.png"); 
	render_node->addChild(road,1);
	road->setPosition3D(Vec3(0,-1,-250));
	road->setRotation3D(Vec3(90,0,0));
	render_node->setCameraMask(2);
	auto action =new GroundAction();
	road->runAction(action);
}

