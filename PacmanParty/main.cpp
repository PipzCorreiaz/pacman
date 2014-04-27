#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <iostream>
#include "Game.h"
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


//Variaveis Globais
Game* game = new Game();



void LoadTexture( const std::string & textureFilename) {
	BMPloader * bitmap = new BMPloader(textureFilename);
	if (bitmap->Isvalid()) {
		glPixelStoref( GL_UNPACK_ALIGNMENT, 1);
		glEnable( GL_TEXTURE_2D);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, bitmap->Width(), bitmap->Heigth(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->Image());
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		 
	} else {
        std::cout << "Problems Loading Texture" << std::endl;
    }
    
	delete bitmap;
}


void myReshape(GLsizei w, GLsizei h) {
    
	glViewport(40, 40, w - 80, h - 80);
	game->_camera->setProjection(((double) w) / h);
    
}

void myDisplay(void) {
    
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glLoadIdentity();
    game->draw();
    
	glutSwapBuffers(); 
}


void keyboard(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
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
}


void update() {
    game->update();
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	
	srand((unsigned int)time(NULL));
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (640, 640);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Pacman");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
    
	LoadTexture("darkmetal.bmp");
    
	glutMainLoop();
    
	return 0;
}

