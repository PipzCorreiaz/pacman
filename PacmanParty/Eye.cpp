#include "Eye.h"

Eye::Eye() {
	_posX = _posY = _posZ = 0;
    
}

Eye::~Eye() {

}

void Eye::intoPlace(float posX, float posY, float posZ) {
    _posX = posX;
    _posY = posY;
    _posZ = posZ;
}

void Eye::draw() {
    
    glPushMatrix();
    
    GLfloat mat_ambient_eye[] = {1, 1, 1};
    GLfloat mat_diffuse_eye[] = {1, 1, 1};
    GLfloat mat_specular_eye[] = {1, 1, 1};
    GLfloat mat_shine_eye = 1.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_eye);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_eye);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_eye);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine_eye);
    
    glTranslatef(_posX,_posY, _posZ);
	glutSolidSphere(0.25, 30, 30); //raio do olho 0.25
	
	// Iris (modificar depois)
    
    GLfloat mat_ambient_iris[] = {0, 0, 0};
    GLfloat mat_diffuse_iris[] = {0, 0, 0};
    GLfloat mat_specular_iris[] = {0, 0, 0};
    GLfloat mat_shine_iris = 100.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_iris);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_iris);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_iris);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine_iris);
    
    glTranslatef(0.0,-0.25, 0.0);
	glutSolidSphere(0.125f, 20, 20); //raio do olho 0.125
    
    glPopMatrix();
    
}
