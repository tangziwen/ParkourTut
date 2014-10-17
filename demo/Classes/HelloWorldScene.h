#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PG_Controller.h"
#include "Player.h"
#include "DrawNode3D.h"
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	virtual  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//virtual void onEnter();

	void upDateScene(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	static cocos2d::DrawNode3D * drawnode;
private:
	Player * player;
	cocos2d::Vec2 touch_begin_pos;
	cocos2d::Vec2 touch_end_pos;
	cocos2d::Camera * the_camera;
	PG_Controller controller;
	
};

#endif // __HELLOWORLD_SCENE_H__
