#include "Wizard.h"

Wizard::Wizard() {
    
}

Wizard::~Wizard() {
    
}

std::string Wizard::loadMap(std::string fileName) {
    std::ifstream infile;
    std::string line;
    infile.open(fileName.c_str(), std::ifstream::in);
    _map = "";
    
    if (infile.is_open()) {
        while (getline(infile, line)) {
            _map += line.c_str();
        }

    } else {
        throw "Could not load the map file.";
    }
    
    return _map;
}