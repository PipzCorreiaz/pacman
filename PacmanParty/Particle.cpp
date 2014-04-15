#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Particle.h"

Particle::Particle(){
    _posX = 0;
    _posY = 0;
    _posZ = 0;
    _vX = 0;
    _vY = 0;
    _vZ = 0;
}

Particle::~Particle(){
    
}

void Particle::reset(float posX, float posY, float posZ, float vx, float vy, float vz){
    _posX = posX;
    _posY = posY;
    _posZ = posZ;
    _vX = vx;
    _vY = vy;
    _vZ = vz;
}

void Particle::move(float dx, float dy, float dz){
    _posX += dx;
    _posY += dy;
    _posZ += dz;
}

void Particle::draw(){

    if(_posZ > 0){
        
        glPushMatrix();
        
        glTranslatef(_posX, _posY, _posZ);
        
        GLfloat mat_ambient[] = {1, 1, 0};
        GLfloat mat_diffuse[] = {1, 1, 0};
        GLfloat mat_specular[] = {1, 1, 0};
        GLfloat mat_shine = 100.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
        
        glutSolidSphere(0.1f, 5, 5);
        
        glPopMatrix();
        
    }
}

