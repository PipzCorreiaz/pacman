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
    int getLife();
    
    void setX(float x);
    void setY(float y);
    void setColor(float a,float b,float c, float shine);
    void setDirection(int direction);
    void setAngle(int angle);
    char getLastSymbol();
    void setLastSymbol(char symbol);
    
    void move(float dist);
    void turn(int direction);
    int turnBack();
    std::vector<float> nextPosition(float dist);
    
    void virtual draw() = 0;
    void drawOnHUD(float x, float y);
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
    char _lastSymbol;
    bool _drawingHUD;
    
};


#endif
