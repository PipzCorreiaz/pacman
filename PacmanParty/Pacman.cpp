#include "Pacman.h"
#include "Wizard.h"

void moreAmmunitions(int value);

/////////////SO DEVE SER USADO PARA O HUD
Pacman::Pacman() : Character() {
    _eye = new Eye();
	_eyebrow = new Eyebrow();
    _posZ = 1.5f;
    _angle = DOWN_ANGLE;
    _direction = DOWN;
    _sick = false;
}

Pacman::Pacman(float x, float y, float color[3], float scarfColor[3]) : Character(color) {
    init();
    _posX = x;
    _posY = y;
    _scarfColor[0] = scarfColor[0];
    _scarfColor[1] = scarfColor[1];
    _scarfColor[2] = scarfColor[2];
}

void Pacman::setName(char name) {
    _name = name;
}

void Pacman::setScarfColor(float color[3]) {
    _scarfColor[0] = color[0];
    _scarfColor[1] = color[1];
    _scarfColor[2] = color[2];
}

void Pacman::init() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.5f;
	_speed = 10; // unidades do labirinto per second
    _direction = DOWN;
    _angle = DOWN_ANGLE;
    _sick = false;
	_eyebrow = new Eyebrow();
	_eye = new Eye();
    _previousX = 0.0;
    _previousY = 0.0;
    _balls = 0;
    _ammunitions = 0;
    _lastSymbol = HALL;
}

bool Pacman::getSick() {
    return _sick;
}

int Pacman::getBalls(){
    return _balls;
}

char Pacman::getName() {
    return _name;
}

int Pacman::getAmmunitions() {
    return _ammunitions;
}

void Pacman::setSick(bool value) {
    _sick = value;
}


float* Pacman::getScarfColor() {
    return _scarfColor;
}


void Pacman::cleanUpBullets() {
    std::vector<Bullet*> newBullets;
    
    for (int i = 0; i < _bullets.size(); i++) {
        if (_bullets[i]->isActive()) {
            newBullets.push_back(_bullets[i]);
        }
    }
    _bullets = newBullets;
}

void Pacman::shoot() {
    if (_ammunitions > 0) {
        _bullets.push_back(new Bullet(getX(), getY(), getZ(), getDirection()));
        _ammunitions--;
    }
}


void Pacman::draw() {
    
    
    glPushMatrix();
    
    glTranslatef(getX(), getY(), getZ());
    glScalef(1.50f, 1.50f, 1.50f);
    
    if (_drawingHUD) {
        glRotatef(-90, 1, 0, 0);
    } else {
        glRotatef(getAngle(), 0, 0, 1);
    }
    
    _eye->intoPlace(0.375f, -0.7f, 0.0f); //olho direito
    _eye->draw();
    _eye->intoPlace(-0.375f, -0.7f, 0.0f); //olho esquerdo
    _eye->draw();
    _eyebrow->intoPlace(0.375f ,-0.848f , 0.375f); // sobranc direita
    _eyebrow->adjust(5.0f);
    _eyebrow->draw();
    _eyebrow->intoPlace(-0.375f ,-0.848f , 0.375f); //sobranc esquerda
    _eyebrow->adjust(-5.0f);
    _eyebrow->draw();
    
    if(getSick()) {
        colorize(_color);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glutSolidSphere(1.0f, 30.0f, 30.0f);
        glDisable(GL_BLEND);
    }
    else {
        colorize(_color);
        glutSolidSphere(1.0f, 30.0f, 30.0f);
    }
    
    colorize(_scarfColor);
    glTranslatef(0.0f, 0.0f, 0.65f);
    glutSolidTorus(0.15f, 0.7f, 5, 12);
    
    
    glPopMatrix();
    
    for(int i=0; i<_bullets.size(); i++) {
        _bullets[i]->draw();
    }
    
}

void Pacman::move(float dist) {
    std::vector<float> nextPosition = Character::nextPosition(dist);
    char symbol = Wizard::getInstance().getMapSymbol(nextPosition[0], nextPosition[1]);
    
    if (getSick()) {
        Wizard::getInstance().changeMap(getX(), getY(), getLastSymbol());
    } else {
        Wizard::getInstance().changeMap(getX(), getY(), HALL);
        eat(nextPosition[0], nextPosition[1], symbol);
    }
    Character::move(dist);
    Wizard::getInstance().changeMap(getX(), getY(), getName());
    setLastSymbol(symbol);
}

void Pacman::update(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    int directionBack = 0;
    
    cleanUpBullets();
    for(int i=0; i<_bullets.size(); i++) {
        _bullets[i]->update(dt);
    }
    
    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        move(dist);
		turn(Wizard::getInstance().availablePosition(nextPosition[0], nextPosition[1]));
		
		_previousX = round(getX());
		_previousY = round(getY());
    } else if(Wizard::getInstance().isGhostScared(nextPosition[0], nextPosition[1], getDirection()) && !getSick()) {
        move(dist);
    } else if(Wizard::getInstance().isGhost(nextPosition[0], nextPosition[1], getDirection()) && !getSick()) {
        shoot();
        directionBack = turnBack();
        turn(directionBack);
        //move(dist);
    } else if (Wizard::getInstance().isPacman(getName(), nextPosition[0], nextPosition[1], getDirection())) {
        Wizard::getInstance().treatIfSick(getName(), nextPosition[0], nextPosition[1], getDirection());
        directionBack = turnBack();
        turn(directionBack);
    } else if(Wizard::getInstance().canTurn(getX(), getY())) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::backAgain() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
}

void Pacman::eat(float x, float y, char symbol) {
    
    switch (symbol) {
        case SMALL_BALL:
            _balls++;
            break;
        case BIG_BALL:
            Wizard::getInstance().ghostsTrouble();
            _balls++;
            break;
        case SCARED_GHOST:
            Wizard::getInstance().ghostHidden(x, y);
            break;
        case GHOST:
            detonate();
            break;
        case AMMUNITION:
            _ammunitions += BULLETS_PER_AMMUNITION;
            Wizard::getInstance().addAmmunitionToQueue(x, y);
            glutTimerFunc(10000, moreAmmunitions, 0);
            break;
        default:
            break;
    }
}

void moreAmmunitions(int value) {
    Wizard::getInstance().removeAmmunitionFromQueue();
}

void Pacman::detonate() {
    setSick(true);
    float black[3] = {0.0f, 0.0f, 0.0f};
    setColor(black);
}

void Pacman::treat() {
    setSick(false);
    float yellow[3] = {1.0f, 1.0f, 0.0f};
    setColor(yellow);
}


