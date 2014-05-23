#include "Bullet.h"
#include "Wizard.h"


Bullet::Bullet() {
    _x = _y = 0.0f;
    _z = 0.5f;
    _speed = 80;
    _active = true;
    _quadratics = gluNewQuadric();
    gluQuadricNormals(_quadratics, GLU_SMOOTH);
    _vX = _vY = 1.0f; //TROLOLOL
}

Bullet::Bullet(float x, float y, float z, int direction) {
    _x = x;
    _y = y;
    _z = z;
    _speed = 20;
    _active = true;
    _quadratics = gluNewQuadric();
    gluQuadricNormals(_quadratics, GLU_SMOOTH);
    setSpeed(direction);
}

Bullet::~Bullet() {
    gluDeleteQuadric(_quadratics);
}

void Bullet::intoPlace(float x, float y) {
    _x = x;
    _y = y;
}

bool Bullet::isActive() {
    return _active;
}

void Bullet::setSpeed(int direction) {
    switch (direction) {
        case UP: 
            _vY = _speed;
            _vX = 0;
            break;
        case DOWN:
            _vY = -_speed;
            _vX = 0;
            break;
        case LEFT:
            _vY = 0;
            _vX = -_speed;
            break;
        case RIGHT:
            _vY = 0;
            _vX = _speed;
            break;
    }
}

void Bullet::draw() {

    if(_active){
        
        glPushMatrix();
        
        glTranslatef(_x, _y, _z);
        if (_vY == 0) {
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        } else if (_vX == 0) {
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        }
        
        GLfloat mat_ambient[] = {1, 0, 0};
        GLfloat mat_diffuse[] = {1, 0, 0};
        GLfloat mat_specular[] = {1, 0, 0};
        GLfloat mat_shine = 100.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
        
        gluCylinder(_quadratics, 0.3f, 0.3f, 0.7f, 8, 8);
        glTranslatef(0.0f, 0.0f, 0.7f);
        gluCylinder(_quadratics, 0.3f, 0.0f, 0.4f, 8, 8);
        
        glPopMatrix();
        
    }
}

int Bullet::update(float dt) {
    int deadGhost = 0;
    float lastX = _x;
    float lastY = _y;
    _x += _vX * dt;
    _y += _vY * dt;
    int lastIndex = Wizard::getInstance().positionToIndex(lastX, lastY);
    int index = Wizard::getInstance().positionToIndex(_x, _y);
    
    if ((abs(index - lastIndex) > 1 && abs(index - lastIndex) < 10)
        || (abs(index - lastIndex) > 55 && abs(index - lastIndex) < 500)) {
        //std::cout << "SERIOUS PROBLEMS: talk to Filipa, she'll know what to do!" << std::endl;
    }
    
    char symbol = Wizard::getInstance().getMapSymbol(_x, _y);

    if (symbol == WALL) {
        _active = false;
    } else if (symbol == GHOST) {
        deadGhost = Wizard::getInstance().shotGhost(_x, _y);
        _active = false;
    }
    return deadGhost;
}