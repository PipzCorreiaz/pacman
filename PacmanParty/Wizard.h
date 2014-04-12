#ifndef PacmanParty_Wizard_h
#define PacmanParty_Wizard_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "Constraints.h"

class Wizard {

public:
    
    ~Wizard();
    
    static Wizard& getInstance() {
        static Wizard instance;
        return instance;
    }
    
    std::string loadMap(std::string fileName);
    int positionToIndex(int x, int y);
    std::vector<int> indexToPosition(int index);
    int rightPosition(int index);
    int leftPosition(int index);
    int upPosition(int index);
    int downPosition(int index);
    std::vector<int> availablePositions(int index);
    bool isWall(int index);
    bool canTurn(int x, int y);
    int positionAhead(int x, int y, float dist, int direction);
        
    
private:
    Wizard() {};
    Wizard(Wizard const&);
    void operator= (Wizard const&);
    std::string _map;
    int _mapWidth;
    int _mapHeight;
};

#endif
