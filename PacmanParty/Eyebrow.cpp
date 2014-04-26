#include "Eyebrow.h"

Eyebrow::Eyebrow() {
	_posX= _posY = _posZ = 0;
}

Eyebrow::~Eyebrow() {

}

void Eyebrow::intoPlace(float posX, float posY, float posZ) {
    _posX = posX;
    _posY = posY;
    _posZ = posZ;
}

void Eyebrow::adjust(float angle) {
	_angle = angle;
}

void Eyebrow::draw() {

	glPushMatrix();
    
    GLfloat mat_ambient[] = {0.25, 0.15, 0.075};
    GLfloat mat_diffuse[] = {0.25, 0.15, 0.075};
    GLfloat mat_specular[] = {0.25, 0.15, 0.075};
    GLfloat mat_shine = 100.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
    
    glTranslatef(_posX,_posY,_posZ);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 0.25f, 0.25f);
	glutSolidSphere(0.25, 30, 30); //raio do olho 0.25	
    
    glPopMatrix();


}