#include "Game.h"


static std::vector<Ghost*>* stack = new std::vector<Ghost*>();
static int bigBalls;




Game::Game(){
	try{
		Wizard::getInstance().loadMap("map.txt");
	}
	catch(std::string* e) {
		std::cerr << *e << std::endl;
		exit(-1);
	}
    
    float yellow[3] = {1.0f, 1.0f, 0.0f};
    float blue[3] = {0.0f, 0.0f, 1.0f};
    float red[3] = {1.0f, 0.0f, 0.0f};
    float green[3] = {0.0f, 1.0f, 0.0f};
    float pink[3] = {1.0f, 0.4f, 0.8f};
    float lightBlue[3] = {0.4f, 0.6f, 1.0f};
    
    _pac = new Pacman(9.0f, 6.0f, yellow, pink);
    _poc = new Pacman(-9.0f, 6.0f, yellow, lightBlue);
    
    _pac->setName(PACMAN);
    _poc->setName(POCMAN);
    
    _pacmen.push_back(_pac);
    _pacmen.push_back(_poc);
    
    Wizard::getInstance().setPacmen(_pacmen);
    
    _camera = new Camera(_pac);
    _maze = new Maze();
    _ghostOne = new Ghost(25,26, 1, blue);
    _ghostTwo = new Ghost(-25,26, 2, red);
    _ghostThree = new Ghost(25,-12, 3, green);
    
    _ghosts.push_back(_ghostOne);
    _ghosts.push_back(_ghostTwo);
    _ghosts.push_back(_ghostThree);
    Wizard::getInstance().setGhosts(_ghosts);
    
    _ghostHUD = new Ghost();
    _pacmanHUD = new Pacman();
    _light = new DayLight();
    bigBalls = 0;
    _score = 0;
    _balls = 276;
    _detonator = false;
    present_time = 0;
    last_time = 0;
    
    _done = false;

}

void Game::update() {
	float dt;
	present_time = glutGet(GLUT_ELAPSED_TIME); /* in milliseconds */
	dt = 0.001f*(present_time - last_time); /* in seconds */
    
    _pac->update(dt);
    _poc->update(dt);
    _ghostOne->update(dt);
    _ghostTwo->update(dt);
    _ghostThree->update(dt);
    
	last_time = present_time;
}


void Game::mapItemsDrawer(){ //actualiza o desenho das bolas
    std::string map = Wizard::getInstance().getMap();
    Ball* ball = new Ball(); //evitar getBalls
    Ammunition* ammunition = new Ammunition();
    
    int balls = _balls;
    
	glPushMatrix();
	
	int i = 0; //i percorre matriz, j percorre balls
	int x = -27, y = 28; 
	
	glColor3f(0.7f,0.7f,0.7f); //cor bolas
	
	for (i=0; i< map.size(); i = i + 2) {
		
		if(map[i] == SMALL_BALL){
			ball->intoPlace(x, y);
            ball->growth(1.0f);
			ball->draw();
            balls--;
		} else if(map[i] == BIG_BALL){
			ball->intoPlace(x, y);
			ball->growth(2.0f);
			ball->draw();
            balls--;
		} else if (map[i] == AMMUNITION) {
            ammunition->intoPlace(x, y);
            ammunition->draw();
        }
		
		x = x+2;
        
		if ((i+1)%55 == 0 && i != 0) {
            i = i + 54; // ignora uma linha
			x = -27;
			y = y - 2;
		}
	}
    
    if ((_balls - balls) == 0) {
        _done = true;
    }

    glPopMatrix();

    delete(ball);
}

std::string Game::integerToString(int num){
    std::string string = "";
    string += num / 100 + 48;
    string += (num / 10) % 10 + 48;
    string += num % 10 + 48;
    return string + '\0';
}

void Game::setScore() {
    int catchedGhosts = _pac->getGhostCatched() + _poc->getGhostCatched();
    _score = _pac->getBalls() + _poc->getBalls() + (catchedGhosts*30);
}


void Game::drawHUD() {
	glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
	
    glOrtho(-35.0f, 35.0f, -35.0f, 35.0f, -35.0f, 35.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	setScore();

    std::string c = "Score: ";
    c += integerToString(_score);

    int i;

    glColor3f(0.0f, 0.0f, 0.0f);

    glRasterPos2f(-30, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = integerToString(_ghostOne->getLife());
    glRasterPos2f(-12, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = integerToString(_ghostTwo->getLife());
    glRasterPos2f(-2, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = integerToString(_ghostThree->getLife());
    glRasterPos2f(8, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = integerToString(_pac->getAmmunitions());
    glRasterPos2f(18, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = integerToString(_poc->getAmmunitions());
    glRasterPos2f(28, 33);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    glEnable(GL_LIGHTING);
    
    _ghostHUD->setX(-15.0f);
    _ghostHUD->setY(32.0f);
    _ghostHUD->setColor(_ghostOne->getColor());
    _ghostHUD->draw();
    
    _ghostHUD->setX(-5.0f);
    _ghostHUD->setY(32.0f);
    _ghostHUD->setColor(_ghostTwo->getColor());
    _ghostHUD->draw();
    
    _ghostHUD->setX(5.0f);
    _ghostHUD->setY(32.0f);
    _ghostHUD->setColor(_ghostThree->getColor());
    _ghostHUD->draw();
    
    _pacmanHUD->setX(15.0f);
    _pacmanHUD->setY(33.5f);
    _pacmanHUD->setColor(_pac->getColor());
    _pacmanHUD->setScarfColor(_pac->getScarfColor());
    _pacmanHUD->draw();
    
    _pacmanHUD->setX(25.0f);
    _pacmanHUD->setY(33.5f);
    _pacmanHUD->setColor(_poc->getColor());
    _pacmanHUD->setScarfColor(_poc->getScarfColor());
    _pacmanHUD->draw();

	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Game::winnerRenderBitmapString(){
    glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
	
    glOrtho(-35.0f, 35.0f, -35.0f, 35.0f, -35.0f, 35.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	
    std::string c = "GANHASTE, SORTE DE PRINCIPIANTE";
    int i;
    
    glColor3f(1.0f, 0.0f, 0.5f);//color
    
    glRasterPos2f(-15, 10);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = "So ";
    c += integerToString(_score);
    c += " pontos???";
    
    glRasterPos2f(-15, -10);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Game::loserRenderBitmapString(){
    glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
	
	glOrtho(-35.0f, 35.0f, -35.0f, 35.0f, -35.0f, 35.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	
    std::string c = "YOUR PACMEN ARE NOT CLEVER ENOUGH";
    int i;
    
    glColor3f(1.0f, 0.0f, 0.5f);//color
    
    glRasterPos2f(-25, 5);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    
    c = "YOU LOSE";
    glRasterPos2f(-8, -5);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Game::draw(){
    
    glPushMatrix();

    
    if (_done) {
        winnerRenderBitmapString();
    } else if (_pac->getSick() && _poc->getSick()) {
        loserRenderBitmapString();
    } else {
    

        _camera->setLookAt();
        _light->lightUs(_pac);
        
        
        _maze->draw();
        mapItemsDrawer();

        drawHUD();
        
        _pac->draw();
        _poc->draw();
        
        _ghostOne->draw();
        _ghostTwo->draw();
        _ghostThree->draw();
        
        
    }
    
    glPopMatrix();
}


