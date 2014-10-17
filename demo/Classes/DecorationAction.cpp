#include "DecorationAction.h"
#include "DemoUtility.h"
USING_NS_CC;
bool DecorationAction::isDone() const
{
	return !_target;
}

void DecorationAction::step(float time)
{
	if(_target)
	{
		_target->setPosition3D (DemoUtility::translateRelative(_target->getPosition3D(),_target->getRotation3D(),Vec3(0,0,100*time)));
		if(_target->getPositionZ()>=35)
		{
			_target->removeFromParent(); 
			_target=nullptr;
		}
	} 
}




