#ifndef __GHOST_H__
#define __GHOST_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include "Character.h"

class Ghost : public Character {

public:
    Ghost(int posx, int posy, int id);
    
    bool getTrouble();
    bool getHidden();
    
    void setSpeed(float speed);
    void setTrouble(bool trouble);
    void setHidden(bool value);
   // void setColor(float a, float b, float c);
    
    void draw();
    void update(float dt);
    void move(float dist);
    void shoot(int i);

    void backAgain();
    
    
private:
    int _ghostId;
    bool _trouble;
    bool _hidden;

};

#endif
