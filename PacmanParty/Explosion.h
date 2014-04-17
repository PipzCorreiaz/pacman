#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include "Constraints.h"
#include "Particle.h"

class Explosion {

public:
    Explosion(float pacX, float pacY, float pacZ);
    ~Explosion();
    void checkParticles();
    void resetParticles(float pacX, float pacY, float pacZ);
    void moveParticles(float dt);
    void draw();
    
    
public:
    Particle* _particles[PARTICLES];
    bool _areThereAnyParticles;

};

#endif
