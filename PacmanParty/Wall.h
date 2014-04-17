#ifndef __WALL_H__
#define __WALL_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Constraints.h"
#include "Brick.h"


class Wall {
    
public:
    Wall();
    ~Wall();
    
    void resize(float width, float height);
    void intoPlace(float posx, float posy, float posz);
	void draw();
    
    
    
private:
    float _width;
    float _height;
    float _posX;
    float _posY;
    float _posZ;
    Brick* _brick;
    
    
    
};




#endif
