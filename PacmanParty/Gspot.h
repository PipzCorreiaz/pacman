#ifndef PacmanParty_Gspot_h
#define PacmanParty_Gspot_h

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Lighting.h"
#include "Character.h"

class Gspot : public Lighting {
    
public:
    
    Gspot();
    ~Gspot();
    void lightUs(Character *pac);
    float lastDir[];


private:

    
};

#endif
