//
//  Brick.h
//  PacmanParty
//
//  Created by bia on 5/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanParty_Brick_h
#define PacmanParty_Brick_h

class Brick {
    
public:
    Brick();
    ~Brick();
    
    void resize(float width, float height);
    void intoPlace(float posx, float posy, float posz);
	void draw();
    
    
    
private:
    
    float _width;
    float _height;
    float _posX;
    float _posY;
    float _posZ;
    
};




#endif
