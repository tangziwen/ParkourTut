#ifndef DECORATION_ACTION_H
#define DECORATION_ACTION_H
#include "cocos2d.h"
class DecorationAction : public cocos2d::Action{
public:
	virtual bool isDone() const;
	virtual void step(float time);
};

#endif