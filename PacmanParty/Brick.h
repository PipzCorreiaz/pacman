#ifndef __BRICK_H__
#define __BRICK_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Brick {
    
public:
    Brick();
    ~Brick();
    
    void resize(float width, float height);
    void intoPlace(float posx, float posy, float posz);
	void draw();
    
    
private:
    
    float _width;
    float _height;
    float _posX;
    float _posY;
    float _posZ;
    
};




#endif
