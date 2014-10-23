#ifndef PG_CONTROLLER_H
#define  PG_CONTROLLER_H 
#include <cocos2d.h>
#include "MapSequence.h"
#include <stack>
#include "Player.h"
class PG_Controller
{
public:
	PG_Controller();
	~PG_Controller();
	void randomGenerate(Player * player, cocos2d::Node * render_node,float dt);
	void generateScene(Player * player,cocos2d::Node * render_node);
	void generateObstacle(Player * player,cocos2d::Node * render_node);
	void generateCoin(Player * player,cocos2d::Node *render_node);
	void generateGround(cocos2d::Node * render_node);
	void insertMapSequence(MapSequence * map_sequence);
    void preGenerate(cocos2d::Node * render_node);
private:
	SequenceInfo pump();
	void run(float dt);
	MapSequence * current_sequence;
	std::vector<MapSequence *> sequence_list;
};

#endif