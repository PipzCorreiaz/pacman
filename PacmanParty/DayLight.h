#ifndef __DAYLIGHT_H__
#define __DAYLIGHT_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Lighting.h"
#include "Character.h"

class DayLight : public Lighting {
    
public:
    
    DayLight();
    ~DayLight();
    void lightUs(Character *pac);


private:

    
};

#endif
