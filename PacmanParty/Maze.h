#ifndef __MAZE_H__
#define __MAZE_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Section.h"

class Maze {
	
public:
    
	Maze();
	~Maze();
    void setTextureOn(bool state);

	void draw();


private:
    Section* _section;
    bool _textureOn;
};



#endif
