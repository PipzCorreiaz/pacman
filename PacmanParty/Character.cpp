#include "Character.h"
#include "Wizard.h"



Character::Character() {
    _life = 100;
}

float Character::getX() {
    return _posX;
}

float Character::getY() {
    return _posY;
}

float Character::getZ() {
    return _posZ;
}

float Character::getSpeed() {
	return _speed;
}

int Character::getDirection() {
    return _direction;
}

int Character::getAngle() {
	return _angle;
}


void Character::setX(float x) {
    _posX = x;
}

void Character::setY(float y) {
    _posY = y;
}

void Character::setDirection(int direction) {
    _direction = direction;
}

void Character::setAngle(int angle) {
    _angle = angle;
}

void Character::setColor(float a,float b,float c, float shine){
    
    // glColor4f(a, b, c, 0.5);
    
    GLfloat mat_ambient[] = {a, b, c};
    GLfloat mat_diffuse[] = {a, b, c};
    GLfloat mat_specular[] = {a, b, c};
    GLfloat mat_shine = shine;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
    
}

void Character::move(float dist) {
    float x = getX();
    float y = getY();
    int dir = getDirection();
    float limit = ((Wizard::getInstance().getMapWidth()) / 2);

    if (x <= -limit && dir == LEFT && y == 0) {
        setX(limit);
    } else if (x >= limit && dir == RIGHT && y == 0) {
        setX(-limit);
    } else {
        switch (dir) {
            case UP:
                setY(y + dist);
                break;
            case DOWN:
                setY(y - dist);
                break;
            case LEFT:
                setX(x - dist);
                break;
            case RIGHT:
                setX(x + dist);
                break;
            default:
                break;
        }
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

int Character::turnBack(){
    int direction = getDirection();
    int backDirection = 0;
    switch (direction) {
        case UP:
            backDirection = DOWN;
            break;
        case LEFT:
            backDirection = RIGHT;
            break;
        case DOWN:
            backDirection = UP;
            break;
        case RIGHT:
            backDirection = LEFT;
            break;
        default:
            break;
    }
    return backDirection;
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








