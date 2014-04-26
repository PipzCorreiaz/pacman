#ifndef __AMMUNITION_H__
#define __AMMUNITION_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Bullet.h"

class Ammunition {
    
public:
    Ammunition();
    ~Ammunition();
    
    void intoPlace(float x, float y);
    void draw();
    
private:
    float _x;
    float _y;
    Bullet* _bullet;
    
};

#endif
