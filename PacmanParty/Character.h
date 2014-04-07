#ifndef PacmanLove_Character_h
#define PacmanLove_Character_h

#include "Eye.h"
#include <string.h>

class Character {
    
public:
    Character();
    ~Character();
    float getX();
    float getY();
    float getZ();
    float getDirection();
    float getPauseAngle();
    float getSpeed();
    
    void setUp(bool up);
    void setDown(bool down);
    void setLeft(bool left);
    void setRight(bool right);
    void setX(float x);
    void setY(float y);
    
    bool isUp();
    bool isDown();
    bool isLeft();
    bool isRight();
    bool isStopped();
    bool virtual isGhost() = 0;
    void virtual backAgain() = 0;

    
    
    void virtual draw() = 0;
    void up();
    void down();
    void left();
    void right();
    void virtual move(float dist) = 0;
    void resetMove();
    void resetPressedKeys();
    void pause();
    
    bool _upPressed, _downPressed, _leftPressed, _rightPressed;
    bool _turnedUp, _turnedDown, _turnedLeft, _turnedRight;
     

    
protected:
    float _posX, _posY, _posZ, _direction, _pauseAngle, _speed;
    bool _up, _down, _left, _right;
	Eye* _eye;
    
    
};


#endif
