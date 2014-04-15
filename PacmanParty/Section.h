#ifndef PacmanLove_Section_h
#define PacmanLove_Section_h

#include "Wall.h"
#include "Ball.h"

class Section{
    
public:
	Section(int quadX, int quadY);
	~Section();
	
	void draw();
    
private:
	int _quadrantX;
	int _quadrantY;
    
};


#endif
