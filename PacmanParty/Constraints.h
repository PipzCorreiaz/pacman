//
//  CONSTRAINTS.h
//  PacmanParty
//
//  Created by Miguel Roxo on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanParty_CONSTRAINTS_h
#define PacmanParty_CONSTRAINTS_h

/* Ghost Constraints */

#define WALL_HOWBIG 1 // preferencialmente inteiro

#define GHOST_STATE_NORMAL 1 // Deprecated
#define GHOST_STATE_ESCAPE 2 // Deprecated

#define GHOST_NORMAL_SPEED 10
#define GHOST_ESCAPE_SPEED 2*GHOST_NORMAL_SPEED/3 // 2/3

#define GHOST_ESCAPE_TIME 10 //in seconds

#define PARTICLES 240 //numero de particulas na explosao
#define EXPLOSION_VEL 20 //velocidade maxima das particulas na explosao
#define ACCELERATION 9.8;

#define PAC_RADIUS 1.25
#define GHOST_RADIUS 1.5

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#endif
