#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Eye.h"
#include "Constraints.h"

class Character {
    
public:
    Character(); //SO DEVE SER USADO PARA O HUD
    Character(float color[3]);
    float getX();
    float getY();
    float getZ();
    float getSpeed();
    int getDirection();
    int getAngle();
    int getLife();
    float* getColor();
    
    void setX(float x);
    void setY(float y);
    void setDirection(int direction);
    void setAngle(int angle);
    void setLife(int life);
    void setColor(float color[3]);
    char getLastSymbol();
    void setLastSymbol(char symbol);
    
    void move(float dist);
    void turn(int direction);
    int turnBack();
    std::vector<float> nextPosition(float dist);
    
    void virtual draw() = 0;
    void virtual update(float dt) = 0;
    
    void colorize(float c[3]);
    void virtual backAgain() = 0;
    
    
    int _previousX, _previousY;
    
    
protected:
    float _posX;
    float _posY;
    float _posZ;
    float _speed;
    int _direction;
    int _angle;
    float _color[3];
    float _shine;
	Eye* _eye;
    int _life;
    char _lastSymbol;
    bool _drawingHUD;
    
};


#endif
