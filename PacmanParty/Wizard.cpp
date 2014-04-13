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
            _mapWidth = (int)line.length();        
        }

    } else {
        throw new std::string("Could not load the map file.");
    }
    
    return _map;
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
		neighbours.push_back(LEFT); 
	}
	newIndex = rightPosition(index);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(RIGHT); 
	}
	
	newIndex = upPosition(index);
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(UP); 
	}
	
	newIndex = downPosition(index); 
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
	int lol = positions[rand() % positions.size()];
	return lol;
}

int Wizard::availablePosition(int index) {
	std::vector<int> positions = availablePositions(index);
	int lol = positions[rand() % positions.size()];
	return lol;
}

std::vector<float> Wizard::nextPosition(float x, float y, float dist, int direction) {
    
    std::vector<float> coords(2);
    
    coords[0] = x;
    coords[1] = y;
    
    switch (direction) {
		case UP:
			coords[1] = y + dist;
			break;
		case LEFT:
			coords[0] = x - dist;
			break;
		case DOWN:
			coords[1] = y - dist;
			break;
		case RIGHT:
			coords[0] = x + dist;
			break;
		default:
			break;
	}
    
    return coords;
}

int Wizard::positionAhead(float x, float y, float dist, int direction) {
	int index = 0;
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

 
