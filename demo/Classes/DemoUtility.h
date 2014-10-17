#ifndef  DEMO_UTILITY_H
#define DEMO_UTILITY_H  
#include <cocos2d.h>
using namespace cocos2d;
namespace DemoUtility{
	 Vec3 translateRelative(Vec3 Pos,Vec3 rotateAngle,Vec3 Speed);
	 int getTrack(float x);
}
#endif