#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h"



Character::Character(){
	
}

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

int Character::getDirection(){
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
    _turnedUp = _turnedLeft = _turnedDown = _turnedRight = false;
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
    _turnedUp = true;
    _angle = UP;
    _direction = 180;
}

void Character::down(){
    resetMove();
    _down = true;
    _turnedDown = true;
    _angle = DOWN;
    _direction = 0;
}

void Character::left(){
    resetMove();
    _left = true;
    _turnedLeft = true;
    _angle = LEFT;
    _direction = -90;
}

void Character::right(){
    resetMove();
    _right = true;
    _turnedRight = true;
    _angle = RIGHT;
    _direction = 90;
}

void Character::move(float dist){
    
    if(isUp()){
        _posY = _posY + dist;
    }
    
    else if(isDown()){
        _posY = _posY - dist;
    }
    
    else if(isLeft()){
        _posX = _posX - dist;
    }
    else if(isRight()){
        _posX = _posX + dist;
    }
}

void Character::roundPosition() {
	
	switch (getDirection()) {    
        case UP:
			setY(ceil(getY()));
            break;
        case LEFT:
            setX(floor(getX()));
            break;
        case DOWN:
			setY(floor(getY()));
            break;
        case RIGHT:
            setX(ceil(getX()));
            break;
        default:
            break;
    }
}
 
void Character::turn(int direction) {
	
	//roundPosition();
	setX(round(getX()));
	setY(round(getY()));
	
    switch (direction) {    
        case UP:
            up();
            break;
        case LEFT:
            left();
            break;
        case DOWN:
            down();
            break;
        case RIGHT:
            right();
            break;
        default:
            break;
    }
}








