#include "Wizard.h"


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
            _mapHeight++;
            _mapWidth = line.length();        
        }

    } else {
        throw new std::string("Could not load the map file.");
    }
    
    return _map;
}

int Wizard::positionToIndex(int x, int y) {
    int position = (floor(_mapHeight / 2) - y) * _mapWidth; //linhas completas
    position += (ceil(_mapWidth / 2) + x);
    return position;
}

std::vector<int> Wizard::indexToPosition(int index) {
	std::vector<int> coords(2);
	
	coords[1] = floor(_mapHeight / 2) - floor(index / _mapWidth);
	coords[0] = -floor(_mapWidth / 2) + (index % _mapWidth);
	
	return coords;
}

int Wizard::rightPosition(int index) {
	return index + 2;
}

int Wizard::leftPosition(int index) {
	return index - 2;
}

int Wizard::upPosition(int index) {
	return index - 2 * _mapWidth;
}
int Wizard::downPosition(int index) {
	return index + 2 * _mapWidth;

}

std::vector<int> Wizard::availablePositions(int index) {
	std::vector<int> neighbours;
	int newIndex = 0;
	
	newIndex = leftPosition(index);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(newIndex); 
	}
	newIndex = rightPosition(index); 
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(newIndex); 
	}
	
	newIndex = upPosition(index); 
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(newIndex); 
	}
	
	newIndex = downPosition(index); 
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(newIndex); 
	}
	
	return neighbours;
}

bool Wizard::canTurn(int x, int y) {
	int index = positionToIndex(x, y);
	return availablePositions(index).size() > 2;
}

int Wizard::positionAhead(int x, int y, float dist, int direction) {
	int index = 0;
	int currentIndex = positionToIndex(x, y);
	
	switch (direction) {    
		case UP:
			index = upPosition(positionToIndex(x, y + dist));
			break;
		case LEFT:
			index = leftPosition(positionToIndex(x - dist, y));
			break;
		case DOWN:
			index = downPosition(positionToIndex(x, y - dist));
			break;
		case RIGHT:
			index = rightPosition(positionToIndex(x + dist, y));
			break;
		default:
			break;
	}
	
	return index;
}

bool Wizard::isWall(int index) {
	
	return _map[index] == WALL;
}

 
