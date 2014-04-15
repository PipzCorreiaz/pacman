#if defined (__APPLE__) || defined (MACOSX)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <iostream>
#include "MinerHat.h"

MinerHat::MinerHat(){
	_posX = _posY = _posZ = 0;
	}

MinerHat::~MinerHat(){}

void MinerHat::intoPlace(float posX, float posY, float posZ){
    _posX = posX;
    _posY = posY;
    _posZ = posZ;
}


void MinerHat::drawFace(float angle){
	
	glPushMatrix();
	
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-0.525f, 0.91f, 0.5f);
	glVertex3f(-0.525f, 0.91f, 0.0f);
	
	glNormal3f(-0.404f, 0.7f, 1.0f);
	glVertex3f(-0.404f, 0.7f, 0.5f);
	
	glNormal3f(0.404f, 0.7f, 1.0f);
	glVertex3f(0.404f, 0.7f, 0.5f);
	
	glNormal3f(0.525f, 0.91f, 0.5f);
	glVertex3f(0.525f, 0.91f, 0.0f);
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-0.404f, 0.7f, 1.0f);
	glVertex3f(-0.404f, 0.7f, 0.5f);
	
	glNormal3f(-0.231f, 0.4f, 1.5f);
	glVertex3f(-0.231f, 0.4f, 0.75f);
	
	glNormal3f(0.231f, 0.4f, 1.5f);
	glVertex3f(0.231f, 0.4f, 0.75f);
	
	glNormal3f(0.404f, 0.7f, 1.0f);
	glVertex3f(0.404f, 0.7f, 0.5f);
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(-0.231f, 0.4f, 1.5f);
	glVertex3f(-0.231f, 0.4f, 0.75f);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.75f);
	
	glNormal3f(0.231f, 0.4f, 1.5f);
	glVertex3f(0.231f, 0.4f, 0.75f);
	glEnd();
	
	glPopMatrix();	
	
}

void MinerHat::draw(){
    
    glPushMatrix();
        
    GLfloat mat_ambient_hat[] = {1.6f, 0.0f, 0.0f};
    GLfloat mat_diffuse_hat[] = {1.0f, 0.0f, 0.0f};
    GLfloat mat_specular_hat[] = {1.0f, 0.0f, 0.0f};
    GLfloat mat_shine_hat = 1.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_hat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_hat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_hat);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine_hat);
    
    glTranslatef(_posX,_posY, _posZ);
	
	// <cap>
	drawFace(0);
	drawFace(60);
	drawFace(120);
	drawFace(180);
	drawFace(240);
	drawFace(300);
	drawFace(360);
	// </cap>
	
	//pala do chapeu
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.525f, -0.91f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.4f, -1.11f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.4f, -1.11f, 0.0f);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.525f, -0.91f, 0.0f);
	glEnd();
	
	
	
	// <teara>
	//glutSolidTorus(0.2f, 0.7f, 10, 20);
	// </teara>
	
	// <lanterna> 
	glTranslatef(0.0f, -1.0f, 0.5f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.25f, 0.5f, 30, 30);
    
    if(glIsEnabled(GL_LIGHT0)){
    
	GLfloat mat_ambient_bulb[] = {0.1f, 0.1f, 0.1f};
	GLfloat mat_diffuse_bulb[] = {0.1f, 0.1f, 0.1f};
	GLfloat mat_specular_bulb[] = {0.1f, 0.1f, 0.1f};
   // GLfloat mat_emissive_bulb[] = {0.5f, 0.5f, 0.5f};
    
	GLfloat mat_shine_bulb = 200.0f;
	 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_bulb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_bulb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_bulb);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shine_bulb);
  //  glMaterialfv(GL_FRONT,GL_EMISSION, mat_emissive_bulb);
     
    glutSolidSphere(0.2f, 5, 5);
    
    } else {
            
        glDisable(GL_LIGHTING);
        //glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        glutSolidSphere(0.2f, 5, 5);
        
        glEnable(GL_LIGHTING);
        //glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

    }

    // </lanterna>
	
    glPopMatrix();
    
}
