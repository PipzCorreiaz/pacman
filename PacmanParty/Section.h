#ifndef __SECTION_H__
#define __SECTION_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Wall.h"

class Section{
    
public:
	Section();
	~Section();
    
	void setQuadrant(int x, int y);
	void draw();
    
private:
    Wall* _wall;
	int _quadrantX;
	int _quadrantY;
    
};


#endif
