//
//  Ghost.h
//  BatesPoucoBates
//
//  Created by bia on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BatesPoucoBates_Ghost_h
#define BatesPoucoBates_Ghost_h

#include "Character.h"
#include "Eye.h"
#include "Constraints.h"

class Ghost : public Character {

public:
    Ghost(int posx, int posy, int id);
    ~Ghost();
    
    bool isGhost();
    bool _trouble;
    
    int _ghostId;
    
    void setDirection(float posX, float posY);
    void setColor(float a, float b, float c);
    void setSpeed(float speed);
    void setTrouble(bool trouble);
    void draw();
    void move(float dist);
    void backAgain();
    
    bool _hiddenTime;
    
private: 

};

#endif
