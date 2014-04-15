#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Wall.h"


Wall::Wall() {
    _width = 0;
    _height = 0;
    _posX = 0;
    _posY = 0;
    _brick = new Brick();
}

Wall::~Wall(){
    
}

// define os limites da parede
void Wall::resize(float width, float height){
    
    _width = width;
    _height = height;
    
}


void Wall::intoPlace(float posx, float posy, float posz){
    
    _posX = posx;
    _posY = posy;
    _posZ = posz;
    
}

void Wall::draw(){
    
    glPushMatrix();
  
    int i, j, k;
    
    
    glTranslatef(-_width/2, -_height/2, 0); //centrar referencia da parede
    glTranslatef(_posX, _posY, _posZ);
    
    for (k = 0; k < WALL_HOWBIG; k++){
    
        for (j = 0; j < _height; j++) {
            
            for (i = 0; i < _width; i++) {
                
                _brick->intoPlace(i , j, k);
                _brick->draw();
                
            }
        }
    }
	glPopMatrix();
}






















