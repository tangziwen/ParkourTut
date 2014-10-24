#ifndef DECORATION_ACTION_H
#define DECORATION_ACTION_H
#include "cocos2d.h"

//this action is for the decoration for game,the decoration mean the element that don't take role in game play. 
class DecorationAction : public cocos2d::Action{
public:
	virtual bool isDone() const;
	virtual void step(float time);
};

#endif