#ifndef __PACMAN_H__
#define __PACMAN_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <map>
#include "Character.h"
#include "Eyebrow.h"
#include "Bullet.h"

class Pacman : public Character {
    
public:
    Pacman(); //SO DEVE SER USADO PARA O HUD
    Pacman(float x, float y, float color[3], float scarfColor[3]);
    
    bool getSick();
    int getBalls();
    void setSick(bool value);
    char getName();
    int getAmmunitions();
    float* getScarfColor();
    int getGhostCatched();
    
    void setName(char);
    void setScarfColor(float color[3]);
    void setGhostCatched();
    
    void draw();
    void move(float);
    void percept(float dt);
    void options();
    int filter();
    void plan(float dt);
    void reactive(float dt);
    void deliberative(float dt);
    void update(float dt);
    
    void backAgain();
    void eat(float x, float y, char symbol);
    void detonate();
    void treat();
    
private:
    void init();
    void cleanUpBullets();
    void shoot();

    void eatSmallBall(float dt);

    float _scarfColor[3];
    bool _sick;
	Eyebrow* _eyebrow;
    int _balls;
    char _name;
    int _ammunitions;
    int _ghostCatched;
    std::vector<Bullet*> _bullets;

    std::map<char, bool> _beliefs;
    std::map<int, bool> _desires;
    int _intention;
    bool _hasPlan;
};


#endif
