#ifndef  GROUND_ACTION_H
#define GROUND_ACTION_H  
#include "cocos2d.h"
#include "Player.h"
class GroundAction: public cocos2d::Action
{
public:
	virtual bool isDone() const;
	virtual void step(float time);
};
#endif