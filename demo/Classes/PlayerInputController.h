#ifndef PLAYER_INPUT_CONTROLLER
#define PLAYER_INPUT_CONTROLLER
#include "cocos2d.h"
#include "Player.h"


//handle the player input.
class PlayerInputController{
public:
    PlayerInputController(Player * player);
    void receiveTouchBegin(cocos2d::Vec2 pos);
    void receiveTouchEnd(cocos2d::Vec2 pos);
private:
    Player * player;
    cocos2d::Vec2 touch_begin_pos;
    cocos2d::Vec2 touch_end_pos;
};

#endif // !PLAYER_INPUT_CONTROLLER
