#include "Ammunition.h"

Ammunition::Ammunition() {
    _x = _y = 0.0f;
    _bullet = new Bullet();
}

Ammunition::~Ammunition() {
}

void Ammunition::intoPlace(float x, float y) {
    _x = x;
    _y = y;
}

void Ammunition::draw() {
    glPushMatrix();
    
    _bullet->intoPlace(_x, _y);
    _bullet->draw();
    _bullet->intoPlace(_x - 0.6f, _y);
    _bullet->draw();
    _bullet->intoPlace(_x + 0.6f, _y);
    _bullet->draw();
    
    glPopMatrix();
}
