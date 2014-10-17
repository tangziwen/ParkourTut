#include "CoinAction.h"
USING_NS_CC;
bool CoinAction::isDone() const
{
	return !_target;
}

void CoinAction::step(float time)
{
	if(_target)
	{
		_target->setRotation3D(Vec3(90,angle,180));
		angle+=time*140;
		_target->setPosition3D (_target->getPosition3D()+Vec3(0,0,100*time));
		if(_target->getPositionZ()>-20 && _target->getPositionZ()<10 )// enter the front
		{
			Sprite3D * sprite = dynamic_cast<Sprite3D * >(_target);
			Vec3 vertices[8];

			auto player_aabb= player->getPlayer()->getAABB();

			player_aabb._max-=Vec3(5,5,5);
			player_aabb._min+=Vec3(5,5,5);
			if(sprite->getAABB().intersects(player_aabb))
			{
				sprite->setVisible(false);
				CCLOG("get Money !!!");
			}
		}
		if(_target->getPositionZ()>=10)
		{
			_target->removeFromParent();
			_target=nullptr;
		}
	}
}

CoinAction::CoinAction():player(NULL),angle(0)
{

}

CoinAction::CoinAction(Player * player):angle(0)
{
	this->player=player;
}
