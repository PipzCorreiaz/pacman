//
//  Eye.h
//  PacmanLove
//
//  Created by bia on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanLove_Eye_h
#define PacmanLove_Eye_h

class Eye {
    
public:
    Eye();
    ~Eye();
    
    void draw();
    void intoPlace(float posX, float posY, float posZ);
   
    
private:
    float _posX;
    float _posY;
    float _posZ;
    
};


#endif
