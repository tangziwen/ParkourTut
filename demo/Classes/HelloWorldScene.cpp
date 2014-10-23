#include "HelloWorldScene.h"

USING_NS_CC;
#include <functional>
#include "PG_Controller.h"
#include  "CCMoveBy3D.h"
#include "MapSequence.h"
#include "cocostudio/CCSGUIReader.h"




cocos2d::DrawNode3D * HelloWorld::drawnode=nullptr;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	auto camera_1 = Camera::createOrthographic(960,640,0,1000);
	camera_1->setCameraFlag(CameraFlag::USER2);
	auto bg_layer= Layer::create();
	scene->addChild(camera_1);



	scene->addChild(bg_layer,-100,"back ground");
	auto the_background= Sprite::create("back_ground.jpg");
	the_background->setName("back ground!!!!");
	the_background->setAnchorPoint(Vec2(0,0));
	bg_layer->addChild(the_background);
	bg_layer->setCameraMask(4);

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    
	scene->addChild(layer,100,"game main");
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) 
    {  
        return false;
    }
	this->gold=0;
	player =new Player();

	this->addChild(player->getPlayer(),10);
	
    player->getPlayer()->setPosition3D(Vec3(0,0,-40));
	
	
	auto s = Director::getInstance()->getWinSize();
	auto camera =Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 200);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setPosition3D(Vec3(0, 15, -15));
	camera->lookAt(Vec3(0,0,-60),Vec3(0,1,0));
    this->addChild(camera);


	drawnode=DrawNode3D::create();
	this->addChild(drawnode);
	

	CCLOG("%f %f %f",camera->getPosition3D().x,camera->getPosition3D().y,camera->getPosition3D().z);
	this->setCameraMask((unsigned short )CameraFlag::USER1);
	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	schedule(schedule_selector(HelloWorld::upDateScene));
	auto map_sequence=new MapSequence();
	controller.insertMapSequence(map_sequence);   
    controller.preGenerate(this);
    auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HUD/HUD.json");
    gold_text = (cocos2d::ui::TextAtlas *)widget->getChildByName("gold");
    gold_text->setStringValue("0");
    this->addChild(widget);
    return true;
}



void HelloWorld::upDateScene(float dt)
{
	controller.randomGenerate(player,this,dt);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
	 
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	this->touch_begin_pos=std::move(touch->getLocation());
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	this->touch_end_pos=std::move(touch->getLocation());

	Vec2 diff =touch_end_pos-touch_begin_pos;
	diff.normalize();
	auto a =std::move(Vec2(1,0));//horizontal line
	auto result =Vec2::dot(diff,a);
	const int TURN_LEFT=1;
	const int TURN_RIGHT=2;
	if(abs(result)>0.7)// left or right 
	{
		if(result>0)//right
		{
			if(player->getPlayer()->getPositionX()<10 && !player->getPlayer()->getActionByTag(TURN_RIGHT) && !player->getPlayer()->getActionByTag(TURN_LEFT))
			{
				auto action = MoveBy3D::create(0.2,Vec3(10,0,0),false);
				action->setTag(TURN_RIGHT);
				this->player->getPlayer()->runAction(action);
			}
			CCLOG("right");
		}else //left
		{
			if(player->getPlayer()->getPositionX()>-10 && !player->getPlayer()->getActionByTag(TURN_RIGHT) && !player->getPlayer()->getActionByTag(TURN_LEFT))
			{
				auto action = MoveBy3D::create(0.2,Vec3(-10,0,0),false);
				action->setTag(TURN_LEFT);
				this->player->getPlayer()->runAction(action);
			}
			CCLOG("left");
		}
	}else{  //up or down 
		if(diff.y>0)
		{
			CCLOG("up");
		}else
		{
			CCLOG("down");
		}
	}
}

void HelloWorld::earnGold()
{
    this->gold++;
    char str[100];
    sprintf(str,"%d",gold);
    gold_text->setStringValue(str);
}

void HelloWorld::hitPlayer() 
{
    auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Menu/Menu.json");
    this->addChild(widget);
    auto restart_btn = (cocos2d::ui::Button *)widget->getChildByName("restart");
    restart_btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {  
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {  
              CCLOG("hehe cao ni ma");
              Director::getInstance()->replaceScene(HelloWorld::createScene());
        }  
    }); 
    this->pauseSchedulerAndActions();
    this->_actionManager->removeAllActions();
    this->player->getPlayer()->stopAllActions();
    //this->getParent()->pause();
}

void HelloWorld::onRestartTouch(cocos2d::ui::TouchEventType event)
{
    if ( event == ui::TOUCH_EVENT_ENDED )
    {
        CCLOG("hehe cao ni ma");
    }
}
