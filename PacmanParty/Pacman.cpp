#include "Pacman.h"
#include "Wizard.h"


Pacman::Pacman() : Character() {
    init();
}

Pacman::Pacman(float x, float y) {
    init();
    _posX = x;
    _posY = y;
}

void Pacman::setName(char name) {
    _name = name;
}

void Pacman::init() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
	_speed = 10; // unidades do labirinto per second
    _direction = DOWN;
    _angle = DOWN_ANGLE;
    _exploding = false;
    _sick = false;
	_eyebrow = new Eyebrow();
	_eye = new Eye();
    _previousX = 0.0;
    _previousY = 0.0;
    _balls = 0;
    _ammunitions = 0;
    _lastSymbol = HALL;
}

bool Pacman::getExploding() {
    return _exploding;
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

void Pacman::setExploding(bool value) {
    _exploding = value;
}

void Pacman::setSick(bool value) {
    _sick = value;
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
        glRotatef(getAngle(), 0, 0, 1); // direccao do pacman
        
        //glColor3f(1, 1, 0); // Amarelo

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

    setColor(0,0,0,40.0);
    if(getSick()) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glutSolidSphere(1, 30, 30);
        glDisable(GL_BLEND);
    } 
    else {
        setColor(1,1,0,100.0);
        glutSolidSphere(1, 30, 30);
    }
    
     // pacman r=1

    glPopMatrix();

    for(int i=0; i<_bullets.size(); i++) {
        _bullets[i]->draw();
    }
    
}

void Pacman::move(float dist) {
    std::vector<float> nextPosition = Character::nextPosition(dist);
    char symbol = Wizard::getInstance().getMapSymbol(nextPosition[0], nextPosition[1]);

    eat(nextPosition[0], nextPosition[1], symbol);
    if (getSick()) {
        Wizard::getInstance().changeMap(getX(), getY(), getLastSymbol());
    } else {
        Wizard::getInstance().changeMap(getX(), getY(), HALL);
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
    setExploding(false);
}

void Pacman::eat(float x, float y, char symbol) {
    
    
    switch (symbol) {
        case SMALL_BALL:
//            Wizard::getInstance().changeMap(x, y, HALL);
            _balls++;
            break;
        case BIG_BALL:
//            Wizard::getInstance().changeMap(x, y, HALL);
            Wizard::getInstance().ghostsTrouble();
            _balls++;
            break;
        case SCARED_GHOST:
            Wizard::getInstance().ghostHidden(x, y);
//            Wizard::getInstance().changeMap(x, y, HALL);
            break;
        case GHOST:
            detonate();
            break;
        case AMMUNITION:
            _ammunitions += BULLETS_PER_AMMUNITION;
            break;
        default:
            break;
    }
}

void Pacman::detonate() {
    setSick(true);
    //setExploding(true);
    //_explosion = new Explosion(getX(), getY(), getZ());

}


