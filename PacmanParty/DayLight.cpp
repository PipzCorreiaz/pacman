//
//  Lighting.cpp
//  PacmanParty
//
//  Created by Miguel Roxo on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "DayLight.h"

DayLight::DayLight(){
    
}

DayLight::~DayLight(){
    
}

void DayLight::lightUs(Character *pac){
    
    // LIGHT 0
    
    GLfloat light0_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    GLfloat light0_pos[] = {3.0f, 5.0f, 5.0f, 0.0f};
    
	glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}


