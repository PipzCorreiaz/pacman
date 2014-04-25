#ifndef __PACMAN_H__
#define __PACMAN_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h"
#include "Eyebrow.h"
#include "Explosion.h"
#include "MinerHat.h"
#include "Bullet.h"

class Pacman : public Character {
    
public:
    Pacman();
    
    bool getExploding();
    int getBalls();
    void setExploding(bool value);
    
    void draw();
    void move(float);
    void update(float dt);
    
    void backAgain();
    void eat(float x, float y, char symbol);
    void detonate();

    
private:
    void cleanUpBullets();

    bool _exploding;
	Eyebrow* _eyebrow;
	MinerHat* _cap;
    Explosion* _explosion;
    int _balls;
    std::vector<Bullet*> _bullets; 
};


#endif
