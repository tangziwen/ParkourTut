#ifndef OBSTACLE_H
#define OBSTACLE_H  
#include "cocos2d.h"
#include "Player.h"
class Obstacle : public cocos2d::Sprite3D{
	public :
		Obstacle();
		void initByFile(const char * file_name);
		void initDefault(Player * player,cocos2d::Node * render_node);
		cocos2d::Sprite3D * getSprite();
		void bindTo(cocos2d::Node * render_node);
		void setLength(int new_length);
		int getLength();
		void update(float delta);
private:
	int length;
	cocos2d::Sprite3D * obstacle_sprite;
};

#endif