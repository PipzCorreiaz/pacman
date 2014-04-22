#include "Wizard.h"

void backToNormal(int value);
void theComeBack(int ghostIndex);

Wizard::~Wizard() {
    
}

void Wizard::loadMap(std::string fileName) {
    std::ifstream infile;
    std::string line;
    infile.open(fileName.c_str(), std::ifstream::in);
    _map = "";
    
    if (infile.is_open()) {
        while (getline(infile, line)) {
            _map += line.c_str();
            _mapHeight++;
            _mapWidth = (int)line.length();        
        }

    } else {
        throw new std::string("Could not load the map file.");
    }
}

void Wizard::setGhosts(std::vector<Ghost*> ghosts) {
    _ghosts = ghosts;
}

std::vector<Ghost*> Wizard::getGhosts() {
    return _ghosts;
}

std::string Wizard::getMap() {
    return _map;
}

float Wizard::getMapWidth() {
    return _mapWidth;
}

float Wizard::getMapHeight() {
    return _mapHeight;
}

int Wizard::positionToIndex(float x, float y) {
    int position = (((_mapHeight - 1) / 2) - round(y)) * _mapWidth;
    position += ((_mapWidth - 1) / 2) + round(x);
    return position;
}

std::vector<float> Wizard::indexToPosition(int index) {
	std::vector<float> coords(2);
	
	coords[0] = (index % _mapWidth) - ((_mapWidth - 1) / 2);
	coords[1] = ((_mapWidth * ((_mapHeight - 1) / 2)) + ((_mapWidth - 1) / 2) + coords[0] - index) / _mapWidth;
	
	return coords;
}

int Wizard::rightPosition(int index, int nPositions) {
	return index + nPositions;
}

int Wizard::leftPosition(int index, int nPositions) {
	return index - nPositions;
}

int Wizard::upPosition(int index, int nPositions) {
	return index - nPositions * _mapWidth;
}
int Wizard::downPosition(int index, int nPositions) {
	return index + nPositions * _mapWidth;

}

std::vector<int> Wizard::availablePositions(int index) {
	std::vector<int> neighbours;
	int newIndex = 0;
	
	newIndex = leftPosition(index, 2);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(LEFT); 
	}
	newIndex = rightPosition(index, 2);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(RIGHT); 
	}
	
	newIndex = upPosition(index, 2);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(UP); 
	}
	
	newIndex = downPosition(index, 2);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(DOWN); 
	}
	
	return neighbours;
}

bool Wizard::canTurn(float x, float y) {
	int index = positionToIndex(x, y);
	return availablePositions(index).size() > 2;
}

int Wizard::availablePosition(float x, float y) {
	int index = positionToIndex(x, y);
	std::vector<int> positions = availablePositions(index);
    int size = positions.size(); 	
    if(!size) {
        std::cout << "nao encontrei posicoes" << std::endl;
        return -1;
    }
    return positions[rand() % size];
}   

int Wizard::availablePosition(int index) {
	std::vector<int> positions = availablePositions(index);
    int size = positions.size();    
    if(!size) {
        std::cout << "nao encontrei posicoes" << std::endl;
        return -1;
    }
    return positions[rand() % size];
}

int Wizard::positionAhead(float x, float y, int direction, int nPositions) {
	int index = 0;
	switch (direction) {    
		case UP:
			index = upPosition(positionToIndex(x, y), nPositions);
			break;
		case LEFT:
			index = leftPosition(positionToIndex(x, y), nPositions);
			break;
		case DOWN:
			index = downPosition(positionToIndex(x, y), nPositions);
			break;
		case RIGHT:
			index = rightPosition(positionToIndex(x, y), nPositions);
			break;
		default:
			break;
	}
	
	return index;
}

char Wizard::getMapSymbol(float x, float y) {
    int index = positionToIndex(x, y);
    return _map[index];
}

void Wizard::changeMap(float x, float y, char symbol) {
    int index = positionToIndex(x, y);
    _map[index] = symbol;
}

bool Wizard::isWall(float x, float y, int direction) {
	int indexAhead = positionAhead(x, y, direction, 2);
	return _map[indexAhead] == WALL;
}

bool Wizard::isBall(float x, float y) {
    int index = positionToIndex(x, y);
    return (_map[index] == SMALL_BALL || _map[index] == BIG_BALL);
}

bool Wizard::isGhost(float x, float y, int direction) {
    int ghostIndex = 0;
    int indexAhead = positionAhead(x, y, direction, 1);
    int indexFarAway = positionAhead(x, y, direction, 2);
    for (int i=0; i < _ghosts.size(); i++) {
        ghostIndex = positionToIndex(_ghosts[i]->getX(), _ghosts[i]->getY());
        if (ghostIndex == positionToIndex(x, y) || ghostIndex == indexAhead ||ghostIndex == indexFarAway) {
            return true;
        }
    }
    return false;
}

bool Wizard::isGhostScared(float x, float y, int direction) {
    int ghostIndex = 0;
    int indexAhead = positionAhead(x, y, direction, 1);
    int indexFarAway = positionAhead(x, y, direction, 2);
    for (int i=0; i < _ghosts.size(); i++) {
        ghostIndex = positionToIndex(_ghosts[i]->getX(), _ghosts[i]->getY());
        if (_ghosts[i]->getTrouble() &&
            (ghostIndex == positionToIndex(x, y)
            || ghostIndex == indexAhead
            || ghostIndex == indexFarAway)) {
            return true;
        }
    }
    return false;
}

void backToNormal(int value) {
    std::vector<Ghost*> ghosts = Wizard::getInstance().getGhosts();
    for (int i = 0; i < ghosts.size(); i++) {
        ghosts[i]->setTrouble(false);
    }
}

void theComeBack(int ghostIndex) {
    std::vector<Ghost*> ghosts = Wizard::getInstance().getGhosts();
    Ghost* ghost = ghosts[ghostIndex];
    ghost->setHidden(false);
}

void Wizard::ghostsTrouble() {
    for (int i = 0; i < _ghosts.size(); i++) {
        _ghosts[i]->setTrouble(true);
    }
    glutTimerFunc(10000, backToNormal, 1);
}

void Wizard::ghostHidden(float x, float y) {
    int ghostIndex = 0;
    for (int i=0; i < _ghosts.size(); i++) {
        ghostIndex = positionToIndex(_ghosts[i]->getX(), _ghosts[i]->getY());
        if (ghostIndex == positionToIndex(x, y)) {
            _ghosts[i]->setHidden(true);
            _ghosts[i]->setTrouble(false);
            _ghosts[i]->backAgain();
            glutTimerFunc(5000, theComeBack, i);
            return;
        }
    }
    
}
 
