#include "MainScene.h"

USING_NS_CC;
#include <functional>
#include "PG_Controller.h"
#include  "CCMoveBy3D.h"
#include "MapSequence.h"
#include "cocostudio/CCSGUIReader.h"



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	auto camera_1 = Camera::createOrthographic(960,640,0,1000);
	camera_1->setCameraFlag(CameraFlag::USER2);
	auto bg_layer= Layer::create();
	scene->addChild(camera_1);

	scene->addChild(bg_layer,-100,"model/back ground");
	auto the_background= Sprite::create("model/back_ground.jpg");
	the_background->setAnchorPoint(Vec2(0,0));
	bg_layer->addChild(the_background);
	bg_layer->setCameraMask(4);

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
   
	scene->addChild(layer,100,"game main");
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool GameScene::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) 
    {  
        return false;
    }
	this->current_gold=0;
	player =new Player();

	this->addChild(player->getPlayer(),10);
	
    player->getPlayer()->setPosition3D(Vec3(0,0,-40));
	
	input_controller = new PlayerInputController(player);
	auto s = Director::getInstance()->getWinSize();
	auto camera =Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 200);
	camera->setCameraFlag(CameraFlag::USER1);
	camera->setPosition3D(Vec3(0, 15, -15));
	camera->lookAt(Vec3(0,0,-60),Vec3(0,1,0));
    this->addChild(camera);



	CCLOG("%f %f %f",camera->getPosition3D().x,camera->getPosition3D().y,camera->getPosition3D().z);
	this->setCameraMask((unsigned short )CameraFlag::USER1);
	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	schedule(schedule_selector(GameScene::upDateScene));
	auto map_sequence=new MapSequence();
	pg_controller.insertMapSequence(map_sequence);   
    pg_controller.preGenerate(this);
    auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HUD/HUD.json");
    auto pause_button=(cocos2d::ui::Button *)widget->getChildByName("Button_1");
    pause_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        static bool is_pause = false;
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {  
            if(!is_pause){
                Director::getInstance()->pause();
                is_pause = true;
            }else
            {
                is_pause = false;
                Director::getInstance()->resume();
            }

        }  
    }); 
    gold_text = (cocos2d::ui::TextAtlas *)widget->getChildByName("gold");
    gold_text->setStringValue("0");
    this->addChild(widget);
    return true;
}



void GameScene::upDateScene(float dt)
{
	pg_controller.randomGenerate(player,this,dt);
}


bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    input_controller->receiveTouchBegin(touch->getLocation());
	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    input_controller->receiveTouchEnd(touch->getLocation());
}

void GameScene::earnGold()
{
    this->current_gold++;
    char str[100];
    sprintf(str,"%d",current_gold);
    gold_text->setStringValue(str);
}

void GameScene::hitPlayer() 
{
    auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Menu/Menu.json");
    this->addChild(widget);
    auto restart_btn = (cocos2d::ui::Button *)widget->getChildByName("restart");
    restart_btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {  
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {  
              Director::getInstance()->replaceScene(GameScene::createScene());
        }  
    }); 
    this->pauseSchedulerAndActions();
    this->_actionManager->removeAllActions();
    this->player->getPlayer()->stopAllActions();
}
