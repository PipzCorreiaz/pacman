#ifndef PacmanParty_Wizard_h
#define PacmanParty_Wizard_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "Constraints.h"
 
class Wizard {

public:
    
    ~Wizard();
    
    static Wizard& getInstance() {
        static Wizard instance;
        return instance;
    }
 
    void loadMap(std::string fileName);
    std::string getMap();
    int positionToIndex(float x, float y);
    std::vector<float> indexToPosition(int index);
    bool canTurn(float x, float y);
    int availablePosition(float x, float y);
    int availablePosition(int index);
    void changeMap(float, float, char symbol);
    bool isWall(float, float, int);
    bool isBall(float x, float y);
   
    
private:
    Wizard() {};
    Wizard(Wizard const&);
    void operator= (Wizard const&);

    int positionAhead(float x, float y, int direction);
    std::vector<int> availablePositions(int index);
    int rightPosition(int index);
    int leftPosition(int index);
    int upPosition(int index);
    int downPosition(int index);


    std::string _map;
    int _mapWidth;
    int _mapHeight;
};

#endif
