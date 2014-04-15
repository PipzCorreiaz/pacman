#ifndef PacmanLove_Character_h
#define PacmanLove_Character_h

#include <iostream>
#include <string>
#include <vector>
#include "Constraints.h"
#include "Wizard.h"
#include "Eye.h"

class Character {
    
public:
    
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
    
};


#endif
