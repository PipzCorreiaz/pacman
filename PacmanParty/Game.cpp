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
    
    _pac = new Pacman();
    _poc = new Pacman(-9.0f, 6.0f);
    
    _pac->setName(PACMAN);
    _poc->setName(POCMAN);
    
    _camera = new Camera(_pac);
    _maze = new Maze();
    _ghostOne = new Ghost(25,26, 1);
    _ghostTwo = new Ghost(-25,26, 2);
    _ghostThree = new Ghost(25,-12, 3);
    
    _ghosts.push_back(_ghostOne);
    _ghosts.push_back(_ghostTwo);
    _ghosts.push_back(_ghostThree);
    Wizard::getInstance().setGhosts(_ghosts);
    _light = new DayLight();
    bigBalls = 0;
    _score = 0;
    _lives = 3;
    _balls = 276;
    _detonator = false;
    present_time = 0;
    last_time = 0;

}

void Game::update() {
	float dt;
	present_time = glutGet(GLUT_ELAPSED_TIME); /* in milliseconds */
	dt = 0.001f*(present_time - last_time); /* in seconds */
    
//    if(_detonator){
//        _explosion->moveParticles(dt);
//    }
//    else {
//        movePac(_pac->getSpeed()*dt);
//    }
//    
//    moveGhost(_ghostOne, _ghostOne->getSpeed()*dt);
//    moveGhost(_ghostTwo, _ghostTwo->getSpeed()*dt);
//    moveGhost(_ghostThree, _ghostThree->getSpeed()*dt);
    
    _pac->update(dt);
    _poc->update(dt);
    _ghostOne->update(dt);
    _ghostTwo->update(dt);
    _ghostThree->update(dt);
    
	last_time = present_time;
}


void Game::ballsInspector(){ //actualiza o desenho das bolas 
    std::string map = Wizard::getInstance().getMap();
    Ball* ball = new Ball(); //evitar getBalls

	glPushMatrix();
	
	int i = 0; //i percorre matriz, j percorre balls
	int x = -27, y = 28; 
	
	glColor3f(0.7f,0.7f,0.7f); //cor bolas
	
	for (i=0; i< map.size(); i = i + 2) {
		
		if(map[i] == SMALL_BALL){
			ball->intoPlace(x, y);
            ball->growth(1.0f);
			ball->draw();
		}
		if(map[i] == BIG_BALL){
			ball->intoPlace(x, y);
			ball->growth(2.0f);
			ball->draw();
		}
		
		x = x+2;
        
		if ((i+1)%55 == 0 && i != 0) {
            i = i + 54; // ignora uma linha
			x = -27;
			y = y - 2;
		}
	}

    glPopMatrix();

    delete(ball);
}


//void Game::ghostsTrouble() {
//    _ghostOne->setTrouble(true);
//    _ghostTwo->setTrouble(true);
//    _ghostThree->setTrouble(true);
//    glutTimerFunc(10000, backToNormal, 1);
//}
//
//void backToNormal(int value) {
//	bigBalls--;
//    if(bigBalls == 0){
//        ghost1->setTrouble(false);
//        ghost2->setTrouble(false);
//        ghost3->setTrouble(false);
//    }
//}
//
//void theComeBack(int value){
//    Ghost* g = stack->front();
//    stack->erase(stack->begin());
//    g->setHidden(false);
//    g->setTrouble(false);
//    g->backAgain();
//}


std::string Game::integerToString(int num){
    std::string string = "";
    string += num / 100 + 48;
    string += (num / 10) % 10 + 48;
    string += num % 10 + 48;
    return string + '\0';
}


void Game::renderBitmapString(){ 
	glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
	
	glOrtho(-32.0f, 32.0f, -32.0f, 32.0f, -32.0f, 32.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	_score = _pac->getBalls() + _poc->getBalls();
    std::string c = "Score: ";
    c += integerToString(_score);
    int i;

    glColor3f(1.0f, 0.0f, 0.5f);//color

    glRasterPos2f(-29, 32);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    c = "Lives: ";
    c += integerToString(_lives);
    
    glRasterPos2f(22, 32);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Game::winnerRenderBitmapString(){
    glDisable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
	
	glOrtho(-32.0f, 32.0f, -32.0f, 32.0f, -32.0f, 32.0f);
	
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
	
	glOrtho(-32.0f, 32.0f, -32.0f, 32.0f, -32.0f, 32.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	
    std::string c = "E PRECISO SERES BUE INTELIGENTE PARA GANHAR";
    int i;
    
    glColor3f(1.0f, 0.0f, 0.5f);//color
    
    glRasterPos2f(-25, 5);
    for (i = 0; c[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)c[i]);
    }
    
    
    c = "DESCULPA AI";
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

//void Game::detonate(){
//    _detonator = true;
//    _pac->setExploding(true);
//    _explosion = new Explosion(_pac->getX(), _pac->getY(), _pac->getZ());
//    _lives--;
//}

//bool Game::colision(Ghost* g){
//    //ghost à direita do pacman
//    if(!g->getHidden() && !_pac->_explodingTime && g->getX() > _pac->getX() && g->getY() == _pac->getY() && g->getX()-GHOST_RADIUS <= _pac->getX()+PAC_RADIUS){
//        if(g->getTrouble()){
//            g->setHidden(true);
//            stack->push_back(g);
//            glutTimerFunc(5000, theComeBack, 0);
//            _score +=50;
//            return false;
//        }
//        else{
//            detonate();
//            return true;
//        }
//    }
//    //ghost à esquerda do pacman
//    else if(!g->getHidden() && !_pac->_explodingTime && g->getX() < _pac->getX() && g->getY() == _pac->getY() && g->getX()+GHOST_RADIUS >= _pac->getX()-PAC_RADIUS){
//
//        if(g->getTrouble()){
//            g->setHidden(true);
//            stack->push_back(g);
//            glutTimerFunc(5000, theComeBack, 0);
//            _score +=50;
//            return false;
//        }
//        else{
//            detonate();
//            return true;
//        }
//    }
//    //mesma coluna
//    else if(!g->getHidden() && !_pac->_explodingTime && g->getX() == _pac->getX()){
//        //ghost acima do pacman
//        if(!g->getHidden() && !_pac->_explodingTime && g->getY() > _pac->getY() && g->getX() == _pac->getX() && g->getY()-GHOST_RADIUS <= _pac->getY()+PAC_RADIUS){
//
//            if(g->getTrouble()){
//                g->setHidden(true);
//                stack->push_back(g);
//                glutTimerFunc(5000, theComeBack, 0);
//                _score +=50;
//                return false;
//            }
//            else{
//                detonate();
//                return true;
//            }
//        }
//        //ghost abaixo do pacman
//        else if(!g->getHidden() && !_pac->_explodingTime && g->getY() < _pac->getY() && g->getX() == _pac->getX() && g->getY()+GHOST_RADIUS >= _pac->getY()-PAC_RADIUS){
//
//            if(g->getTrouble()){
//                g->setHidden(true);
//                stack->push_back(g);
//                glutTimerFunc(5000, theComeBack, 0);
//                _score +=50;
//                return false;
//            }
//            else{
//                detonate();
//                return true;
//            }
//        }
//        else {
//        }
//    }
//    return true;
//}

void Game::draw(){
    
    glPushMatrix();
	
    if(!_balls && !_pac->getExploding()){
        winnerRenderBitmapString();
    }
    
    else if(!_lives && !_pac->getExploding()){
        loserRenderBitmapString();
    }
    
    else{
        
        //Camera
        _camera->setLookAt();
        
        //Lights
        _light->lightUs(_pac);
        
        
        _maze->draw();
        ballsInspector();
        
        
        if(_ghostOne->getTrouble()){
            _ghostOne->setColor(1, 1, 1, 0);
            _ghostOne->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostOne->setColor(0,0,1,0);
            _ghostOne->setSpeed(GHOST_NORMAL_SPEED);
        }
        if(!_ghostOne->getHidden()){
            _ghostOne->draw();
        }
        
        
        if(_ghostTwo->getTrouble()){
            _ghostTwo->setColor(1, 1, 1,0);
            _ghostTwo->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostTwo->setColor(1,0,0,0);
            _ghostTwo->setSpeed(GHOST_NORMAL_SPEED);
        }
        if(!_ghostTwo->getHidden()){
            _ghostTwo->draw();
        }
        
        
        if(_ghostThree->getTrouble()){
            _ghostThree->setColor(1, 1, 1,0);
            _ghostThree->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostThree->setColor(0, 1, 0,0);
            _ghostThree->setSpeed(GHOST_NORMAL_SPEED);
        }
        if(!_ghostThree->getHidden()){
            _ghostThree->draw();
        }
        
        _pac->draw();
        _poc->draw();
        
        renderBitmapString();
        
    }
    
    glPopMatrix();
}


