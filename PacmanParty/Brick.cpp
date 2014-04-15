#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Constraints.h"
#include "Brick.h"


Brick::Brick() {
    _width = 1;
    _height = 1;
    _posX = 0;
    _posY = 0;
}

Brick::~Brick(){
    
}



void Brick::resize(float width, float height){
    
    _width = width;
    _height = height;
    
}


void Brick::intoPlace(float posx, float posy, float posz){
    
    _posX = posx;
    _posY = posy;
    _posZ = posz; //vai ser a constante WALL_HOWBIG
    
}



void Brick::draw(){
    
    glPushMatrix();
    
    glTranslatef(0.5f, 0.5f, 0.5f); // colocar o tijolo pelo canto inferior esquerdo
	glTranslatef(_posX, _posY, _posZ); // 1 pq se a parede nao sobe prefura o chao
    
    glutSolidCube(1);
	
	
	glPopMatrix();
}
