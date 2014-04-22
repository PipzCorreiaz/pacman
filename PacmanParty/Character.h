#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Constraints.h"
#include "Eye.h"

class Character {
    
public:
    Character();
    float getX();
    float getY();
    float getZ();
    float getSpeed();
    int getDirection();
    int getAngle();
    
    void setX(float x);
    void setY(float y);
    void setDirection(int direction);
    void setAngle(int angle);
    
    void move(float dist);
    void turn(int direction);
    int turnBack();
    std::vector<float> nextPosition(float dist);
    
    void virtual draw() = 0;
    void virtual update(float dt) = 0;
    
    void virtual backAgain() = 0;
    
    
    int _previousX, _previousY;
    
    
protected:
    float _posX;
    float _posY;
    float _posZ;
    float _speed;
    int _direction;
    int _angle;
	Eye* _eye;
    int _life;

    
};


#endif
