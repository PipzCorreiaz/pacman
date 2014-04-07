//
//  Ghost.cpp
//  BatesPoucoBates
//
//  Created by bia on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <iostream>
#include <cmath>
#include "Ghost.h"


Ghost::Ghost(int posx, int posy, int id){
	_eye = new Eye();
	_posX = posx;
    _posY = posy; 
    _posZ = _direction = _pauseAngle = 0;
	_up = _down = _left = _right = false; //inicia parado
    _left = true;
    _speed = GHOST_NORMAL_SPEED; // unidades do labirinto per second
    _trouble = false; //if true vou ser comido :D
    _ghostId = id;
    _hiddenTime = false;
}

Ghost::~Ghost(){}


bool Ghost::isGhost(){
    return true;
}


void Ghost::backAgain(){
    _posX = 0.0f;
	_posY = 0.0f;
}

void Ghost::setDirection(float posX, float posY){
    float vecX = posX - _posX;
    float vecY = posY - _posY;
    _direction = atan2(vecX, -vecY) * 180.0f / 3.14f;
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

void Ghost::setSpeed(float speed){
    _speed = speed;
}

void Ghost::setTrouble(bool trouble){
    _trouble = trouble;
}

void Ghost::draw() {
    
    glPushMatrix();
    
    
    glTranslatef(getX(),getY(), getZ()); // colocar ghost na pos (x,y,z)

	glRotatef(getDirection(), 0, 0, 1); // direccao do ghost

   // glRotatef(getPauseAngle(), 1, 0, 0);
    
	
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

void Ghost::move(float dist){
    
    if(_up){
        _posY = _posY + dist;
        _direction = 180;
        _pauseAngle = 0;
    }
    
    else if(_down){
        _posY = _posY - dist;
        _direction = 0;
        _pauseAngle = 0;
    }
    
    else if(_left){
        _posX = _posX - dist;
        _direction = -90;
        _pauseAngle = 0;
    }
    else if(_right){
        _posX = _posX + dist;
        _direction = 90;
        _pauseAngle = 0;
    }
    
    return;
}

