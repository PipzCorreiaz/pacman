#ifndef PacmanParty_Explosion_h
#define PacmanParty_Explosion_h

#include "Particle.h"
#include "Constraints.h"
#include <cmath>


class Explosion{

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
