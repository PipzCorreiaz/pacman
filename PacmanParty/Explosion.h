//
//  Explosion.h
//  PacmanParty
//
//  Created by bia on 5/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

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
