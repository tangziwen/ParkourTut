#ifndef  COIN_ACTION_H
#define COIN_ACTION_H
#include "cocos2d.h"
#include "Player.h"
// the action for the coin,check every frame whether the player get the coin
class CoinAction  : public cocos2d::Action {
public:
	CoinAction();
	CoinAction(Player * player,cocos2d::Node * node);
	virtual bool isDone() const;
	virtual void step(float time);
	private:
        //the coin action only trigger once.
        bool is_triggered;
        cocos2d::Node * render_node;
		float angle;
		Player * player;
};


#endif