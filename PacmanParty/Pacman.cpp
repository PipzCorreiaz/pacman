#include "Pacman.h"
#include "Wizard.h"
#include "Message.h"


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
    _mode = REACTIVE_MODE;

    startChat();

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

std::string Pacman::getCrossingMap() {
    return _crossingMap;
}

void Pacman::setCrossingMap(std::string map) {
    _crossingMap = map;
}

void Pacman::setMode(int mode) {
    _mode = mode;
}

void Pacman::printCrossingMap() {
    int limit = 0;
    for (int i = 0; i < _crossingMap.length(); i++) {
        std::cout << _crossingMap[i];
        limit++;
        if (limit == 55) {
            std::cout << std::endl;
            limit = 0;
        }
    }
    
    std::cout << std::endl;
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

void Pacman::changeCrossingMap(float x, float y, char symbol) {
    int index = Wizard::getInstance().positionToIndex(x, y);
    _crossingMap[index] = symbol;
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
                // Wizard::getInstance().ghostHidden(x, y);
                // setGhostCatched();
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

void Pacman::catchGhost() {
    if (Wizard::getInstance().isGhostInRange(getX(), getY())) {
        setGhostCatched();
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
    catchGhost();
    Wizard::getInstance().changeMap(getX(), getY(), getName());
    setLastSymbol(symbol);
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

void Pacman::update(float dt) {
    cleanUpBullets();
    for(int i=0; i<_bullets.size(); i++) {
        if(_bullets[i]->update(dt) == 1) {
            setGhostCatched();
        }
    }
    if(getSick()) {
        sendMessage(BE_HEALED);
    } else if (_ammunitions == 0) {
        sendMessage(TRANSFER_AMMUNITION);
    }

    switch (_mode) {
        case REACTIVE_MODE:
            reactive(dt);
            break;
        case BDI_MODE:
            deliberative(dt);
            break;
        case HYBRID_MODE:
            hybrid(dt);
            break;
    }
    //reactive(dt);
    //deliberative(dt);
    //hybrid(dt);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////REACTIVE///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////DELIBERATIVE//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



void Pacman::deliberative(float dt) {
    if (!_hasPlan) {
        percept(dt);
        options();
        _intention = filter();
    }

    plan(dt);
    percept(dt);
}

void Pacman::plan(float dt) {
    _hasPlan = true;

    switch (_intention) {
        case BE_HEALED:
            //std::cout << _name << ": BE HEALED" << std::endl;
            beHealed(dt);
            break;
        case KILL_GHOST:
            //std::cout << _name << ": KILL GHOST" << std::endl;
            killGhost(dt);
            break;
        case EAT_GHOST:
            eatGhost(dt);
            break;
        case RUNAWAY:
            //std::cout << _name << ": RUNAWAY" << std::endl;
            runaway(dt);
            break;
        case HEAL_PACMAN:
            //std::cout << _name << ": HEAL PACMAN" << std::endl;
            healPacman(dt);
            break;
        case EAT_BIG_BALL:
            //std::cout << _name << ": EAT BIG BALL" << std::endl;
            eatBigBall(dt);
            break;
        case TRANSFER_AMMUNITION:
            //std::cout << _name << ": TRANSFER AMMUNITION" << std::endl;
            transferAmmunition(dt);
            break;
        default:
            //std::cout << _name << ": EAT SMALL BALL" << std::endl;
            eatSmallBall(dt);
            break;
    }
}


void Pacman::eatSmallBall(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if(getSick()) {
        _hasPlan = false;    
    } else if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } 
    else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithBall(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (_beliefs[BIG_BALL] && !_beliefs[TRAIL]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePositionExceptCurrent(getX(), getY(), getDirection()));
        }     
    } else {
        move(dist);
    }
    _hasPlan = false;
}

void Pacman::eatBigBall(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } 
    else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithBall(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
        sendMessage(EAT_GHOST);
    }
    _hasPlan = false;
}

void Pacman::killGhost(float dt) {
    float dist = getSpeed() * dt;

    int directionBack = turnBack();

     if(getSick()) {
        _hasPlan = false;    
    } else if (_ammunitions == 0) {
        _hasPlan = false;
    } else if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[GHOST] && _beliefs[CROSSING]) {
        shoot();
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (_beliefs[GHOST]) {
        shoot();
        move(dist);
    } else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::eatGhost(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

     if(getSick()) {
        _hasPlan = false;    
    } else if (_beliefs[GHOST]) {
        _hasPlan = false;
    } else if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[SCARED_GHOST]) {
        move(dist);
    } else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithScaredGhost(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }

    _messages[EAT_GHOST] = false;
}

void Pacman::beHealed(float dt) {
    float dist = getSpeed() * dt;
    int direction = 0;
    int directionBack = turnBack();

    if(getSick() && _beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if(getSick() && _beliefs[CROSSING]) {
        if (Wizard::getInstance().isPacmanOnAnyDirection(getName(), getX(), getY())) {
            direction = Wizard::getInstance().directionToTurn(getName(), getX(), getY());

            if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                if (Wizard::getInstance().isAvailableDirection(getX(), getY(), direction)) {
                    turn(direction);
                } else {
                    turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
                }
            }
        } else {
            if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
            }
        }

        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if(getSick()){
        if (Wizard::getInstance().isPacmanOnSights(getName(), getX(), getY(), getDirection())) {
            direction = Wizard::getInstance().directionToTurn(getName(), getX(), getY());
            if(direction != getDirection()) {

                if (Wizard::getInstance().isAvailableDirection(getX(), getY(), direction)) {
                    turn(direction);
                } else {
                    int dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                    turn(dir);
                }
            }
        }
        move(dist);
    } else {
        _hasPlan = false;
    }
}

void Pacman::healPacman(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    Wizard::getInstance().treatIfSick(getName(), nextPosition[0], nextPosition[1], getDirection());
    int directionBack = turnBack();

     if(getSick()) {
        _hasPlan = false;    
    } else if (!_messages[BE_HEALED]) {
        _hasPlan = false;
    } else  if(_beliefs[PACMAN_SICK] || _beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
    } else if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            int dir = Wizard::getInstance().smartDirection(getName(), getX(), getY());
            if (Wizard::getInstance().isAvailableDirection(getX(), getY(), dir)) {
                turn(dir);
            } else {
                dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                turn(dir);
            }
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
    
    _messages[BE_HEALED] = false;
}

// void Pacman::runaway(float dt) {
//     float dist = getSpeed() * dt;
//     int directionBack = turnBack();

//     if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
//         turn(directionBack);
//     } else {
//         int dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
//         turn(dir);
//     }

//     _previousX = round(getX());
//     _previousY = round(getY());
//     move(dist);
//     _hasPlan = false;
// }


void Pacman::runaway(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if(getSick()) {
        _hasPlan = false;    
    } else if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().directionOnCrossing(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
        turn(directionBack);
        if(Wizard::getInstance().isGhostOnSight(getX(), getY(), getDirection())) {
            int dir = Wizard::getInstance().runToCrossing(getX(), getY(), getDirection(), getCrossingMap());
            //std::cout << "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL " << dir << std::endl;
            turn(dir);
        }
        move(dist);
    } else {
        move(dist);
    }
        _hasPlan = false;
}

void Pacman::transferAmmunition(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if(getSick()) {
        _hasPlan = false;    
    } else if (_beliefs[PACMAN_SICK]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
        _hasPlan = false; 

    } else if (_beliefs[PACMAN]) {
        Wizard::getInstance().shareAmmunitions();
        _hasPlan = false;
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            int dir = Wizard::getInstance().smartDirection(getName(), getX(), getY());
            if (Wizard::getInstance().isAvailableDirection(getX(), getY(), dir)) {
                turn(dir);
            } else {
                dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                turn(dir);
            }
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
    
    _messages[TRANSFER_AMMUNITION] = false;  
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////HYBRID////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



void Pacman::hybrid(float dt) {
    
    if (!_hasPlan) {
        percept(dt);
        options();
        _intention = filter();
    }

    hybridPlan(dt);
    if (reconsider(dt)) {
        percept(dt);
        options();
        _intention = filter();
    }
}


void Pacman::hybridPlan(float dt) {
    _hasPlan = true;

    switch (_intention) {
        case BE_HEALED:
            //std::cout << _name << ": BE HEALED" << std::endl;
            beHealedHybrid(dt);
            break;
        case KILL_GHOST:
            //std::cout << _name << ": KILL GHOST" << std::endl;
            killGhostHybrid(dt);
            break;
        case EAT_GHOST:
            eatGhostHybrid(dt);
            break;
        case RUNAWAY:
            //std::cout << _name << ": RUNAWAY" << std::endl;
            runawayHybrid(dt);
            break;
        case HEAL_PACMAN:
            //std::cout << _name << ": HEAL PACMAN" << std::endl;
            healPacmanHybrid(dt);
            break;
        case EAT_BIG_BALL:
            //std::cout << _name << ": EAT BIG BALL" << std::endl;
            eatBigBallHybrid(dt);
            break;
        case TRANSFER_AMMUNITION:
            //std::cout << _name << ": TRANSFER AMMUNITION" << std::endl;
            transferAmmunitionHybrid(dt);
            break;
        default:
            //std::cout << _name << ": EAT SMALL BALL" << std::endl;
            eatSmallBallHybrid(dt);
            break;
    }
}


void Pacman::eatSmallBallHybrid(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();
    if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } 
    else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithBall(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (_beliefs[BIG_BALL] && !_beliefs[TRAIL]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePositionExceptCurrent(getX(), getY(), getDirection()));
        }     
    } else {
        move(dist);
    }
}

void Pacman::eatBigBallHybrid(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();
    if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } 
    else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithBall(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
        sendMessage(EAT_GHOST);
    }
}

void Pacman::killGhostHybrid(float dt) {
    float dist = getSpeed() * dt;

    int directionBack = turnBack();
    if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[GHOST] && _beliefs[CROSSING]) {
        shoot();
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (_beliefs[GHOST]) {
        shoot();
        move(dist);
    } else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::eatGhostHybrid(float dt) {
    float dist = getSpeed() * dt;

    int directionBack = turnBack();
    if(_beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[SCARED_GHOST]) {
        move(dist);
    } else if (_beliefs[CROSSING]) {
        if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().availablePositionWithScaredGhost(getX(), getY()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }

    _messages[EAT_GHOST] = false;
}

void Pacman::beHealedHybrid(float dt) {
    float dist = getSpeed() * dt;
    int direction = 0;
    int directionBack = turnBack();

    if(getSick() && _beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        }else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if(getSick() && _beliefs[CROSSING]) {
        if (Wizard::getInstance().isPacmanOnAnyDirection(getName(), getX(), getY())) {
            direction = Wizard::getInstance().directionToTurn(getName(), getX(), getY());

            if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                if (Wizard::getInstance().isAvailableDirection(getX(), getY(), direction)) {
                    turn(direction);
                } else {
                    turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
                }
            }
        } else {
            if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
            }
        }

        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if(getSick()){
        if (Wizard::getInstance().isPacmanOnSights(getName(), getX(), getY(), getDirection())) {
            direction = Wizard::getInstance().directionToTurn(getName(), getX(), getY());
            if(direction != getDirection()) {

                if (Wizard::getInstance().isAvailableDirection(getX(), getY(), direction)) {
                    turn(direction);
                } else {
                    int dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                    turn(dir);
                }
            }
        }
        move(dist);
    } else {
        _hasPlan = false;
    }
}

void Pacman::healPacmanHybrid(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    Wizard::getInstance().treatIfSick(getName(), nextPosition[0], nextPosition[1], getDirection());
    int directionBack = turnBack();


    if(_beliefs[PACMAN_SICK] || _beliefs[PACMAN]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY(), getDirection()));
        }
    } else if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            int dir = Wizard::getInstance().smartDirection(getName(), getX(), getY());
            if (Wizard::getInstance().isAvailableDirection(getX(), getY(), dir)) {
                turn(dir);
            } else {
                dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                turn(dir);
            }
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
    
    _messages[BE_HEALED] = false;
}

// void Pacman::runawayHybrid(float dt) {
//     float dist = getSpeed() * dt;
//     int directionBack = turnBack();
//     if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
//         turn(directionBack);
//     } else {
//         int dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
//         turn(dir);
//     }

//     _previousX = round(getX());
//     _previousY = round(getY());
//     move(dist);
// }

void Pacman::runawayHybrid(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            turn(Wizard::getInstance().directionOnCrossing(getX(), getY(), getDirection()));
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
        turn(directionBack);
        if(Wizard::getInstance().isGhostOnSight(getX(), getY(), getDirection())) {
            int dir = Wizard::getInstance().runToCrossing(getX(), getY(), getDirection(), getCrossingMap());
            //std::cout << "LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOL " << dir << std::endl;
            turn(dir);
        }
        move(dist);
    } else {
        move(dist);
    }
}

void Pacman::transferAmmunitionHybrid(float dt) {
    float dist = getSpeed() * dt;
    int directionBack = turnBack();

    if (_beliefs[PACMAN_SICK]) {
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }

    } else if (_beliefs[PACMAN]) {
        Wizard::getInstance().shareAmmunitions();
        if (Wizard::getInstance().isAvailableDirection(getX(), getY(), directionBack)) {
            turn(directionBack);
        } else {
            turn(Wizard::getInstance().availablePosition(getX(), getY()));
        }
    } else if (_beliefs[CROSSING]) {
        if (!(_previousX == round(getX()) && _previousY == round(getY()))) {
            int dir = Wizard::getInstance().smartDirection(getName(), getX(), getY());
            if (Wizard::getInstance().isAvailableDirection(getX(), getY(), dir)) {
                turn(dir);
            } else {
                dir = Wizard::getInstance().availablePosition(getX(), getY(), getDirection());
                turn(dir);
            }
        }
        _previousX = round(getX());
        _previousY = round(getY());
        move(dist);
    } else {
        move(dist);
    }
    
    _messages[TRANSFER_AMMUNITION] = false;  
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////// COMMOM FUNCTIONS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void Pacman::percept(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);

    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        _beliefs[WALL] = true;
    } else {
        _beliefs[WALL] = false;
    }

    if(Wizard::getInstance().isScaredGhostOnSight(getX(), getY(), getDirection())) {
        _beliefs[SCARED_GHOST] = true;
    } else {
        _beliefs[SCARED_GHOST] = false;
    }        

    
    if (Wizard::getInstance().isGhostOnSight(getX(), getY(), getDirection())) {
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
        changeCrossingMap(getX(), getY(), CROSSING);

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

    
    if (!_beliefs[AMMUNITION] && _ammunitions == 0 && _beliefs[GHOST]) {
        _desires[RUNAWAY] = true;
    } else {
        _desires[RUNAWAY] = false;
    }

    
    if (_beliefs[GHOST]) {
        _desires[KILL_GHOST] = true;
    } else {
        _desires[KILL_GHOST] = false;
    }

    if (_beliefs[SCARED_GHOST] || _messages[EAT_GHOST]) {
        _desires[EAT_GHOST] = true;
    } else {
        _desires[EAT_GHOST] = false;
    }

    if (_beliefs[BIG_BALL] && _beliefs[TRAIL] && !_beliefs[SCARED_GHOST]) {
        _desires[EAT_BIG_BALL] = true;
    } else {
        _desires[EAT_BIG_BALL] = false;
    }

    if (_beliefs[PACMAN_SICK] || _messages[BE_HEALED]) {
        _desires[HEAL_PACMAN] = true;
    } else {
        _desires[HEAL_PACMAN] = false;
    }

    if (getSick()) {
        _desires[BE_HEALED] = true;
    } else {
        _desires[BE_HEALED] = false;
    }

    if (_ammunitions != 0 && _messages[TRANSFER_AMMUNITION]) {
        _desires[TRANSFER_AMMUNITION] = true;
    } else {
        _desires[TRANSFER_AMMUNITION] = false;
    }
}

int Pacman::filter() {

    if (_desires[BE_HEALED]) {
        return BE_HEALED;
    }
    if (_desires[EAT_GHOST]) {
        return EAT_GHOST;
    }
    if (_desires[RUNAWAY]) {
        return RUNAWAY;
    }
    if (_desires[KILL_GHOST]) {
        return KILL_GHOST;
    }
    if (_desires[EAT_BIG_BALL]) {
        return EAT_BIG_BALL;
    }
    if (_desires[HEAL_PACMAN]) {
        return HEAL_PACMAN;
    }
    if (_desires[TRANSFER_AMMUNITION]) {
        return TRANSFER_AMMUNITION;
    }
    return EAT_SMALL_BALL;
}

bool Pacman::reconsider(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);

    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection()) != _beliefs[WALL]) {
        return true;
    }

    if(Wizard::getInstance().isGhostScared(nextPosition[0], nextPosition[1]) != _beliefs[SCARED_GHOST]) {
        return true;
    }        

    if(Wizard::getInstance().isGhostOnSight(getX(), getY(), getDirection()) != _beliefs[GHOST]) {
        return true;
    }

    if (Wizard::getInstance().isPacman(getName(), nextPosition[0], nextPosition[1], getDirection()) != _beliefs[PACMAN]) {
        return true;
    }

    if (Wizard::getInstance().isPacmanSick(getName(), nextPosition[0], nextPosition[1], getDirection()) != _beliefs[PACMAN_SICK]) {
        return true;
    }

    if (Wizard::getInstance().isAmmunition(nextPosition[0], nextPosition[1], getDirection()) != _beliefs[AMMUNITION]) {
        return true;
    }

    if (Wizard::getInstance().isBigBall(nextPosition[0], nextPosition[1], getDirection()) != _beliefs[BIG_BALL]) {
        return true;
    }

    if (Wizard::getInstance().canTurn(getX(), getY(), getDirection()) != _beliefs[CROSSING]) {
        return true;
    }

    if (Wizard::getInstance().isGhostTrail(nextPosition[0], nextPosition[1]) != _beliefs[TRAIL]) {
        return true;
    }

    return false;

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////// MESSAGE SYSTEM ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void Pacman::analyseMessage(Message msg) {
    switch (msg.getMessage()) {
        case TRANSFER_AMMUNITION:
            _messages[TRANSFER_AMMUNITION] = true;
            break;
        case BE_HEALED:
            _messages[BE_HEALED] = true;
            break;
        case EAT_GHOST:
            _messages[EAT_GHOST] = true;
            break;
        default:
            break;
    }
}

void Pacman::sendMessage(int message) {
    Message msg(_name, getX(), getY(), message);
    Wizard::getInstance().broadcastMessage(msg);
}

Message Pacman::receiveMessage() {
    std::cout << _name << " is ready to receive messages" << std::endl;
    while (true) {
        if (!_inbox.empty()) {
            Message msg = _inbox.front();
            analyseMessage(msg);
            _inbox.pop();

            //std::cout << "> " << msg.toString() << std::endl;
        }
    }
}

void Pacman::addToInbox(Message msg) {
    _inbox.push(msg);
}

void Pacman::startChat() {
    _chat = std::thread(&Pacman::receiveMessage, this);
}



