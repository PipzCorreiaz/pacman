#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Pacman.h"

Pacman::Pacman(){
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
    _direction = _pauseAngle = 0;
	_up = _down = _left = _right = false; //inicia parado
    _down = true;
	_speed = 10; // unidades do labirinto per second
    //_left = true; // possivel direccao inicial
    _angle = 1;
	_eye = new Eye();
	_eyebrow = new Eyebrow();
	_cap = new MinerHat();
    _turnedUp = _turnedRight = _turnedLeft = false;
    _turnedDown = true;
    _explodingTime = false;
    
}

Pacman::~Pacman(){}

// ACRESCENTAR OS EIXOS PARA ELE OLHAR :D
int Pacman::getAngle(){
    return _angle;
}

void Pacman::setAngle(float posX, float posY){

}

bool Pacman::isGhost(){
    return false;
}


void Pacman::draw() {
    
    glPushMatrix();

    glTranslatef(getX(),getY(), getZ()); // colocar pacman na pos (x,y,z)
    glScalef(1.25f, 1.25f, 1.25f); //Pacman um bocadinho maior
	glRotatef(getDirection(), 0, 0, 1); // direccao do pacman
	glRotatef(getPauseAngle(), 1, 0, 0);
    
	
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

void Pacman::backAgain(){
    _posX = 9.0f;
	_posY = 6.0f;
    _posZ = 1.25f;
    _explodingTime = false;
    resetMove();
    _direction = 0;
}



void Pacman::update(float dt) {
    float dist = getSpeed() * dt;
    int dir = rand() % 4;
    turn(dir);
    move(dist);
}

