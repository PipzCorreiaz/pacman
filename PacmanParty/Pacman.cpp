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
    _ghostCatched = 0;
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

void Pacman::setGhostCatched() {
    _ghostCatched = _ghostCatched + 1;
}

void Pacman::setAmmunitions(int value) {
    _ammunitions = value;
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
    _ghostCatched = 0;
    _hasPlan = false;
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

int Pacman::getGhostCatched() {
    return _ghostCatched;
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
    
    if (getSick()) {
        glEnable(GL_BLEND);
        glBlendFunc (GL_ONE, GL_DST_COLOR);
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
        float zombieGreen[3] = {0.1f, 0.4f, 0.2f};
        colorize(zombieGreen);
    }
    else {
        colorize(_color);
    }
    
    glutSolidSphere(1.0f, 30.0f, 30.0f);
    colorize(_scarfColor);
    glTranslatef(0.0f, 0.0f, 0.65f);
    glutSolidTorus(0.15f, 0.7f, 5, 12);
    
    
    glPopMatrix();
    
    for(int i=0; i<_bullets.size(); i++) {
        _bullets[i]->draw();
    }
    
    if (getSick()) {
        glDisable(GL_BLEND);
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




void Pacman::reactive(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    int directionBack = 0;
    
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

void Pacman::percept(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);

    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[WALL] = true;
    } else {
        _beliefs[WALL] = false;
    }

    if(Wizard::getInstance().isGhostScared(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[SCARED_GHOST] = true;
    } else {
        _beliefs[SCARED_GHOST] = false;
    }        

    if(Wizard::getInstance().isGhost(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[GHOST] = true;
    } else {
        _beliefs[GHOST] = false;
    }

    if (Wizard::getInstance().isPacman(getName(), nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[PACMAN] = true;
    } else {
        _beliefs[PACMAN] = false;
    }
    if (Wizard::getInstance().isPacmanSick(getName(), nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[PACMAN_SICK] = true;
    } else {
        _beliefs[PACMAN_SICK] = false;
    }

    if (Wizard::getInstance().isAmmunition(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[AMMUNITION] = true;
    } else {
        _beliefs[AMMUNITION] = false;
    }

    if (Wizard::getInstance().isBigBall(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[BIG_BALL] = true;
    } else {
        _beliefs[BIG_BALL] = false;
    }

    if (Wizard::getInstance().canTurn(getX(), getY(), getDirection())) {
        _beliefs[CROSSING] = true;
    } else {
        _beliefs[CROSSING] = false;
    }

    if (Wizard::getInstance().isGhostTrail(nextPosition[0], nextPosition[1])) {
        _beliefs[TRAIL] = true;
    } else {
        _beliefs[TRAIL] = false;
    }

 
}

void Pacman::options() {

    if (_beliefs[BIG_BALL] || _beliefs[AMMUNITION] || _ammunitions != 0 || _beliefs[SCARED_GHOST]) {
        _desires[KILL_GHOST] = true;
    } else {
        _desires[KILL_GHOST] = false;
    }

    if (!_beliefs[AMMUNITION] && _ammunitions == 0 && _beliefs[GHOST]) {
        _desires[RUNAWAY] = true;
    } else {
        _desires[RUNAWAY] = false;
    }

    if (_beliefs[BIG_BALL] && _beliefs[TRAIL] && !_beliefs[SCARED_GHOST]) {
        _desires[EAT_BIG_BALL] = true;
    } else {
        _desires[EAT_BIG_BALL] = false;
    }

    if (_beliefs[PACMAN_SICK]) {
        _desires[HEAL_PACMAN] = true;
    } else {
        _desires[HEAL_PACMAN] = false;
    }

    if (getSick()) {
        _desires[BE_HEALED] = true;
    } else {
        _desires[BE_HEALED] = false;
    }

    if (_ammunitions != 0 && _beliefs[PACMAN]) {
        _desires[TRANSFER_AMMUNITION] = true;
    } else {
        _desires[TRANSFER_AMMUNITION] = false;
    }
}

int Pacman::filter() {

    if (_desires[BE_HEALED]) {
        return BE_HEALED;
    }
    if (_desires[KILL_GHOST]) {
        return KILL_GHOST;
    }
    if (_desires[RUNAWAY]) {
        return RUNAWAY;
    }
    if (_desires[HEAL_PACMAN]) {
        return HEAL_PACMAN;
    }
    if (_desires[EAT_BIG_BALL]) {
        return EAT_BIG_BALL;
    }
    if (_desires[TRANSFER_AMMUNITION]) {
        return TRANSFER_AMMUNITION;
    }
    return EAT_SMALL_BALL;
}

void Pacman::plan(float dt) {
    _hasPlan = true;

    switch (_intention) {
        case BE_HEALED:
            std::cout << "be_healed" << std::endl;
            be_healed(dt);
            break;
        case KILL_GHOST:
            killGhost(dt);
            break;
        case RUNAWAY:
            runaway(dt);
            break;
        case HEAL_PACMAN:
            break;
        case EAT_BIG_BALL:
            break;
        case TRANSFER_AMMUNITION:
            transferAmmunition(dt);
            break;
        default:
            eatSmallBall(dt);
            break;
    }
}

void Pacman::eatSmallBall(float dt) {
    float dist = getSpeed() * dt;

    if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithBall(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::killGhost(float dt) {
    float dist = getSpeed() * dt;

    if (_beliefs[GHOST]) {
        float bulletsNeeded = 100 / GUN_POWER;
        if (_ammunitions > bulletsNeeded) {
            for (int i = 0; i < bulletsNeeded; i++) {
                shoot();
            }
        } else {
            for (int i = 0; i < _ammunitions; i++) {
                shoot();
            }
        }
    } else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithGhost(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::be_healed(float dt) {
    float dist = getSpeed() * dt;
    int friendDirection = 0;

    if(getSick() && _beliefs[CROSSING]) {
        if (Wizard::getInstance().pacmanVision(getName(), getX(), getY())) {
            friendDirection = Wizard::getInstance().friendDirection(getName());
            if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                turn(friendDirection);
            }
            _previousX = round(getX());
            _previousY = round(getY());
            move(dist);
            _hasPlan = false;
        }
    } else {
        move(dist);
    }
}

void Pacman::heal_pacman(float dt) {
}

void Pacman::deliberative(float dt) {
    percept(dt);
    
    if (!_hasPlan) {
        options();
        _intention = filter();
    }

    plan(dt);
}

void Pacman::update(float dt) {
    cleanUpBullets();
    for(int i=0; i<_bullets.size(); i++) {
        if(_bullets[i]->update(dt) == 1) {
            setGhostCatched();
        }
    }
    //reactive(dt);
    deliberative(dt);
}


void Pacman::runaway(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();
    turn(directionBack);
    move(dist);
    _hasPlan = false;
}


void Pacman::transferAmmunition(float dt) {
    float dist = getSpeed() * dt;
    if (_beliefs[PACMAN]) {
        Wizard::getInstance().shareAmmunitions();
        _hasPlan = false;
    }
    move(dist);
}


void Pacman::backAgain() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
}

void Pacman::eat(float x, float y, char symbol) {
    
    if (!getSick()) {
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
                setGhostCatched();
				break;
            case AMMUNITION:
                _ammunitions += BULLETS_PER_AMMUNITION;
                Wizard::getInstance().addAmmunitionToQueue(x, y);
                glutTimerFunc(30000, moreAmmunitions, 0);
                break;
            default:
                break;
        }
    }
}

void moreAmmunitions(int value) {
    Wizard::getInstance().removeAmmunitionFromQueue();
}

void Pacman::detonate() {
    setSick(true);
    _ammunitions = 0;
}

void Pacman::treat() {
    setSick(false);
}


