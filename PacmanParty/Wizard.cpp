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

void Wizard::setGhosts(std::vector<Ghost*> ghosts) {
    _ghosts = ghosts;
}

void Wizard::setPacmen(std::vector<Pacman*> pacmen) {
    _pacmen = pacmen;
}

std::vector<Ghost*> Wizard::getGhosts() {
    return _ghosts;
}

std::vector<Pacman*> Wizard::getPacmen() {
    return _pacmen;
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

int Wizard::bigBallsCatched() {
    return _bigBallsCatched;
}

void Wizard::setBigBallsCatched(int value) {
    _bigBallsCatched = value;
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

bool Wizard::canTurn(float x, float y, int direction) {
    int index = positionToIndex(x, y);
    return availablePositions(index).size() > 2 || isWall(x, y, direction);
}

int Wizard::availablePosition(float x, float y) {
	int index = positionToIndex(x, y);
	std::vector<int> positions = availablePositions(index);
    int size = (int)positions.size();
    if(!size) {
        std::cout << "nao encontrei posicoes" << std::endl;
        return -1;
    }
    return positions[rand() % size];
}

int Wizard::availablePosition(float x, float y, int dir) {
    int index = positionToIndex(x, y);
    std::vector<int> positions = availablePositions(index);
    int size = (int)positions.size();
    if(!size) {
        std::cout << "nao encontrei posicoes" << std::endl;
        return -1;
    }
    int chosenDir = positions[rand() % size];
    int back = (chosenDir + 2) % 4;
    while (size != 1 && back == dir) {
        chosenDir = positions[rand() % size];
        back = (chosenDir + 2) % 4;
    }

    return chosenDir;
}

bool Wizard::isAvailableDirection(float x, float y, int direction) {
    int index = positionToIndex(x, y);
    std::vector<int> positions = availablePositions(index);
    int size = (int)positions.size();

    for (int i = 0; i < size; i++) {
        if (direction == positions[i]) {
            return true;
        }
    }

    return false;

}

int Wizard::availablePositionWithBall(float x, float y) {
    int index = positionToIndex(x, y);
    int newIndex = 0;
    
    newIndex = leftPosition(index, 2);
    if(_map[newIndex] == SMALL_BALL) {
        return LEFT; 
    }
    newIndex = rightPosition(index, 2);
    if(_map[newIndex] == SMALL_BALL) {
        return RIGHT; 
    }
    
    newIndex = upPosition(index, 2);
    if(_map[newIndex] == SMALL_BALL) {
        return UP; 
    }
    
    newIndex = downPosition(index, 2);
    if(_map[newIndex] == SMALL_BALL) {
        return DOWN; 
    }
    
    return availablePosition(x, y);
}

int Wizard::availablePositionWithScaredGhost(float x, float y) {
    int index = positionToIndex(x, y);
    int newIndex = 0;
    bool stopLeft, stopRight, stopUp, stopDown;
    stopLeft = stopRight = stopUp = stopDown = false;
    
    for (int i = 0; ; i++) {
        newIndex = leftPosition(index, 2);
        if(!stopLeft && _map[newIndex] == SCARED_GHOST) {
            return LEFT; 
        }
        if (_map[newIndex] == WALL || _map[newIndex] == ' ') stopLeft = true;

        newIndex = rightPosition(index, 2);
        if(!stopRight && _map[newIndex] == SCARED_GHOST) {
            return RIGHT; 
        }
        if (_map[newIndex] == WALL || _map[newIndex] == ' ') stopRight = true;

        newIndex = upPosition(index, 2);
        if(!stopUp && _map[newIndex] == SCARED_GHOST) {
            return UP; 
        }
        if (_map[newIndex] == WALL || _map[newIndex] == ' ') stopUp = true;

        newIndex = downPosition(index, 2);
        if(!stopDown && _map[newIndex] == SCARED_GHOST) {
            return DOWN; 
        }
        if (_map[newIndex] == WALL || _map[newIndex] == ' ') stopDown = true;

        if (stopLeft && stopDown && stopUp && stopRight) {
            break;
        }
    }
    
    return availablePosition(x, y);
}

int Wizard::availablePositionExceptCurrent(float x, float y, int dir) {
    int index = positionToIndex(x, y);
    std::vector<int> positions = availablePositions(index);
    int size = (int)positions.size();
    if(!size) {
        std::cout << "nao encontrei posicoes" << std::endl;
        return -1;
    }
    int chosenDir = positions[rand() % size];
    while (size != 1 && chosenDir == dir) {
        chosenDir = positions[rand() % size];
    }

    std::cout << "CURRENT DIR: " << dir 
        << " NEXT DIR: " << chosenDir << "SIZE: " << size
        << "POSITION: " << index 
        << " SYMBOL 1: " << _map[upPosition(index, 2)]
        << " SYMBOL 2: " << _map[leftPosition(index, 2)]
        << " SYMBOL 3: " << _map[rightPosition(index, 2)]
        << " SYMBOL 4: " << _map[downPosition(index, 2)]
        << std::endl;
    return chosenDir;
}

int Wizard::runToCrossing(float x, float y, int direction, std::string crossingMap) {
    bool continue1, continue2;
    continue1 = continue2 = true;
    int index, index1, index2, direction1, direction2;
    index = positionToIndex(x, y);
    index1 = index2 = direction1 = direction2 = 0;

    for (int i = 0; (continue1 || continue2) ; i++) {
        if(direction == UP || direction == DOWN) {
            if(continue1) {
                index1 = upPosition(index, i);
                direction1 = UP;    
            }
            if(continue2) {
                index2 = downPosition(index, i);
                direction2 = DOWN;
            }
        } else if (direction == RIGHT || direction == LEFT){
            if(continue1) {
                index1 = leftPosition(index, i);
                direction1 = RIGHT;
            }
            if(continue2) {
                index2 = rightPosition(index, i);
                direction2 = LEFT;
            }
        }

        if (continue1 && crossingMap[index1] == CROSSING) {
            return direction1;
        } else if (_map[index1] == WALL || _map[index1] == ' ' || _map[index1] == GHOST) {
            continue1 = false;
        }

        if (continue2 && crossingMap[index2] == CROSSING)  {
            return direction2;
        } else if (_map[index2] == WALL || _map[index2] == ' ' || _map[index2] == GHOST) {
            continue2 = false;
        }
    }
    return -1;
}

int Wizard::directionOnCrossing(float x, float y, int direction) {
    int direction1, direction2 = 0;
    direction1 = (direction+1) % 4;
    direction2 = (direction-1) % 4;
    if(isAvailableDirection(x,y, direction1)) {
        return direction1;
    } else {
        return direction2;
    }

    return -1;
}


int Wizard::availablePosition(int index) {
	std::vector<int> positions = availablePositions(index);
    int size = (int)positions.size();
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

void Wizard::printMap() {
    int limit = 0;
    for (int i = 0; i < _map.length(); i++) {
        std::cout << _map[i];
        limit++;
        if (limit == 55) {
            std::cout << std::endl;
            limit = 0;
        }
    }
    
    std::cout << std::endl;
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
    int maxPositions = 4;

    for (int i = 1; i <= maxPositions; i++) {
        if (_map[positionAhead(x, y, direction, i)] == GHOST) {
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

bool Wizard::isGhostScared(float x, float y) {
    for (int i = 0; i < _ghosts.size(); i++) {
        float pX = _ghosts[i]->getX();
        float pY = _ghosts[i]->getY();

        if (!_ghosts[i]->getTrouble() && inRange(x, y, pX, pY, 2)) {
            std::cout << "Found a ghost" << std::endl;
            return true;
        }
    }
    
    return false;
}

bool Wizard::inRange(float origX, float origY, float x, float y, float radius) {
    
    return (pow(x - origX, 2) + pow(y - origY, 2)) <= pow(radius, 2);
}

bool Wizard::isPacman(char name, float x, float y, int direction) {

    int maxPositions = 3;
    for (int i = 0; i <= maxPositions; i++) {
        int index = positionAhead(x, y, direction, i);
        if (_map[index] != name && (_map[index] == PACMAN || _map[index] == POCMAN)) {
            return true;
        }
    }
    return false;
}

bool Wizard::isPacman(char name, float x, float y) {
    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != name) {
            float pX = _pacmen[i]->getX();
            float pY = _pacmen[i]->getY();
            
            if (!_pacmen[i]->getSick() && inRange(x, y, pX, pY, 2)) {
                std::cout << "Found a pacman" << std::endl;
                return true;
            }
        }
    }
    
    return false;
}

bool Wizard::isPacmanOnSights(char name, float x, float y, int direction) {
    bool continue1 = true;
    bool continue2 = true;
    int index1 = 0;
    int index2 = 0;

    for (int i = 0; (continue1 || continue2) ; i++) {
        if(direction == UP || direction == DOWN) {
            if(continue1) {
                index1 = upPosition(positionToIndex(x, y), i);    
            }
            if(continue2) {
                index2 = downPosition(positionToIndex(x, y), i);
            }
        } else if (direction == RIGHT || direction == LEFT){
            if(continue1) {
                index1 = leftPosition(positionToIndex(x, y), i);
            }
            if(continue2) {
                index2 = rightPosition(positionToIndex(x, y), i);
            }
        }

        if (continue1 && (_map[index1] != name && (_map[index1] == PACMAN || _map[index1] == POCMAN))) {
            return true;
        } else if (_map[index1] == WALL || _map[index1] == ' ') {
            continue1 = false;
        }

        if (continue2 && (_map[index2] != name && (_map[index2] == PACMAN || _map[index2] == POCMAN)))  {
            return true;
        } else if (_map[index2] == WALL || _map[index2] == ' ') {
            continue2 = false;
        }
    }
    return false;
}

bool Wizard::isPacmanOnAnyDirection(char name, float x, float y) {
    bool continueUp = true;
    bool continueDown = true;
    bool continueLeft = true;
    bool continueRight = true;
    int index = positionToIndex(x,y);
    int indexUp = 0;
    int indexDown = 0;
    int indexLeft = 0;
    int indexRight = 0;

    for (int i = 0; (continueUp || continueDown || continueLeft || continueRight) ; i++) {

        if(continueUp) {
            indexUp = upPosition(index, i);    
        }
        if(continueDown) {
            indexDown = downPosition(index, i);
        }
        if(continueLeft) {
            indexLeft = leftPosition(index, i);
        }
        if(continueRight) {
            indexRight = rightPosition(index, i);
        }
        
        if (continueUp && (_map[indexUp] != name && (_map[indexUp] == PACMAN || _map[indexUp] == POCMAN))) {
            return true;
        } else if (_map[indexUp] == WALL || _map[indexUp] == ' ') {
            continueUp = false;
        }

        if (continueDown && (_map[indexDown] != name && (_map[indexDown] == PACMAN || _map[indexDown] == POCMAN)))  {
            return true;
        } else if (_map[indexDown] == WALL || _map[indexDown] == ' ') {
            continueDown = false;
        }
        if (continueLeft && (_map[indexLeft] != name && (_map[indexLeft] == PACMAN || _map[indexLeft] == POCMAN)))  {
            return true;
        } else if (_map[indexLeft] == WALL || _map[indexLeft] == ' ') {
            continueLeft = false;
        }
        if (continueRight && (_map[indexRight] != name && (_map[indexRight] == PACMAN || _map[indexRight] == POCMAN)))  {
            return true;
        } else if (_map[indexRight] == WALL || _map[indexRight] == ' ') {
            continueRight = false;
        }
    }
    return false;
}



bool Wizard::isAmmunition(float x, float y, int direction) {
    int maxPositions = 3;

    for (int i = 1; i <= maxPositions; i++) {
        if (_map[positionAhead(x, y, direction, i)] == AMMUNITION) {
            return true;
        }
    }
    return false;
}

bool Wizard::isBigBall(float x, float y, int direction) {
    int maxPositions = 4;

    for (int i = 1; i <= maxPositions; i++) {
        if (_map[positionAhead(x, y, direction, i)] == BIG_BALL) {
            return true;
        }
    }
    return false;
}

bool Wizard::isPacmanSick(char name, float x, float y, int direction) {
    int maxPositions = 3;
   
    for (int i = 0; i <= maxPositions; i++) {
        int index = positionAhead(x, y, direction, i);
        if (_map[index] != name && (_map[index] == PACMAN || _map[index] == POCMAN)) {
            for(int i = 0; i<_pacmen.size(); i++) {
                if (_pacmen[i]->getName() != name && _pacmen[i]->getSick()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Wizard::isGhostTrail(float x, float y) {

    for (int i=0; i < _ghosts.size(); i++) {
        if(distance(x, y, _ghosts[i]->getX(), _ghosts[i]->getY()) < TRAIL_THRESHOLD) {
            return true;
        } 
    }
    return false;
}

float Wizard::distance(float x, float y, float x2, float y2) {
    return sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
}

bool Wizard::pacmanVision(char name, float x, float y) {
     for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != name) {
            if(isSameLine(y, _pacmen[i]->getY()) || isSameColumn(x, _pacmen[i]->getX())) {
                return true;
            }  
        }
    }
    return false;
}

int Wizard::friendDirection(char name) {
    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != name) {
            return (_pacmen[i]->getDirection());
        }
    }
    return -1;
}

int Wizard::directionToTurn(char name, float x, float y) {
    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != name) {
            if (Wizard::getInstance().isSameLine(y, _pacmen[i]->getY())) {
                if(_pacmen[i]->getX() > x) { //esta a direita
                    return RIGHT;
                }
                if(_pacmen[i]->getX() < x) { //esta a esquerda
                    return LEFT;
                }
            }
            if (Wizard::getInstance().isSameColumn(x, _pacmen[i]->getX())) {
                if(_pacmen[i]->getY() > y) { //esta acima
                    return UP;
                }
                
                if(_pacmen[i]->getY() < y) { //esta abaixo
                    return DOWN;
                }
            }
        }
    }
    return -1;
}

int Wizard::smartDirection(char name, float x, float y) {

    int xDifference = 0;
    int yDifference = 0; 

    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != name) {
            xDifference = abs(_pacmen[i]->getX() - x);
            yDifference = abs(_pacmen[i]->getY() - y);

            if (xDifference > yDifference) {
                if(_pacmen[i]->getX() > x) { //esta a direita
                    return RIGHT;
                }
                if(_pacmen[i]->getX() < x) { //esta a esquerda
                    return LEFT;
                }
            } else {
                if(_pacmen[i]->getY() > y) { //esta acima
                    return UP;
                }
                
                if(_pacmen[i]->getY() < y) { //esta abaixo
                    return DOWN;
                }
            }
        }
    }
    return -1;
}

void Wizard::treatIfSick(char name, float x, float y, int direction) {
    int maxPositions = 3;
    char symbol = HALL;
    for (int i = 0; i <= maxPositions; i++) {
        int index = positionAhead(x, y, direction, i);
        symbol = _map[index];
        if (symbol != name && (symbol == PACMAN || symbol == POCMAN)) {
            break;
        }
    }
    
    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() == symbol && _pacmen[i]->getSick()) {
            _pacmen[i]->treat();
        }
    }
}


void Wizard::shareAmmunitions() {
    int a = 0;
    for (int i = 0; i < _pacmen.size(); i++) {
        a += _pacmen[i]->getAmmunitions();
    }
    a = a / _pacmen.size();
    for (int i = 0; i < _pacmen.size(); i++) {
        _pacmen[i]->setAmmunitions(a);
    }
}

bool Wizard::isSameIndex(float x1, float y1, float x2, float y2) {
    
    int i = positionToIndex(x1, y1);
    int j = positionToIndex(x2, y2);
    
    return i == j;
}

bool Wizard::isSameColumn(float x1, float x2) {
    if(abs(x1 - x2) < 0.4) {
       return true; 
    }
    return false;
}

bool Wizard::isSameLine(float y1, float y2) {
    if(abs(y1 - y2) < 0.4) {
        return true;
    }
    return false;
}

bool Wizard::isGhostOnSight(float x, float y, int direction) {
    int index;
    for (int i = 0; ; i++) {
        switch (direction) {    
            case UP:
            index = upPosition(positionToIndex(x, y), i);
            break;
            case LEFT:
            index = leftPosition(positionToIndex(x, y), i);
            break;
            case DOWN:
            index = downPosition(positionToIndex(x, y), i);
            break;
            case RIGHT:
            index = rightPosition(positionToIndex(x, y), i);
            break;
            default:
            return false;
        }

        if (_map[index] == GHOST) {
            return true;
        } else if (_map[index] == WALL || _map[index] == ' ') {
            return false;
        }
    }

    return false;
}

bool Wizard::isScaredGhostOnSight(float x, float y, int direction) {
    int index;
    for (int i = 0; ; i++) {
        switch (direction) {    
            case UP:
            index = upPosition(positionToIndex(x, y), i);
            break;
            case LEFT:
            index = leftPosition(positionToIndex(x, y), i);
            break;
            case DOWN:
            index = downPosition(positionToIndex(x, y), i);
            break;
            case RIGHT:
            index = rightPosition(positionToIndex(x, y), i);
            break;
            default:
            return false;
        }

        if (_map[index] == SCARED_GHOST) {
            return true;
        } else if (_map[index] == WALL || _map[index] == ' ') {
            return false;
        }
    }

    return false;
}

void Wizard::addAmmunitionToQueue(float x, float y) {
    std::vector<float> coords;
    coords.push_back(x);
    coords.push_back(y);
    
    _ammunitionsQueue.push(coords);
}

void Wizard::removeAmmunitionFromQueue() {
    std::vector<float> coords = _ammunitionsQueue.front();
    _ammunitionsQueue.pop();
    changeMap(coords[0], coords[1], AMMUNITION);
}


void Wizard::ghostsTrouble() {
    _bigBallsCatched++;
    for (int i = 0; i < _ghosts.size(); i++) {
        _ghosts[i]->setTrouble(true);
        _ghosts[i]->setSpeed(GHOST_ESCAPE_SPEED);
    }
    glutTimerFunc(10000, backToNormal, 1);
}

void Wizard::ghostHidden(float x, float y) {
    int ghostIndex = 0;
    for (int i = 0; i < _ghosts.size(); i++) {
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

bool Wizard::isGhostInRange(float x, float y) {
    for (int i = 0; i < _ghosts.size(); i++) {
        float pX = _ghosts[i]->getX();
        float pY = _ghosts[i]->getY();
        
        if (_ghosts[i]->getTrouble() && inRange(x, y, pX, pY, 2)) {
            _ghosts[i]->setHidden(true);
            _ghosts[i]->setTrouble(false);
            _ghosts[i]->backAgain();
            glutTimerFunc(5000, theComeBack, i);
            return true;
        }
    }

    return false;
}

int Wizard::shotGhost(float x, float y) {
    int deadGhost = 0;
    int index = positionToIndex(x, y);
    for(int i = 0; i < _ghosts.size(); i++) {
        int ghostIndex = positionToIndex(_ghosts[i]->getX(), _ghosts[i]->getY());
        if (index == ghostIndex) {
            deadGhost = _ghosts[i]->shoot(i);
            _map[ghostIndex] = _ghosts[i]->getLastSymbol();
        }
    }
    return deadGhost;
}


void Wizard::killPacman(char pacman) {
    for(int i = 0; i < _pacmen.size(); i++) {
        if (pacman == _pacmen[i]->getName()) {
            _pacmen[i]->detonate();
        }
    }
}

void Wizard::killPacman(float x, float y) {
    for (int i = 0; i < _pacmen.size(); i++) {
        float pX = _pacmen[i]->getX();
        float pY = _pacmen[i]->getY();
        
        if (!_pacmen[i]->getSick() && inRange(x, y, pX, pY, 2)) {
            _pacmen[i]->detonate();
            return;
        }
    }
}

void Wizard::broadcastMessage(Message msg) {
    char senderName = msg.getSender();
    for (int i = 0; i < _pacmen.size(); i++) {
        if (_pacmen[i]->getName() != senderName)
        _pacmen[i]->addToInbox(msg);
    }
}


void backToNormal(int value) {
    int ballsCatched = Wizard::getInstance().bigBallsCatched();
    if (ballsCatched == 1) {
        std::vector<Ghost*> ghosts = Wizard::getInstance().getGhosts();
        for (int i = 0; i < ghosts.size(); i++) {
            ghosts[i]->setTrouble(false);
            ghosts[i]->setSpeed(GHOST_NORMAL_SPEED);
        }
    }
    
    Wizard::getInstance().setBigBallsCatched(ballsCatched - 1);
}

void theComeBack(int ghostIndex) {
    std::vector<Ghost*> ghosts = Wizard::getInstance().getGhosts();
    Ghost* ghost = ghosts[ghostIndex];
    ghost->setHidden(false);
    ghost->setLife(100);
}