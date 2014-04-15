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

    bool _explodingTime;
    
private:
	Eyebrow* _eyebrow;
	MinerHat* _cap;
};


#endif
