#ifndef __CONSTRAINTS_H__
#define __CONSTRAINTS_H__

#define WALL_HOWBIG 1 // preferencialmente inteiro

#define GHOST_STATE_NORMAL 1 // Deprecated
#define GHOST_STATE_ESCAPE 2 // Deprecated

#define GHOST_NORMAL_SPEED 10
#define GHOST_ESCAPE_SPEED 2*GHOST_NORMAL_SPEED/3 // 2/3

#define GHOST_ESCAPE_TIME 10 //in seconds

#define PARTICLES 240 //numero de particulas na explosao
#define EXPLOSION_VEL 20 //velocidade maxima das particulas na explosao
#define ACCELERATION 9.8

#define PAC_EYE_X 0.375
#define PAC_EYE_Y -0.7
#define PAC_RADIUS 1.25
#define GHOST_RADIUS 1.5

#define CAM_MODE_1 0
#define CAM_MODE_2 1
#define CAM_MODE_3 2
#define DEFAULT CAM_MODE_1

#define GUN_POWER 25
#define BULLETS_PER_AMMUNITION 3

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
#define POCMAN 'q'
#define AMMUNITION 'a'
#define PACMAN_SICK 'i'
#define CROSSING 'c'
#define TRAIL 't'

#define TRAIL_THRESHOLD 10

#define KILL_GHOST 100
#define RUNAWAY 101
#define EAT_BIG_BALL 102
#define HEAL_PACMAN 103
#define BE_HEALED 104
#define TRANSFER_AMMUNITION 105
#define EAT_SMALL_BALL 106


#endif
