#ifndef __CONSTRAINTS_H__
#define __CONSTRAINTS_H__

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


#define CAM_MODE_1 0
#define CAM_MODE_2 1
#define CAM_MODE_3 2
#define DEFAULT CAM_MODE_1


#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define UP_ANGLE 180
#define LEFT_ANGLE -90
#define DOWN_ANGLE 0
#define RIGHT_ANGLE 90

#define WALL 'w'
#define SMALL_BALL 'b'
#define BIG_BALL 'B'
#define HALL '.'
#define GHOST 'g'
#define SCARED_GHOST 's'
#define PACMAN 'p'

#endif
