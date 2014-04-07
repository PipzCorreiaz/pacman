//
//  Lighting.h
//  PacmanParty
//
//  Created by Miguel Roxo on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanParty_Lighting_h
#define PacmanParty_Lighting_h

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h"

class Lighting {
    
public:
    
    Lighting();
    ~Lighting();
    void virtual lightUs(Character *pac) = 0;


private:

    
};

#endif
