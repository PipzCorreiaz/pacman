//
//  main.cpp
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
#include <time.h>
#include "Game.h"
#include "Constraints.h"
#include "Gspot.h"
#include "DayLight.h"
#include "BMPReader.h"

void myReshape(GLsizei w, GLsizei h) ;
void myDisplay(void) ;
void keyboard(unsigned char key, int x, int y);
void update();
void specialPressedKeys(int key, int x, int y);
void specialUpKeys(int key, int x, int y);
void setGhostsState(int state);
void LoadTexture( const std::string & textureFilename);

// "Variaveis" Globais
float present_time = 0, last_time = 0;
Game* game = new Game();

//TEXTURE STUFF

void LoadTexture( const std::string & textureFilename)
{
	BMPloader * bitmap = new BMPloader( textureFilename);
	if ( bitmap->Isvalid() )
	{
		glPixelStoref( GL_UNPACK_ALIGNMENT, 1);
		glEnable( GL_TEXTURE_2D);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->Image());
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		 
	}
	else
        std::cout << "Problems Loading Texture" << std::endl;
	delete bitmap;
}

// ENDOF TEXTURE STUFF

void myReshape(GLsizei w, GLsizei h) {
    
	glViewport(40, 40, w-80, h-80);
    
	game->_camera->setProjection(((double)w)/h);
    
}

// myDisplay : desenhar o cenario de jogo
void myDisplay(void) {
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);

    glLoadIdentity();
    
    //ACTION
    game->draw();
    
	glutSwapBuffers(); 
}


// Teclas W(up), S(down), A(left), D(right)
void keyboard(unsigned char key, int x, int y){
	if (key == 27) {
		exit(0);
	}
    if(key == 'p'){
        game->_pac->pause();
        game->_ghostOne->pause();
        game->_ghostTwo->pause();
        game->_ghostThree->pause();
    }
    if(key == 'c'){
        game->_camera->nextMode();
        game->_camera->setProjection((double)glutGet(GLUT_WINDOW_WIDTH)/glutGet(GLUT_WINDOW_HEIGHT));
    }
	if(key == '1'){
        game->_light = new DayLight();
    }
	if(key == '2'){
        game->_light = new Gspot();
    }
	if(key == 'l'){
        game->winnerRenderBitmapString();
    }
}

void specialUpKeys(int key, int x, int y){
    switch (key) {
            
        case GLUT_KEY_UP:
            game->_pac->_upPressed = false;
            break;
            
        case GLUT_KEY_DOWN:
            game->_pac->_downPressed = false;
            break;
            
        case GLUT_KEY_LEFT:
            game->_pac->_leftPressed = false;
            break;
            
        case GLUT_KEY_RIGHT:
            game->_pac->_rightPressed = false;
            break;
            
        default:
            break;
    }
}


// Teclas Setas
void specialPressedKeys(int key, int x, int y){
    switch (key) {
            
        case GLUT_KEY_UP:
            
            game->resetPressedKeys();
            game->_pac->_upPressed = true;
            
            break;
            
        case GLUT_KEY_DOWN:
            
            game->resetPressedKeys();
            game->_pac->_downPressed = true;
            
            break;
            
        case GLUT_KEY_LEFT:
            game->resetPressedKeys();               
            game->_pac->_leftPressed = true;
            
            break;
            
        case GLUT_KEY_RIGHT:
            game->resetPressedKeys();
            game->_pac->_rightPressed = true;
            
            break;
            
        default:
            break;
    }
}

// Deslocamento em funcao do tempo real mantendo uma velocidade
void update(){
    
	float dt;
	// GLUT_ELAPSED TIME: milisegundos desde que foi chamada a glutInit
	present_time = glutGet(GLUT_ELAPSED_TIME); /* in milliseconds */
	dt = 0.001f*(present_time - last_time); /* in seconds */ 

    if(game->_detonator){
        game->_explosion->moveParticles(dt);
    }
    else {
        game->movePac(game->_pac->getSpeed()*dt);
    }
    
    game->moveGhost(game->_ghostOne, game->_ghostOne->getSpeed()*dt);
    game->moveGhost(game->_ghostTwo, game->_ghostTwo->getSpeed()*dt);
    game->moveGhost(game->_ghostThree, game->_ghostThree->getSpeed()*dt);
    
	last_time = present_time;
    
	glutPostRedisplay(); //forçar o re-desenho
    
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (640, 640);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Pacman");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialPressedKeys);
	glutSpecialUpFunc(specialUpKeys);
	glutIdleFunc(update);
    
	LoadTexture("darkmetal.bmp");
    
	glutMainLoop();
    
	return 0;
}

