//
//  Ball.cpp
//  PacmanLove
//
//  Created by bia on 3/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Ball.h"

Ball::Ball(){
    _posX = 0;
    _posY = 0;
    _posZ = 0.5f;
    _scale = 1;
}

void Ball::draw(){
    
    glPushMatrix();
    
    //glColor3f(1, 1, 0); // Amarelo
    GLfloat mat_ambient[] = {1, 1, 1};
    GLfloat mat_diffuse[] = {0.4, 0.4, 0.4};
    GLfloat mat_specular[] = {0.77, 0.77, 0.77};
    GLfloat mat_shine = 200.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shine);
    
    glTranslatef(_posX, _posY, _posZ);
    glScalef(_scale, _scale, _scale);
    glutSolidSphere(0.25, 30, 30);
    
    glPopMatrix();
}

void Ball::intoPlace(float posX, float posY){
    _posX = posX;
    _posY = posY;
}

void Ball::growth(float scale){
	_scale  = scale;
}

