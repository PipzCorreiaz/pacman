#ifndef __WIZARD_H__
#define __WIZARD_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <fstream>
#include <queue>
#include <cmath>
#include "Ghost.h"
#include "Pacman.h"
#include "Constraints.h"

void backToNormal(int value);
void theComeBack(int ghostIndex);


 
class Wizard {

public:
    
    ~Wizard();
    
    static Wizard& getInstance() {
        static Wizard instance;
        return instance;
    }
 
    void loadMap(std::string fileName);
    void setGhosts(std::vector<Ghost*> ghosts);
    void setPacmen(std::vector<Pacman*> pacmen);
    std::vector<Ghost*> getGhosts();
    std::vector<Pacman*> getPacmen();
    std::string getMap();
    int positionToIndex(float x, float y);
    std::vector<float> indexToPosition(int index);
    bool canTurn(float x, float y);
    bool canTurn(float x, float y, int direction);
    int availablePosition(float x, float y);
    int availablePosition(float x, float y, int dir);
    int availablePositionWithBall(float x, float y);
    int availablePositionWithGhost(float x, float y);
    bool isAvailableDirection(float x, float y, int direction);
    int availablePosition(int index);
    char getMapSymbol(float x, float y);
    void changeMap(float, float, char symbol);
    float getMapWidth();
    float getMapHeight();
    int bigBallsCatched();
    void setBigBallsCatched(int);
    
    void ghostsTrouble();
    void ghostHidden(float x, float y);
    int shotGhost(float x, float y);
    void killPacman(char pacman);

    
    bool isWall(float, float, int);
    bool isBall(float x, float y);
    bool isGhost(float x, float y, int direction);
    bool isGhostScared(float x, float y, int direction);
    bool isPacman(char, float, float, int);
    bool isPacmanOnSights(char name, float x, float y, int direction);
    bool isPacmanOnAnyDirection(char name, float x, float y);
    bool isAmmunition(float x, float y, int direction);
    bool isBigBall(float x, float y, int direction);
    bool isPacmanSick(char name, float x, float y, int direction);
    bool isGhostTrail(float x, float y);
    bool isGhostOnSight(float x, float y, int direction);
    float distance(float x, float y, float x2, float y2);
    int friendDirection(char name);
    int directionToTurn(char name, float x, float y);
    bool pacmanVision(char name, float x, float y);
    void treatIfSick(char, float, float, int);
    void shareAmmunitions();
    
    bool isSameIndex(float, float, float, float);
    bool isSameColumn(float x1, float x2);
    bool isSameLine(float y1, float y2);
    
    void addAmmunitionToQueue(float, float);
    void removeAmmunitionFromQueue();
    
   
    
private:
    Wizard() {};
    Wizard(Wizard const&);
    void operator= (Wizard const&);
    
    void printMap();

    int positionAhead(float x, float y, int direction, int nPositions);
    std::vector<int> availablePositions(int index);
    int rightPosition(int index, int nPositions);
    int leftPosition(int index, int nPositions);
    int upPosition(int index, int nPositions);
    int downPosition(int index, int nPositions);


    std::string _map;
    std::vector<Ghost*> _ghosts;
    std::vector<Pacman*> _pacmen;
    int _mapWidth;
    int _mapHeight;
    int _bigBallsCatched = 0;
    std::queue<std::vector<float> > _ammunitionsQueue;
};


#endif
