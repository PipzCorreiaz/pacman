//
//  Ball.h
//  PacmanLove
//
//  Created by bia on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanLove_Ball_h
#define PacmanLove_Ball_h

class Ball{
    
public:
    Ball();
    ~Ball();
    
    void draw();
    void intoPlace(float posX, float posY);
	void growth(float scale);
    
private:
    float _posX;
    float _posY;
    float _posZ;
    float _scale;
    
};

#endif
