#ifndef  COIN_ACTION_H
#define COIN_ACTION_H
#include "cocos2d.h"
#include "Player.h"
class CoinAction  : public cocos2d::Action {
public:
	CoinAction();
	CoinAction(Player * player,cocos2d::Node * node);
	virtual bool isDone() const;
	virtual void step(float time);
	private:
        cocos2d::Node * render_node;
		float angle;
		Player * player;
};


#endif