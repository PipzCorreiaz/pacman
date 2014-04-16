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

void backToNormal(int value);
void theComeBack(int value);


class Game {
	
public:
    
	Game();
    
    void update();
	
    void ballsInspector();
        
    void ghostsTrouble();
    
//    bool colision(Ghost* g);
    void detonate();
    
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
    std::vector<Ghost*> _ghosts;
    int _ghostsState;
    int _ghostsNextState;
    
    bool _detonator;
    Explosion* _explosion;

private:
    float present_time;
    float last_time;
    
};



#endif
