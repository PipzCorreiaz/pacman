#ifndef BatesPoucoBates_Ghost_h
#define BatesPoucoBates_Ghost_h

#include <iostream>
#include <cmath>
#include "Constraints.h"
#include "Character.h"
#include "Eye.h"

class Ghost : public Character {

public:
    Ghost(int posx, int posy, int id);
    
    bool getTrouble();
    bool getHidden();
    
    void setSpeed(float speed);
    void setTrouble(bool trouble);
    void setHidden(bool value);
    void setColor(float a, float b, float c);
    
    void draw();
    void update(float dt);
    
    void backAgain();
    
    
private:
    int _ghostId;
    bool _trouble;
    bool _hidden;

};

#endif
