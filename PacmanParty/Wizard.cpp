#include "Wizard.h"


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

std::string Wizard::getMap() {
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

int Wizard::positionAhead(float x, float y, int direction) {
	int index = 0;
	switch (direction) {    
		case UP:
			index = upPosition(positionToIndex(x, y));
			break;
		case LEFT:
			index = leftPosition(positionToIndex(x, y));
			break;
		case DOWN:
			index = downPosition(positionToIndex(x, y));
			break;
		case RIGHT:
			index = rightPosition(positionToIndex(x, y));
			break;
		default:
			break;
	}
	
	return index;
}

void Wizard::changeMap(float x, float y, char symbol) {
    int index = positionToIndex(x, y);
    _map[index] = symbol;
}

bool Wizard::isWall(float x, float y, int direction) {
	int indexAhead = positionAhead(x, y, direction);
	return _map[indexAhead] == WALL;
}

bool Wizard::isBall(float x, float y) {
    int index = positionToIndex(x, y);
    return (_map[index] == SMALL_BALL || _map[index] == BIG_BALL);
}

 
