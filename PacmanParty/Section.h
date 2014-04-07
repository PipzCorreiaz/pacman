//
//  Section.h
//  PacmanLove
//
//  Created by bia on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanLove_Section_h
#define PacmanLove_Section_h

#include "Wall.h"
#include "Ball.h"

class Section{
    
public:
	Section(int quadX, int quadY);
	~Section();
	
	void draw();
    
private:
	int _quadrantX;
	int _quadrantY;
    
};


#endif
