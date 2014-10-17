#ifndef  COIN_ACTION_H
#define COIN_ACTION_H
#include "cocos2d.h"
#include "Player.h"
class CoinAction  : public cocos2d::Action {
public:
	CoinAction();
	CoinAction(Player * player);
	virtual bool isDone() const;
	virtual void step(float time);
	private:
		float angle;
		Player * player;
};


#endif