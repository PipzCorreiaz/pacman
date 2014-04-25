#ifndef __PACMAN_H__
#define __PACMAN_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Constraints.h"
#include "Character.h"
#include "Eyebrow.h"
#include "Explosion.h"
#include "MinerHat.h"
#include "Bullet.h"

class Pacman : public Character {
    
public:
    Pacman();
    Pacman(float, float);
    
    bool getExploding();
    bool getSick();
    int getBalls();
    void setExploding(bool value);
    void setSick(bool value);
    void setName(char);
    char getName();
    
    void draw();
    void move(float);
    void update(float dt);
    
    void backAgain();
    void eat(float x, float y, char symbol);
    void detonate();

    
private:
    void init();
    void cleanUpBullets();
    void shoot();

    bool _exploding;
    bool _sick;
	Eyebrow* _eyebrow;
    Explosion* _explosion;
    int _balls;
    char _name;
    int _ammunitions;
    std::vector<Bullet*> _bullets; 
};


#endif
