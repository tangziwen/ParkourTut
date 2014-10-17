#include "CCMoveBy3D.h"

#include <stdarg.h>

#include "2d/CCSprite.h"
#include "2d/CCNode.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCActionInstant.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventDispatcher.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN

static float PI_OVER_180 =(3.1415927 / 180.0);
MoveBy3D* MoveBy3D::create(float duration, const Vec3& deltaPosition,bool is_relative)
{
	MoveBy3D *ret = new (std::nothrow) MoveBy3D();
	ret->initWithDuration(duration, deltaPosition);
	ret->autorelease();
	ret->setIsRelative(is_relative);
	return ret;
}

MoveBy3D* MoveBy3D::clone() const 
{
	// no copy constructor
	auto a = new (std::nothrow) MoveBy3D();
	a->initWithDuration(_duration, _positionDelta);
	a->autorelease();
	return a;
}

MoveBy3D* MoveBy3D::reverse(void) const 
{
	return MoveBy3D::create(_duration, Vec3( -_positionDelta.x, -_positionDelta.y,-_positionDelta.z));
}

void MoveBy3D::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	_previousPosition = _startPosition = target->getPosition3D();
}

void MoveBy3D::update(float time)
{
	if (_target)
	{
		if(!_isRelative)
		{
			#if CC_ENABLE_STACKABLE_ACTIONS
						Vec3 currentPos = _target->getPosition3D();
						Vec3 diff = currentPos - _previousPosition;
						_startPosition = _startPosition + diff;
						Vec3 newPos =  _startPosition + (_positionDelta * time);
						_target->setPosition3D(newPos);
						_previousPosition = newPos;
			#else
						_target->setPosition3D(_startPosition + _positionDelta * time);
			#endif // CC_ENABLE_STACKABLE_ACTIONS
		}else
		{
			Vec3 currentPos = _target->getPosition3D();
			Vec3 diff = currentPos - _previousPosition;
			_startPosition = _startPosition + diff;
			Vec3 newPos =  _startPosition;
			Vec3 rotation=_target->getRotation3D();
			float yaw= rotation.y;
			float pitch = rotation.x;
			float roll =rotation.z;
			newPos.z += cos(PI_OVER_180 *pitch)*cos(PI_OVER_180 * yaw )*_positionDelta.z*time 
				- sin(PI_OVER_180 * yaw )*_positionDelta.x*time 
					+sin(PI_OVER_180 *pitch)*_positionDelta.y*time;  
			newPos.x+= sin(PI_OVER_180 * yaw)*_positionDelta.z* time  
					+cos(PI_OVER_180 *yaw)*cos(PI_OVER_180 * roll)*_positionDelta.x*time+
						sin(PI_OVER_180 * roll)*_positionDelta.y*time;
			newPos.y+= - sin(PI_OVER_180 *pitch)*cos(PI_OVER_180 * yaw )*_positionDelta.z*time 
						+ cos(PI_OVER_180 * roll)*cos(PI_OVER_180 *pitch)*_positionDelta.y*time
							- sin(PI_OVER_180*roll)*_positionDelta.x*time;  
			_target->setPosition3D(newPos);
			_previousPosition = newPos;
		}
	}

}

bool MoveBy3D::initWithDuration(float duration, const Vec3& deltaPosition)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_positionDelta = deltaPosition;
		return true;
	}
}

void MoveBy3D::setIsRelative(bool is_relative)
{
	this->_isRelative=is_relative;
}

NS_CC_END