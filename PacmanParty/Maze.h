//
//  Maze.h
//  PacmanLove
//
//  Created by bia on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanLove_Maze_h
#define PacmanLove_Maze_h

#include <vector>
#include <string>
#include "Section.h"
#include "Wall.h"

class Maze {
	
public:
    
	Maze();
	~Maze();
    void setTextureOn(bool state);

	void draw();


private:
    Wall* _floor;
    bool _textureOn;
};



#endif
