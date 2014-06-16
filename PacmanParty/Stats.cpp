#include "Stats.h"

#include <iostream>

Stats::~Stats() {

}

void Stats::setBalls(int value) {
    _balls = value;
}

void Stats::incGhosts() {
    _ghosts = _ghosts + 1;
}

void Stats::incZombies() {
    _zombies = _zombies + 1;
}

void Stats::dump() {
    std::cout << "================ STATS ================" << std::endl;
    std::cout << "BALLS: " << _balls << std::endl;
    std::cout << "GHOSTS EATEN/KILLED: " << _ghosts << std::endl;
    std::cout << "ZOMBIES: " << _zombies << std::endl;
    std::cout << "=======================================" << std::endl;
}