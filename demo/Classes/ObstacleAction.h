#ifndef OBSTACLE_ACTION_H
#define  OBSTACLE_ACTION_H 
#include "cocos2d.h"
#include "Player.h"
class ObstacleAction : public cocos2d::Action{
public:
	ObstacleAction (Player * player);
	ObstacleAction();
	virtual bool isDone() const;
	virtual void step(float time);
private:
	Player * player;
};
#endif