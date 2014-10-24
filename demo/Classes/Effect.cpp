#include "Effect.h"
USING_NS_CC;


void Effect::CoinEffect(cocos2d::Node * render_node)
{
    auto sprite = Sprite::create("effect/specialAttack.jpg");
    sprite->setVisible(false);  
    auto blend_func =BlendFunc();
    blend_func.dst =GL_ONE_MINUS_SRC_ALPHA;
    blend_func.src = GL_ONE;
    sprite->setBlendFunc(blend_func);
    sprite->setScaleX(0.01);
    sprite->setRotation(0);
    sprite->setOpacity(0);
    sprite->setAnchorPoint(Vec2(0.5, 0.5)); 
    sprite->setPosition3D(Vec3(845, 545, 50));
    auto speed = 0.5;
    auto rotate = 360; 
    auto startRotate = 0;
     auto scaleAction = ScaleBy::create(speed, 100, 1);
     auto rotateAction = RotateBy::create(speed, rotate);
     auto attack_ = Spawn::create(scaleAction, rotateAction,NULL);
     auto attack = EaseCircleActionOut::create(attack_);
     auto fadeAction = FadeIn::create(speed);
     auto fadeAction2 = FadeOut::create(0);
     auto scaleAction2 = ScaleBy::create(0, 0.01, 1);
     auto rotateAction2 = RotateTo::create(0, startRotate);
     auto restore = Spawn::create(fadeAction2, scaleAction2, rotateAction2, Hide::create(),NULL);
     auto sequence = Sequence::create(Show::create(), attack, fadeAction, restore,NULL);
     sprite->runAction(sequence);
     render_node->addChild(sprite);
}
