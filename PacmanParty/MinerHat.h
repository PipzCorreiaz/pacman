#ifndef __MINERHAT_H__
#define __MINERHAT_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class MinerHat {
    
public:
    MinerHat();
    ~MinerHat();
    
    void draw();
    void intoPlace(float posX, float posY, float posZ);
	void drawFace(float angle);
   
    
private:
    float _posX;
    float _posY;
    float _posZ;
    
};


#endif
