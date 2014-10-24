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

void PG_Controller::randomGenerate(Player * player,cocos2d::Node * render_node,float dt)
{
	static float  step=0;
    static float obstacle_step=0;
	step +=dt;
    obstacle_step += dt;
    if(obstacle_step>0.4)
    {
        generateObstacle(player,render_node);
        obstacle_step=0;
    }
	if(step >= 3.87)
	{
		generateScene(player,render_node);
		step=0;  
	}
}

void PG_Controller::generateScene(Player * player,cocos2d::Node * render_node)
{
	auto sprite_left =cocos2d::Sprite3D::create("model/scene.c3b");  
	sprite_left->setScale(0.2); 
    sprite_left->setRotation3D(Vec3(0,90,0));
	render_node->addChild(sprite_left,10); 
	auto action = new DecorationAction();
	sprite_left->setPosition3D(Vec3(0,-5,-550));  
	sprite_left->runAction(action); 
	sprite_left->setName("scene");
    render_node->setCameraMask(2);
}

void PG_Controller::generateObstacle(Player * player,cocos2d::Node * render_node)
{
	auto sequence =pump();
	switch(sequence.L)
	{
	case MONSTER:
		{
			auto a = new Obstacle();
			a->initDefault(player,render_node);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (-10,-5,-250));
		}
		break;
	case EMPTY:
		//do nothing 
		break;
	case COIN:
		{
			auto a =new Coin(player,render_node);
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
			a->initDefault(player,render_node);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (0,-5,-250));
		}
		break;
	case EMPTY:
		// do nothing 
		break;
	case COIN:
		{
			auto a =new Coin(player,render_node);
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
			a->initDefault(player,render_node);
			a->bindTo(render_node);
			a->getSprite()->setPosition3D(Vec3 (10,-5,-250));
		}
		break;
	case EMPTY:
		//do nothing
		break;
	case COIN:
		{
			auto a =new Coin(player,render_node);
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

void PG_Controller::preGenerate(cocos2d::Node * render_node)
{
    auto scene_1 =cocos2d::Sprite3D::create("model/scene.c3b");  
    scene_1->setScale(0.2); 
    scene_1->setRotation3D(Vec3(0,90,0));
    render_node->addChild(scene_1,10); 
    auto action_1 = new DecorationAction();
    scene_1->setPosition3D(Vec3(0,-5,0));  
    scene_1->runAction(action_1); 
    render_node->setCameraMask(2);

    auto scene_2 =cocos2d::Sprite3D::create("model/scene.c3b");  
    scene_2->setScale(0.2); 
    scene_2->setRotation3D(Vec3(0,90,0));
    render_node->addChild(scene_2,10); 
    auto action_2 = new DecorationAction();
    scene_2->setPosition3D(Vec3(0,-5,-470));  
    scene_2->runAction(action_2); 
    render_node->setCameraMask(2);
}

