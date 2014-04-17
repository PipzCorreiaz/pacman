#ifndef __PACMAN_H__
#define __PACMAN_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h"
#include "Eyebrow.h"
#include "MinerHat.h"

class Pacman : public Character {
    
public:
    Pacman();
    
    bool getExploding();
    void setExploding(bool value);
    
    void draw();
    void move(float);
    void update(float dt);
    
    void backAgain();
    void eat(float x, float y, char symbol);

    
private:
    bool _exploding;
	Eyebrow* _eyebrow;
	MinerHat* _cap;
};


#endif
