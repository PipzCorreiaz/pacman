#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Particle {

public:
    Particle();
    ~Particle();
    void reset(float posX, float posY, float posZ, float vx, float vy, float vz);
    void move(float dx, float dy, float dz);
    void draw();
    
public:
    float _posX, _posY, _posZ;
    float _vX, _vY, _vZ;

};

#endif
