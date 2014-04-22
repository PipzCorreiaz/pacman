#include "Bullet.h"
#include "Wizard.h"

Bullet::Bullet(float x, float y, float z, int direction) {
    _x = x;
    _y = y;
    _z = z;
    _active = true;
    setSpeed(direction);
}

void Bullet::setSpeed(int direction) {
    float speed = 10;
    switch (direction) {
        case UP: 
            _vY = speed;
            _vX = 0;
            break;
        case DOWN:
            _vY = -speed;
            _vX = 0;
            break;
        case LEFT:
            _vY = 0;
            _vX = -speed;
            break;
        case RIGHT:
            _vY = 0;
            _vX = speed;
            break;
    }
}

void Bullet::draw() {

    if(_active){
        
        glPushMatrix();
        
        glTranslatef(_x, _y, _z);
        
        GLfloat mat_ambient[] = {1, 0, 0};
        GLfloat mat_diffuse[] = {1, 0, 0};
        GLfloat mat_specular[] = {1, 0, 0};
        GLfloat mat_shine = 100.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
        
        glutSolidSphere(0.25f, 5, 5);
        
        glPopMatrix();
        
    }
}

void Bullet::update(float dt) {
    _x += _vX * dt;
    _y += _vY * dt;
    char symbol = Wizard::getInstance().getMapSymbol(_x, _y);

    if (symbol == GHOST || symbol == WALL) {
        _active = false;
    }
}