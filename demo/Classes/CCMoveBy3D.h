#ifndef CC_MOVE_BY_3D_H
#define CC_MOVE_BY_3D_H

#include <vector>

#include "2d/CCAction.h"
#include "2d/CCAnimation.h"
#include "base/CCProtocols.h"
#include "base/CCVector.h"

#include "2d/CCActionInterval.h"

NS_CC_BEGIN


//moveBy class for 3d Object
class  MoveBy3D : public ActionInterval
{
public:
	/** creates the action */
	static MoveBy3D* create(float duration, const Vec3& deltaPosition,bool is_relative=false);

	//
	// Overrides
	//
	virtual MoveBy3D* clone() const override;
	virtual MoveBy3D* reverse(void) const  override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;
	void setIsRelative(bool is_relative);
CC_CONSTRUCTOR_ACCESS:
	MoveBy3D() {}
	virtual ~MoveBy3D() {}

	/** initializes the action */
	bool initWithDuration(float duration, const Vec3& deltaPosition);

protected:
	Vec3 _positionDelta;
	Vec3 _startPosition;
	Vec3 _previousPosition;
	bool _isRelative;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(MoveBy3D);
};






NS_CC_END
#endif