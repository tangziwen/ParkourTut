#include "DemoUtility.h"
using namespace cocos2d;
#include <math.h>
#define PI_OVER_180 (3.141592653/180.0) 

namespace DemoUtility{


	cocos2d::Vec3 translateRelative(Vec3 Pos,Vec3 rotateAngle,Vec3 Speed)
	{
		Vec3 newPos =  Pos;
		float yaw= rotateAngle.y;
		float pitch = rotateAngle.x;
		float roll =rotateAngle.z;
		newPos.z += cos(PI_OVER_180 *pitch)*cos(PI_OVER_180 * yaw )*Speed.z
			- sin(PI_OVER_180 * yaw )*Speed.x 
			+sin(PI_OVER_180 *pitch)*Speed.y;  
		newPos.x+= sin(PI_OVER_180 * yaw)*Speed.z
			+cos(PI_OVER_180 *yaw)*cos(PI_OVER_180 * roll)*Speed.x+
			sin(PI_OVER_180 * roll)*Speed.y;
		newPos.y+= - sin(PI_OVER_180 *pitch)*cos(PI_OVER_180 * yaw )*Speed.z 
			+ cos(PI_OVER_180 * roll)*cos(PI_OVER_180 *pitch)*Speed.y
			- sin(PI_OVER_180*roll)*Speed.x; 
		return newPos;
	}

	int getTrack(float x)
	{
		if(x>=-10 && x<-5)
		{

			return 0;
		}
		else if(x>-5 && x<5)
		{
			return 1;
		}else if(x>5 && x<=10)
		{
			return 2;
		}
	}

}


