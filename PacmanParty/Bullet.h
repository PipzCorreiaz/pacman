#ifndef __BULLET_H__
#define __BULLET_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Constraints.h"

class Bullet {

public:
    Bullet(float x, float y, float z, int direction);
    ~Bullet();
    bool isActive();

    void draw();
    void update(float dt);

private:
    float _x;
    float _y;
    float _z;
    float _speed;
    float _vX;
    float _vY;
    bool _active;
    GLUquadric* _quadratics;

    void setSpeed(int direction);


};

#endif