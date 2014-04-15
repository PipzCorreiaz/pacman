#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h"


float Character::getX(){
    return _posX;
}

float Character::getY(){
    return _posY;
}

float Character::getZ(){
    return _posZ;
}

float Character::getSpeed(){
	return _speed;
}

int Character::getDirection(){
    return _direction;
}

int Character::getAngle(){
	return _angle;
}

void Character::setX(float x){
    _posX = x;
}

void Character::setY(float y){
    _posY = y;
}

void Character::setDirection(int direction) {
    _direction = direction;
}

void Character::setAngle(int angle) {
    _angle = angle;
}

void Character::move(float dist){
    switch (getDirection()) {
        case UP:
            setY(getY() + dist);
            break;
        case DOWN:
            setY(getY() - dist);
            break;
        case LEFT:
            setX(getX() - dist);
            break;
        case RIGHT:
            setX(getX() + dist);
            break;
        default:
            break;
    }
}

 
void Character::turn(int direction) {
	
	setX(round(getX()));
	setY(round(getY()));
	
    switch (direction) {    
        case UP:
            setDirection(UP);
            setAngle(UP_ANGLE);
            break;
        case LEFT:
            setDirection(LEFT);
            setAngle(LEFT_ANGLE);
            break;
        case DOWN:
            setDirection(DOWN);
            setAngle(DOWN_ANGLE);
            break;
        case RIGHT:
            setDirection(RIGHT);
            setAngle(RIGHT_ANGLE);
            break;
        default:
            break;
    }
}

std::vector<float> Character::nextPosition(float dist) {
    
    std::vector<float> coords(2);

    coords[0] = getX();
    coords[1] = getY();
    
    switch (getDirection()) {
        case UP:
            coords[1] += dist;
            break;
        case LEFT:
            coords[0] -= dist;
            break;
        case DOWN:
            coords[1] -= dist;
            break;
        case RIGHT:
            coords[0] += dist;
            break;
        default:
            break;
    }
    
    return coords;
}








