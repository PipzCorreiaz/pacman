#include "Section.h"

Section::Section() {
    _wall = new Wall();
}

Section::~Section() {
    delete(_wall);
}

void Section::setQuadrant(int x, int y) {
    _quadrantX = x;
	_quadrantY = y;
}


void Section::draw() {
    
    glPushMatrix();
    
    //glColor3f(0.81,0.31,0.5);
    GLfloat mat_ambient[] = {0.81f, 0.31f, 0.5f};
    GLfloat mat_diffuse[] = {0.81f, 0.31f, 0.5f};
    GLfloat mat_specular[] = {0.0f, 0.0f, 0.0f};
    GLfloat mat_shine = 0.0f; //not used anyway
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);

    _wall->intoPlace( 20 * _quadrantX, 22 * _quadrantY, 0); // Transformacao primeiro de posicao ;)
    _wall->resize(6,4);
    _wall->draw();
	
    _wall->intoPlace(20 * _quadrantX, 15 * _quadrantY, 0);
    _wall->resize(6,2);
    _wall->draw();
	
	_wall->intoPlace(9 * _quadrantX, 22 * _quadrantY, 0);
	_wall->resize(8, 4);
	_wall->draw();
	
	_wall->intoPlace(12 * _quadrantX, 9 * _quadrantY, 0);
	_wall->resize(2, 14);
	_wall->draw();
	
	_wall->intoPlace(8 * _quadrantX, 9 * _quadrantY, 0);
	_wall->resize(6, 2);
	_wall->draw();
	
	_wall->intoPlace(22 * _quadrantX, 6 * _quadrantY, 0);
	_wall->resize(10, 8);
	_wall->draw();
	
	_wall->intoPlace(28 * _quadrantX, 15 * _quadrantY, 0);
	_wall->resize(2, 26);
	_wall->draw();
	
	_wall->intoPlace(15 * _quadrantX, 29 * _quadrantY, 0);
	_wall->resize(28, 2);
	_wall->draw();
	
	_wall->intoPlace(0.5f * _quadrantX, 25 * _quadrantY, 0);
	_wall->resize(1, 10);
	_wall->draw();
	
	_wall->intoPlace(4 * _quadrantX, 15 * _quadrantY, 0);
	_wall->resize(6, 2);
	_wall->draw();
	
	_wall->intoPlace(0.5f * _quadrantX, 12 * _quadrantY, 0);
	_wall->resize(1, 8);
	_wall->draw();
	
	_wall->intoPlace(5 * _quadrantX, 3.5f * _quadrantY, 0);
	_wall->resize(4, 1);
	_wall->draw();
	
	_wall->intoPlace(6.5f * _quadrantX, 1.5f * _quadrantY, 0);
	_wall->resize(1, 3);
	_wall->draw();
   
    glPopMatrix();
    
}

