#include "Pacman.h"
#include "Wizard.h"


Pacman::Pacman() {
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
	_speed = 10; // unidades do labirinto per second
    _direction = DOWN;
    _angle = DOWN_ANGLE;
    _exploding = false;
	_eyebrow = new Eyebrow();
	_eye = new Eye();
	_cap = new MinerHat();
    _previousX = 0.0;
    _previousY = 0.0;
}

bool Pacman::getExploding() {
    return _exploding;
}

void Pacman::setExploding(bool value) {
    _exploding = value;
}


void Pacman::draw() {
    
    glPushMatrix();

    glTranslatef(getX(), getY(), getZ());
    glScalef(1.25f, 1.25f, 1.25f);
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
  
    
    _eye->intoPlace(0.375f, -0.8f, 0.0f); //olho direito
    _eye->draw();
    _eye->intoPlace(-0.375f, -0.8f, 0.0f); //olho esquerdo
    _eye->draw();
	_eyebrow->intoPlace(0.375f ,-0.848f , 0.375f); // sobranc direita
	_eyebrow->adjust(5.0f);
	_eyebrow->draw();
	_eyebrow->intoPlace(-0.375f ,-0.848f , 0.375f); //sobranc esquerda
	_eyebrow->adjust(-5.0f);
	_eyebrow->draw();
	_cap->intoPlace(0.0f, 0.0f, 0.5f);
	_cap->draw();
	
    
    glPopMatrix();
    
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
    
    
    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        move(dist);
		turn(Wizard::getInstance().availablePosition(nextPosition[0], nextPosition[1]));
		
		_previousX = round(getX());
		_previousY = round(getY());
		
	} else if(Wizard::getInstance().isGhost(nextPosition[0], nextPosition[1])) {
        if(Wizard::getInstance().isGhostInTrouble(nextPosition[0], nextPosition[1])) {
            eat(nextPosition[0], nextPosition[1], GHOST);
        }
        
        
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
    setAngle(DOWN_ANGLE);
}

void Pacman::eat(float x, float y, char symbol) {
    
    
    switch (symbol) {
        case SMALL_BALL:
            Wizard::getInstance().changeMap(x, y, HALL);
            break;
        case BIG_BALL:
            Wizard::getInstance().changeMap(x, y, HALL);
            Wizard::getInstance().ghostsTrouble();
            break;
        case GHOST:
            Wizard::getInstance().ghostHidden(x, y);
            break;
        default:
            break;
    }
}


