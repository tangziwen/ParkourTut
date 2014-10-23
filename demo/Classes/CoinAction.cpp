#include "CoinAction.h"
#include "HelloWorldScene.h"
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
		if(_target->getPositionZ()>-40 && _target->getPositionZ()<10 )// enter the front
		{
			Sprite3D * sprite = dynamic_cast<Sprite3D * >(_target);
			Vec3 vertices[8];

			auto player_aabb= player->getPlayer()->getAABB();
            /*
			if(sprite->getAABB().intersects(player_aabb))
			{
				sprite->setVisible(false);
                auto a = (HelloWorld * )this->render_node;
                a->gold_text->setString("100");
				CCLOG("get Money !!!");
			}*/
            auto dist =sprite->getPosition3D().distance(player->getPlayer()->getPosition3D());
            if(dist<5)
            {
                _target->setVisible(false);
                auto a = (HelloWorld * )this->render_node;
                a->earnGold();
                CCLOG("get Money !!!");
                _target->removeFromParent();
                _target=nullptr;
                return ;
            }
		}
		if(_target->getPositionZ()>=10)
		{
			_target->removeFromParent();
			_target=nullptr;
		}
	}
}

CoinAction::CoinAction():player(NULL),angle(0),render_node(NULL)
{

}

CoinAction::CoinAction(Player * player,cocos2d::Node * node):angle(0)
{
	this->player=player;
    this->render_node = node;
}
