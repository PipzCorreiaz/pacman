#ifndef PacmanLove_Pacman_h
#define PacmanLove_Pacman_h

#include "Character.h"
#include "Eyebrow.h"
#include "MinerHat.h"

class Pacman : public Character {
    
public:
    Pacman();
   
    void update(float dt);
    void draw();
    void backAgain();
    void eat(float x, float y, char symbol);
    void move(float);

    bool _explodingTime;
    
private:
	Eyebrow* _eyebrow;
	MinerHat* _cap;
};


#endif
