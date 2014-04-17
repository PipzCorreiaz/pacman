#include "Maze.h"

Maze::Maze() {
	_section = new Section();
}

Maze::~Maze() {
    delete(_section);
}


void Maze::draw() {
    
	//floor
	glColor3f(0.2f,0.2f,0.2f);
    
    GLfloat mat_ambient[] = {0.2f, 0.2f, 0.2f};
    GLfloat mat_diffuse[] = {0.2f, 0.2f, 0.2f};
    GLfloat mat_specular[] = {0, 0, 0};
    GLfloat mat_shine = 50.0f; //not used anyway
    
    GLfloat _mat_tex_ambdif[] = {  .7,  .7,  .7,  1.};
    GLfloat _mat_tex_spec[] = { .32, .32, .32, 1.};
    
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, _mat_tex_ambdif);
    glMaterialfv( GL_FRONT, GL_SPECULAR, _mat_tex_spec);
    glMaterialf(  GL_FRONT, GL_SHININESS, 13.);
    
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS); //chão
    glNormal3f( 0., 0., 1.);
    glTexCoord2f( -10, -10);
    glVertex3f(-29, -30, 0.);
    glTexCoord2f( 10, -10);
    glVertex3f(29, -30, 0.);
    glTexCoord2f( 10, 10);
    glVertex3f(29, 30, 0.);
    glTexCoord2f( -10, 10);
    glVertex3f(-29, 30, 0.);
	glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    
    glPushMatrix();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
    
	_section->setQuadrant(1,1);
	_section->draw();
    _section->setQuadrant(-1,1);
	_section->draw();
    _section->setQuadrant(-1,-1);
	_section->draw();
    _section->setQuadrant(1,-1);
	_section->draw();
    
    glPopMatrix();
	
	
} 
