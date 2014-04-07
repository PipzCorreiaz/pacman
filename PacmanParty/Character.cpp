#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Character.h"


Character::Character(){}

Character::~Character(){}
float Character::getX(){
    return _posX;
}


float Character::getY(){
    return _posY;
}

float Character::getZ(){
    return _posZ;
}

float Character::getDirection(){
	return _direction;
}

float Character::getSpeed(){
	return _speed;
}

float Character::getPauseAngle(){
    return _pauseAngle;
}

bool Character::isUp(){
    return _up;   
}

bool Character::isDown(){
    return _down;
}

bool Character::isLeft(){
    return _left;
}

bool Character::isRight(){
    return _right;
}

bool Character::isStopped(){
    return !isUp() && !isDown() && !isLeft() && !isRight();
}

void Character::resetMove(){
    _up = _down = _left = _right = false;
}

void Character::resetPressedKeys(){
    _upPressed = _downPressed = _leftPressed = _rightPressed = false;
}

void Character::setUp(bool up){
    _up = up;
}
void Character::setDown(bool down){
    _down = down;
}
void Character::setLeft( bool left){
    _left = left;
}
void Character::setRight(bool right){
    _right = right;
}

void Character::setX(float x){
    _posX = x;
}

void Character::setY(float y){
    _posY = y;
}

void Character::pause(){

    resetMove(); //limpar as flags para pacman parar
    
    _direction = 0;
    _pauseAngle = -90;
    
}

void Character::up(){
    resetMove();
	_up = true;

    
}

void Character::down(){
    resetMove();
    _down = true;
}

void Character::left(){
    resetMove();
    _left = true;
}

void Character::right(){
    resetMove();
    _right = true;
}










