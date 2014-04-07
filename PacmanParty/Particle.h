//
//  Particle.h
//  PacmanParty
//
//  Created by bia on 5/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanParty_Particle_h
#define PacmanParty_Particle_h

class Particle{

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
