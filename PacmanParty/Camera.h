#ifndef __CAMERA_H__
#define __CAMERA_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Pacman.h"
#include "Constraints.h"

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
