//
//  Game.h
//  PacmanParty
//
//  Created by bia on 3/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PacmanParty_Game_h
#define PacmanParty_Game_h

#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include "Maze.h"
#include "Pacman.h"
#include "Ball.h"
#include "Ghost.h"
#include "Camera.h"
#include "Lighting.h"
#include "DayLight.h"
#include "Constraints.h"
#include "Explosion.h"
#include "Wizard.h"

void backToNormal(int value);
void theComeBack(int value);


class Game {
	
public:
    
	Game();
	~Game();
    
    void update();
	
    void ballsInspector();
    
    int matrixPosition(int x, int y);
    
    void movePac(float dist);
    void moveGhost(Ghost* ghost, float dist);
    
    int chaseDirection(Ghost* g);
    int runAwayDirection(Ghost* g);
    void ghostsTrouble();
    
    int upCheck(Character* car,float dist);
    int downCheck(Character* car,float dist);
    int leftCheck(Character* car,float dist);
    int rightCheck(Character* car,float dist);
    
    int check(Character* car, float dist);
    void resetPressedKeys();
    
    bool colision(Ghost* g);
    void detonate();
    
    void getOut(Character* g);
    void ballsEater();
    void renderBitmapString();
    void winnerRenderBitmapString();
    void loserRenderBitmapString();
    std::string integerToString(int num);
    void draw();
        
public:
    
    Camera* _camera;
    Lighting * _light;
    Pacman* _pac; //evitar getPacman
    int _balls; 
    int _score;
    int _lives;
    Maze* _maze;
    Ghost* _ghostOne;
    Ghost* _ghostTwo;
    Ghost* _ghostThree;
    int _ghostsState;
    int _ghostsNextState;
    
	std::string matrix;
    bool _detonator;
    Explosion* _explosion;

private:
    float present_time;
    float last_time;
    
};







#endif
