#ifndef __EYEBROW_H__
#define __EYEBROW_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Eyebrow {
    
public:
    Eyebrow();
    ~Eyebrow();
	
	void draw();
    void intoPlace(float posX, float posY, float posZ);
   	void adjust(float angle);
	
	
private:
    float _posX;
    float _posY;
    float _posZ;
    float _angle;
    
};

#endif
