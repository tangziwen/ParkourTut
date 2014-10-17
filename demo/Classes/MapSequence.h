#ifndef MAP_SEQUENCE_H
#define MAP_SEQUENCE_H 
#include <vector>
	 struct SequenceInfo
	{
		unsigned short L;//left track
		unsigned short M;//middle track
		unsigned short R;//right track
		SequenceInfo(unsigned short l,unsigned m,unsigned short r);
	} ;



#define EMPTY 0
#define MONSTER 1
#define COIN 2


class MapSequence{
public:
	MapSequence(const char* sequence_file);
	MapSequence();
	SequenceInfo pump();
	int getTotalSequence();
	void rewind();
	bool isEOS();
private:
	void add(unsigned short l,unsigned short m,unsigned short r);
	int index;
	std::vector <SequenceInfo> sequence;
};

#endif