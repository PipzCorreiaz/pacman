#include "Pacman.h"
#include "Wizard.h"


Pacman::Pacman() : Character() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
	_speed = 10; // unidades do labirinto per second
    _direction = DOWN;
    _angle = DOWN_ANGLE;
    _exploding = false;
	_eyebrow = new Eyebrow();
	_eye = new Eye();
    _previousX = 0.0;
    _previousY = 0.0;
    _balls = 0;
}

bool Pacman::getExploding() {
    return _exploding;
}

int Pacman::getBalls(){
    return _balls;
}

void Pacman::setExploding(bool value) {
    _exploding = value;
}


void Pacman::draw() {
    
    if (_exploding) {
        _explosion->draw();
        if(!_explosion->_areThereAnyParticles){
            setExploding(false);
            backAgain();
        }
    } else {
        
        glPushMatrix();
        
        glTranslatef(getX(), getY(), getZ());
        glScalef(1.50f, 1.50f, 1.50f);
        glRotatef(getAngle(), 0, 0, 1); // direccao do pacman
        
        //glColor3f(1, 1, 0); // Amarelo
        
        GLfloat mat_ambient[] = {1, 1, 0};
        GLfloat mat_diffuse[] = {1, 1, 0};
        GLfloat mat_specular[] = {1, 1, 0};
        GLfloat mat_shine = 100.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
        
        glutSolidSphere(1, 30, 30); // pacman r=1
        
        
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
        
        glPopMatrix();

        for(int i=0; i<_bullets.size(); i++) {
            _bullets[i]->draw();
        }
    }


    
}

void Pacman::move(float dist) {
    std::vector<float> nextPosition = Character::nextPosition(dist);
    char symbol = Wizard::getInstance().getMapSymbol(nextPosition[0], nextPosition[1]);
    
    eat(nextPosition[0], nextPosition[1], symbol);
    Character::move(dist);
}

void Pacman::update(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    int directionBack = 0;

    for(int i=0; i<_bullets.size(); i++) {
        _bullets[i]->update(dt);
    }

    
    if (_exploding) {
        _explosion->moveParticles(dt);
    } else if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        move(dist);
		turn(Wizard::getInstance().availablePosition(nextPosition[0], nextPosition[1]));
		
		_previousX = round(getX());
		_previousY = round(getY());
		
	} else if(Wizard::getInstance().isGhostScared(nextPosition[0], nextPosition[1], getDirection())) {
        move(dist);
    } else if(Wizard::getInstance().isGhost(nextPosition[0], nextPosition[1], getDirection())) {
        directionBack = turnBack();
        _bullets.push_back(new Bullet(getX(), getY(), getZ(), getDirection()));
        std::cout << _bullets.size() << std::endl;
        turn(directionBack);
        move(dist);
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
    //setAngle(DOWN_ANGLE);
}

void Pacman::eat(float x, float y, char symbol) {
    
    
    switch (symbol) {
        case SMALL_BALL:
            Wizard::getInstance().changeMap(x, y, HALL);
            _balls++;
            break;
        case BIG_BALL:
            Wizard::getInstance().changeMap(x, y, HALL);
            Wizard::getInstance().ghostsTrouble();
            _balls++;
            break;
        case SCARED_GHOST:
            Wizard::getInstance().ghostHidden(x, y);
            Wizard::getInstance().changeMap(x, y, HALL);
            break;
        case GHOST:
            detonate();
        default:
            break;
    }
}

void Pacman::detonate() {
    setExploding(true);
    _explosion = new Explosion(getX(), getY(), getZ());
}


