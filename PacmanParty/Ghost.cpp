#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Ghost.h"


Ghost::Ghost(int posx, int posy, int id) {
	_eye = new Eye();
	_posX = posx;
    _posY = posy; 
    _posZ = 0;
    _angle = DOWN_ANGLE;
    _direction = DOWN;
    _speed = GHOST_NORMAL_SPEED; // unidades do labirinto per second
    _trouble = false; //if true vou ser comido :D
    _ghostId = id;
    _hidden = false;
    
    _previousX = 0.0;
    _previousY = 0.0;
}


bool Ghost::getTrouble() {
    return _trouble;
}


bool Ghost::getHidden() {
    return _hidden;
}


void Ghost::setSpeed(float speed){
    _speed = speed;
}


void Ghost::setTrouble(bool trouble){
    _trouble = trouble;
}


void Ghost::setHidden(bool value){
    _hidden = value;
}


void Ghost::setColor(float a,float b,float c){
    
    // glColor4f(a, b, c, 0.5);
    
    GLfloat mat_ambient[] = {a, b, c};
    GLfloat mat_diffuse[] = {a, b, c};
    GLfloat mat_specular[] = {a, b, c};
    GLfloat mat_shine = 0.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
    
}

void Ghost::update(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    
    
    if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
        move(dist);
		turn(Wizard::getInstance().availablePosition(nextPosition[0], nextPosition[1]));
		
		_previousX = round(getX());
		_previousY = round(getY());
		
	} else {
		
		if(Wizard::getInstance().canTurn(getX(), getY())) {
			if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
				turn(Wizard::getInstance().availablePosition(getX(), getY()));
			}
			_previousX = round(getX());
			_previousY = round(getY());
			move(dist);
		}else {
			move(dist);
		}
	}
}


void Ghost::backAgain(){
    _posX = 0.0f;
	_posY = 0.0f;
}



void Ghost::draw() {
    
    glPushMatrix();
    
    
    glTranslatef(getX(),getY(), getZ()); // colocar ghost na pos (x,y,z)

	glRotatef(getAngle(), 0, 0, 1); // direccao do ghost
	
    glBegin(GL_TRIANGLE_FAN); //topo fantasma
    
    glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 3.0f); //Centro
    
    glNormal3f(1.0, 0.0, 0.47);
    glVertex3f(1.5f,0.0f,2.0f);  
    
    glNormal3f(1.0, 1.0, 0.67);
    glVertex3f(1.06f, 1.06f, 2.0f);
    
    glNormal3f(0.0, 1.0, 0.47);
    glVertex3f(0.0f, 1.5f, 2.0f);

    glNormal3f(-1.0, 1.0, 0.67);
    glVertex3f(-1.06f, 1.06f, 2.0f);

    glNormal3f(-1.0, 0.0, 0.47);
    glVertex3f(-1.5f,0.0f, 2.0f);
    
    glNormal3f(-1.0, -1.0, 0.67);
    glVertex3f(-1.06f, -1.06f, 2.0f);

    glNormal3f(-0.0, -1.0, 0.47);
    glVertex3f(0.0f, -1.5f, 2.0f);
    
    glNormal3f(1.0, -1.0, 0.67);
    glVertex3f(1.06f, -1.06f, 2.0f);
    
    glNormal3f(1.0, 0.0, 0.47);
    glVertex3f(1.5f,0.0f,2.0f);
    
    glEnd();
    

    glBegin(GL_TRIANGLE_STRIP); // faces laterais
    
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5f,0.0f,0.75f);
    
    glNormal3f(1.0, 0.0, 0.47);
    glVertex3f(1.5f,0.0f,2.0f); 
    
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(1.06f, 1.06f, 0.75f);
    
    glNormal3f(1.0, 1.0, 0.67);
    glVertex3f(1.06f, 1.06f, 2.0f);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0f, 1.5f, 0.75f);
    
    glNormal3f(0.0, 1.0, 0.47);
    glVertex3f(0.0f, 1.5f, 2.0f);

    glNormal3f(-1.0, 1.0, 0.0);
    glVertex3f(-1.06f, 1.06f, 0.75f);
    
    glNormal3f(-1.0, 1.0, 0.67);
    glVertex3f(-1.06f, 1.06f, 2.0f);
    
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.5f,0.0f, 0.75f);
    
    glNormal3f(-1.0, 0.0, 0.47);
    glVertex3f(-1.5f,0.0f, 2.0f);
    
    glNormal3f(-1.0, -1.0, 0.0);
    glVertex3f(-1.06f, -1.06f, 0.75f);
    
    glNormal3f(-1.0, -1.0, 0.67);
    glVertex3f(-1.06f, -1.06f, 2.0f);
    
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0f, -1.5f, 0.75f);
    
    glNormal3f(0.0, -1.0, 0.47);
    glVertex3f(0.0f, -1.5f, 2.0f);

    glNormal3f(1.0, -1.0, 0.0);
    glVertex3f(1.06f, -1.06f, 0.75f);
    
    glNormal3f(1.0, -1.0, 0.67);
    glVertex3f(1.06f, -1.06f, 2.0f);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5f,0.0f,0.75f);
    
    glNormal3f(1.0, 0.0, 0.47);
    glVertex3f(1.5f,0.0f,2.0f);


    glEnd();
    
    // patas
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(1.06,1.06,0.75); 
    glNormal3f(1.06, 0.44, 0.0);
    glVertex3f(1.39,0.57,0); 
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5, 0.0, 0.75);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(0.0, 1.5, 0.0);
    glVertex3f(0, 1.5, 0.75);
    glNormal3f(0.44, 1.06, 0.0);
    glVertex3f(0.57,1.39,0); 
    glNormal3f(1.0, 1.0, 0.0);
    glVertex3f(1.06,1.06,0.75);     
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(-1.0, 1.0, 0.0);
    glVertex3f(-1.06,1.06,0.75); 
    glNormal3f(-0.44, 1.06, 0.0);
    glVertex3f(-0.57,1.39,0); 
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0, 1.5, 0.75);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(-1.0, 1.0, 0.0);
    glVertex3f(-1.06,1.06,0.75);
    glNormal3f(-1.06, 0.44, 0.0);
    glVertex3f(-1.39,0.57,0); 
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.5, 0.0, 0.75);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(-1.0, -1.0, 0.0);
    glVertex3f(-1.06,-1.06,0.75); 
    glNormal3f(-1.06, -0.44, 0.0);
    glVertex3f(-1.39,-0.57,0); 
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-1.5, 0.0, 0.75);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(-1.0, -1.0, 0.0);
    glVertex3f(-1.06,-1.06,0.75); 
    glNormal3f(-0.44, -1.06, 0.0);
    glVertex3f(-0.57,-1.39,0); 
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, -1.5, 0.75);
    glEnd();
    
    glBegin(GL_TRIANGLES);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, -1.5, 0.75);
    glNormal3f(0.44, -1.06, 0.0);
    glVertex3f(0.57,-1.39,0); 
    glNormal3f(1.0, -1.0, 0.0);
    glVertex3f(1.06,-1.06,0.75); 
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(1.0, -1.0, 0.0);
    glVertex3f(1.06,-1.06,0.75); 
    glNormal3f(0.44, -1.06, 0.0);
    glVertex3f(1.39,-0.57,0); 
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(1.5, 0, 0.75);
    glEnd();
    
    
    
    _eye->intoPlace(0.4f, -1.28f, 2.0f); //olho direito
    _eye->draw();
    _eye->intoPlace(-0.4f, -1.28f, 2.0f); //olho esquerdo
    _eye->draw();
	
    
    glPopMatrix();
    
}


