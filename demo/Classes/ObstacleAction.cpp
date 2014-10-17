#include "ObstacleAction.h"
#include "DemoUtility.h"

USING_NS_CC;
#include "HelloWorldScene.h"


bool ObstacleAction::isDone() const
{
	return !_target;
}

void ObstacleAction::step(float time)
{
	if(_target)
	{
		_target->setPosition3D (DemoUtility::translateRelative(_target->getPosition3D(),_target->getRotation3D(),Vec3(0,0,-100*time)));
		if(_target->getPositionZ()>-20 && _target->getPositionZ()<10 )// enter the front
		{
			 Sprite3D * sprite = dynamic_cast<Sprite3D * >(_target);
			 Vec3 vertices[8];
			 HelloWorld::drawnode->clear();
			 sprite->getAABB().getCorners(vertices);
			 HelloWorld::drawnode->drawCube(vertices,Color4F(1,0,0,1));

			 auto player_aabb= player->getPlayer()->getAABB();

			 player_aabb._max-=Vec3(5,5,5);
			 player_aabb._min+=Vec3(5,5,5);
			 if(sprite->getAABB().intersects(player_aabb))
			 {
				 //do something when hit
				 CCLOG("hit");
			 }
		}
		if(_target->getPositionZ()>=35)
		{
			_target->removeFromParent();
			_target=nullptr;
		}
	}
}

ObstacleAction::ObstacleAction(Player * player)
{
	this->player=player;
}

ObstacleAction::ObstacleAction():player(nullptr)
{

}
