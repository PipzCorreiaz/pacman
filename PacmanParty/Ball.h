#ifndef __BALL_H__
#define __BALL_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Ball {
    
public:
    Ball();
    ~Ball();
    
    void draw();
    void intoPlace(float posX, float posY);
	void growth(float scale);
    
private:
    float _posX;
    float _posY;
    float _posZ;
    float _scale;
    
};

#endif
