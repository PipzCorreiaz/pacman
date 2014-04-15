#ifndef PacmanParty_Camera_h
#define PacmanParty_Camera_h

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Pacman.h"

class Camera {
    
public:
    Camera(Pacman* pacman);
    ~Camera();

    int getMode();
    void setMode(int mode);
    void nextMode();
    void setProjection(double aspect_ratio);
    void setLookAt();
    
private:
    int _mode;
    Pacman* _pacman;

};

#endif
