#ifndef __GAME_H__
#define __GAME_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Maze.h"
#include "Ghost.h"
#include "Camera.h"
#include "DayLight.h"
#include "Wizard.h"
#include "Ball.h"
#include "Ammunition.h"

void backToNormal(int value);
void theComeBack(int value);


class Game {
	
public:
    
	Game();
    
    void update();
	
    void mapItemsDrawer();
    void ghostsTrouble();
    
    void drawHUD();
    void winnerRenderBitmapString();
    void loserRenderBitmapString();
    std::string integerToString(int num);
    void setScore();
    void draw();
        
public:
    
    Camera* _camera;
    Lighting * _light;
    Pacman* _pac;
    Pacman* _poc;
    int _balls; 
    int _score;
    Maze* _maze;
    Ghost* _ghostOne;
    Ghost* _ghostTwo;
    Ghost* _ghostThree;
    Ghost* _ghostHUD;
    Pacman* _pacmanHUD;
    std::vector<Ghost*> _ghosts;
    std::vector<Pacman*> _pacmen;
    int _ghostsState;
    int _ghostsNextState;
    
    bool _detonator;

private:
    float present_time;
    float last_time;
    bool _done;
    
};



#endif
