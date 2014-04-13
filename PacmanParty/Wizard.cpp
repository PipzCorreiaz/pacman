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
    /*int position = (floor(_mapHeight / 2) - y) * _mapWidth; //linhas completas
    position += (ceil(_mapWidth / 2) + x);*/
    int position = (28 - y) * _mapWidth; //linhas completas
    y <= 0 ? position-- : position;
    position += (27 + x);
    return x >= 0 ? position : position--;
}

std::vector<float> Wizard::indexToPosition(int index) {
	std::vector<float> coords(2);
	
	/*coords[1] = floor(_mapHeight / 2) - floor(index / _mapWidth);
	coords[0] = -floor(_mapWidth / 2) + (index % _mapWidth);*/
	
	coords[1] = 28 - floor(index / _mapWidth);
	coords[0] = -28 + (index % _mapWidth);
	
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
	
	std::cout << "index: " << index << std::endl;
	newIndex = leftPosition(index);
	std::cout << "LEFT: " << _map[newIndex];
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(LEFT); 
	}
	newIndex = rightPosition(index);
	std::cout << " RIGHT: " << _map[newIndex];
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(RIGHT); 
	}
	
	newIndex = upPosition(index);
	std::cout << " UP: " << _map[newIndex];
	if(_map[newIndex] != WALL && _map[newIndex] != ' ') {
		neighbours.push_back(UP); 
	}
	
	newIndex = downPosition(index); 
	std::cout << " DOWN: " << _map[newIndex] << std::endl;
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
    std::cout << "availablePosition" << std::endl;
	int index = positionToIndex(x, y);
	std::vector<int> positions = availablePositions(index);
	int lol = positions[rand() % positions.size()];
	std::cout << "tam: " << positions.size() << " random " << lol << std::endl;
	return lol;
}

int Wizard::availablePosition(int index) {
    std::cout << "availablePosition" << std::endl;
	std::vector<int> positions = availablePositions(index);
	int lol = positions[rand() % positions.size()];
	std::cout << "tam: " << positions.size() << " random " << lol << std::endl;
	return lol;
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

 
