#ifndef  DEMO_UTILITY_H
#define DEMO_UTILITY_H  
#include <cocos2d.h>
using namespace cocos2d;

// the utility is for general using
namespace DemoUtility{
     //caculate the relatvie translation for the model
	 Vec3 translateRelative(Vec3 Pos,Vec3 rotateAngle,Vec3 Speed);
     // get the player current track
	 int getTrack(float x);
}
#endif