#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Explosion.h"

Explosion::Explosion(float pacX, float pacY, float pacZ){

    int i;
    _areThereAnyParticles = true;
    for(i = 0; i < PARTICLES; i++){
        _particles[i] = new Particle();
    }
    resetParticles(pacX, pacY, pacZ);
}

Explosion::~Explosion(){}

void Explosion::checkParticles(){
    int i;
    for(i=0; i<PARTICLES; i++){
        if(_particles[i]->_posZ > 0){
            _areThereAnyParticles = true; // ainda ha particulas a ser desenhadas
            return;
        }
    }
    _areThereAnyParticles = false;
}

void Explosion::resetParticles(float pacX, float pacY, float pacZ){
	int i;
    for(i = 0; i < PARTICLES; i++){
        if(i % 4 == 0){
            int vx = rand()%EXPLOSION_VEL;
            int vy = rand()%(int)sqrt(EXPLOSION_VEL*EXPLOSION_VEL-vx*vx); //explodem circularmente
            int vz = rand()%EXPLOSION_VEL;
            _particles[i]->reset(pacX, pacY, pacZ, vx, vy, vz);
        }
        else if(i % 4 == 1){
            int vx = -1 * rand()%EXPLOSION_VEL;
            int vy = rand()%(int)sqrt(EXPLOSION_VEL*EXPLOSION_VEL-vx*vx); //explodem circularmente
            int vz = rand()%EXPLOSION_VEL;
            _particles[i]->reset(pacX, pacY, pacZ, vx, vy, vz);
        }
        else if(i % 4 == 2){
            int vx = -1 * rand()%EXPLOSION_VEL;
            int vy = -1 * rand()%(int)sqrt(EXPLOSION_VEL*EXPLOSION_VEL-vx*vx); //explodem circularmente
            int vz = rand()%EXPLOSION_VEL;
            _particles[i]->reset(pacX, pacY, pacZ, vx, vy, vz);
        }
        else if(i % 4 == 3){
            int vx = rand()%EXPLOSION_VEL;
            int vy = -1 * rand()%(int)sqrt(EXPLOSION_VEL*EXPLOSION_VEL-vx*vx); //explodem circularmente
            int vz = rand()%EXPLOSION_VEL;
            _particles[i]->reset(pacX, pacY, pacZ, vx, vy, vz);
        }
    }
}

void Explosion::moveParticles(float dt){
    int i;
    float dx, dy, dz;
    for(i = 0; i < PARTICLES; i++){
        dx = (_particles[i]->_vX) * dt; 
        dy = (_particles[i]->_vY) * dt;
        _particles[i]->_vZ = _particles[i]->_vZ - dt * ACCELERATION;
        dz = (_particles[i]->_vZ)*dt-0.5f*dt*dt*ACCELERATION;
        _particles[i]->move(dx, dy, dz);
    }
}

void Explosion::draw(){
    
    glPushMatrix();
    
    int i;
    for(i = 0; i < PARTICLES; i++){
        _particles[i]->draw();
    }
    
    checkParticles();
    
    glPopMatrix();
    
}
