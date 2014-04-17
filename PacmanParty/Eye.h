#ifndef __EYE_H__
#define __EYE_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Eye {
    
public:
    Eye();
    ~Eye();
    
    void draw();
    void intoPlace(float posX, float posY, float posZ);
   
    
private:
    float _posX;
    float _posY;
    float _posZ;
    
};


#endif
