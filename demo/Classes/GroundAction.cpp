#include "GroundAction.h"
USING_NS_CC;


bool GroundAction::isDone() const
{
	return !_target;
}

void GroundAction::step(float time)
{
	_target->setPosition3D(_target->getPosition3D()+Vec3(0,0,100*time));
	_target->setGlobalZOrder(-10000);
	if(_target->getPositionZ()>-21)
	{
		_target->removeFromParent(); 
		_target=nullptr;
	}
}
