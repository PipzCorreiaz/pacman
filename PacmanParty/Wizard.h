#ifndef PacmanParty_Wizard_h
#define PacmanParty_Wizard_h

#include <iostream>
#include <fstream>
#include <string>


class Wizard {

public:
    
    ~Wizard();
    
    static Wizard& getInstance() {
        static Wizard instance;
        return instance;
    }
    
    std::string loadMap(std::string fileName);
    
private:
    Wizard();
    std::string _map;
};

#endif
