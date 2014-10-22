#include "MapSequence.h"
#include <assert.h>
#include  "../cocos2d/external/tinyxml2/tinyxml2.h"
using namespace std;
using namespace tinyxml2; 
MapSequence::MapSequence(const char* sequence_file):
	index(0)
{
	XMLDocument doc; 
	doc.LoadFile(sequence_file);
	auto map = doc.RootElement();
	auto node =map->FirstChildElement("Node");
	while(node)
	{
		auto left =node->FirstChildElement("Left");
		auto middle=node->FirstChildElement("Middle");
		auto right=node->FirstChildElement("Right"); 
		add(atoi (left->GetText()),atoi (middle->GetText()),atoi (right->GetText()));
		node=node->NextSiblingElement();
	}
	
}

//just for test
MapSequence::MapSequence():
	index(0)
{
	add(0,0,2);
	add(0,0,2);
	add(0,0,2);
	add(0,0,2);
	add(0,0,2);
	add(0,0,2);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,2,0);
	add(0,0,1);
	add(0,1,0);
	add(1,0,0);
	add(1,1,0);
	add(0,1,0);
	add(1,0,0);
	add(1,1,0);
	add(0,0,1);
	add(0,1,0);
	add(1,1,0);
	add(1,1,0);
	add(0,1,1);
	add(0,1,1);
	add(0,1,1);
	add(0,1,1);
	add(0,1,1);
	add(0,1,1);
	add(0,0,1);
	add(0,1,0);
	add(1,1,0);
	add(1,1,0);
	add(0,1,1);
	add(0,1,1);
	add(0,1,1);
}

SequenceInfo MapSequence::pump()
{
	auto result =std::move(SequenceInfo(0,0,0));
	if(index<this->sequence.size()-1)
	{
		result= this->sequence[index];
		index++;
		return result;
	}
	else
	{
		//error
		assert(-1);
	}
}

int MapSequence::getTotalSequence()
{
	return this->sequence.size();
}

void MapSequence::rewind()
{
	index=0;
}

bool MapSequence::isEOS()
{
	return index>=sequence.size()-1;
}

void MapSequence::add(unsigned short l,unsigned short m,unsigned short r)
{
	sequence.push_back(SequenceInfo(l,m,r));
}


SequenceInfo::SequenceInfo(unsigned short l,unsigned m,unsigned short r)
{
	this->L=l;
	this->M=m;
	this->R=r;
}
