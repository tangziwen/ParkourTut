#include "ObstacleAction.h"
#include "DemoUtility.h"

USING_NS_CC;
#include "MainScene.h"


bool ObstacleAction::isDone() const
{
	return !_target;
}

void ObstacleAction::step(float time)
{
	if(_target)
	{
		_target->setPosition3D (DemoUtility::translateRelative(_target->getPosition3D(),_target->getRotation3D(),Vec3(0,0,150*time)));
		if(_target->getPositionZ()>-40 && _target->getPositionZ()<10 )// enter the front
		{
			 Sprite3D * sprite = dynamic_cast<Sprite3D * >(_target);
             /*
			 auto player_aabb= player->getPlayer()->getAABB();

			 player_aabb._max-=Vec3(5,5,5);
			 player_aabb._min+=Vec3(5,5,5);
			 if(sprite->getAABB().intersects(player_aabb))
			 {
				 //do something when hit
				 CCLOG("hit");
			 }
             */
             auto dist =Vec3(sprite->getPositionX(),0,sprite->getPositionZ()).distance(player->getPlayer()->getPosition3D());
             if(dist<5)
             {
                 _target->setVisible(false);
                 auto a = (GameScene * )this->render_node;
                 a->hitPlayer();
                 _target->setScale(2);
                 CCLOG("HIT !!!");
                 _target->removeFromParent();
                 _target=nullptr;
                 return ;
             }
        
		}
		if(_target->getPositionZ()>=35)
		{
			_target->removeFromParent();
			_target=nullptr;
		}
	}
}

ObstacleAction::ObstacleAction(Player * player,Node * render_node)
{
	this->player=player;
    this->render_node = render_node;
}

ObstacleAction::ObstacleAction():player(nullptr),render_node(nullptr)
{

}
