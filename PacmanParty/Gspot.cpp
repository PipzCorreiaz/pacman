//
//  Lighting.cpp
//  PacmanParty
//
//  Created by Miguel Roxo on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "Gspot.h"

Gspot::Gspot(){
}

Gspot::~Gspot(){
    
}

void Gspot::lightUs(Character *pac){
    

	GLfloat a= 60.0f; //20	
	GLfloat b = 7.0f; //0
	
    GLfloat light1_ambient[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat light1_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light1_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float direction[] = {0.0f, 0.0f, -0.5f, 0.0f};
    GLfloat light1_pos[] = {pac->getX(), pac->getY(), 2.75f, 1.0f};
    
	if(pac->_turnedUp){
        direction[1] = 1.0f;
	}
	else if(pac->_turnedDown){
        direction[1] = -1.0f;
    }
	else if(pac->_turnedLeft){
		direction[0] = -1.0f;
	}
	else if(pac->_turnedRight){
		direction[0] = 1.0f;
	}
	
	glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, a);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, b);
	
	
}


