//
//  Game.cpp
//  PacmanParty
//
//  Created by bia on 3/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "Game.h"

static Ghost* ghost1;
static Ghost* ghost2;
static Ghost* ghost3;
static std::vector<Ghost*>* stack = new std::vector<Ghost*>();
static int bigBalls;

void backToNormal(int value){
	bigBalls--;
    if(bigBalls == 0){
        ghost1->setTrouble(false);
        ghost2->setTrouble(false);
        ghost3->setTrouble(false);
    }
}

void theComeBack(int value){
    Ghost* g = stack->front();
    stack->erase(stack->begin());
    g->_hiddenTime = false;
    g->_trouble = false;
    g->backAgain();
}


Game::Game(){
	
	try{
		matrix = Wizard::getInstance().loadMap("map.txt");
	}
	catch(std::string* e) {
		std::cerr << *e << std::endl;
		exit(-1);
	}
    _pac = new Pacman();
    _camera = new Camera(_pac);
    _maze = new Maze();
    _ghostOne = new Ghost(25,26, 1);
    _ghostTwo = new Ghost(-25,26, 2);
    _ghostThree = new Ghost(25,-26, 3);
    _light = new DayLight();
    ghost1 = _ghostOne;
    ghost2 = _ghostTwo;
    ghost3 = _ghostThree;
    bigBalls = 0;
    _score = 0;
    _lives = 3;
    _balls = 276;
    _detonator = false;
    present_time = 0;
    last_time = 0;

}

Game::~Game(){}

void Game::resetPressedKeys(){
    _pac->_upPressed = _pac->_downPressed = _pac->_leftPressed = _pac->_rightPressed = false;

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
    _ghostOne->update(dt);
    _ghostTwo->update(dt);
    _ghostThree->update(dt);
    
	last_time = present_time;
}


void Game::ballsInspector(){ //actualiza o desenho das bolas 
    Ball* balls[_balls]; //evitar getBalls
    int f;
    
    for(f = 0; f < _balls; f++){
        balls[f] = new Ball();
    }
    
	glPushMatrix();
	
	int i, j = 0; //i percorre matriz, j percorre balls
	int x = -27, y = 28; 
	
	glColor3f(0.7f,0.7f,0.7f); //cor bolas
	
	
	for (i=0; i< matrix.size(); i = i + 2) {
		
		if(matrix[i] == 'b'){
			balls[j]->intoPlace(x, y);
			balls[j]->draw();
			j++;
		}
		if(matrix[i] == 'B'){
			balls[j]->intoPlace(x, y);
			balls[j]->growth(2.0f);
			balls[j]->draw();
			j++;
		}
		
		x = x+2;
        
		
		if ((i+1)%55 == 0 && i != 0) {
            i = i + 54; // ignora uma linha
			x = -27;
			y = y - 2;
		}
	}
	
	glPopMatrix();
}


int Game::matrixPosition(int x, int y){
    int position = (28 - y) * 55; //linhas completas
    position += (28 + x);
    return position - 1;
}
////////////// PACMAN QUER ANDAR: PODE? ///////////////


///POSSO ANDAR? CIMA ///

int Game::upCheck(Character* car,float dist){
    int i, posX = (int)car->getX();
    
    if(car->isLeft()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)(car->getX() - dist), (int) car->getY()); i--, posX--){
            //    printf("%c\t",matrix[i-2]);
                if((car->getX() - dist) <  posX && posX < car->getX()  && (matrix[i-110] == '.' || matrix[i-110] == 'b')){
                    return posX;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else if(car->isRight()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)(car->getX() + dist), (int) car->getY()); i++, posX++){
                if((car->getX() + dist) >  posX && posX > car->getX()  && (matrix[i-110] == '.' || matrix[i-110] == 'b')){
                    return posX;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else{
        return 666;

    }
}



/// POSSO ANDAR? BAIXO ///

int Game::downCheck(Character* car,float dist){
    int i, posX = (int)car->getX();
    
    if(car->isLeft()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)(car->getX() - dist), (int) car->getY()); i--, posX--){
                if((car->getX() - dist) <  posX && posX < car->getX()  && (matrix[i+110] == '.' || matrix[i+110] == 'b')){
                    return posX;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else if(car->isRight()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)(car->getX() + dist), (int) car->getY()); i++, posX++){
                if((car->getX() + dist) >  posX && posX > car->getX()  && (matrix[i+110] == '.' || matrix[i+110] == 'b')){
                    return posX;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else{
        return 666;

    }
}



/// POSSO ANDAR? ESQUERDA ///

int Game::leftCheck(Character* car,float dist){
    int i, posY = (int)car->getY();
    
    if(car->isUp()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)car->getX(), (int)(car->getY() + dist)); i = i - 55, posY++){
                if((car->getY() + dist) >  posY && posY > car->getY() && (matrix[i-2] == '.' || matrix[i-2] == 'b')){
                    return posY;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else if(car->isDown()){
       if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)car->getX(), (int)(car->getY() - dist)); i = i + 55, posY--){
                if((car->getY() - dist) <  posY && posY < car->getY()  && (matrix[i-2] == '.' || matrix[i-2] == 'b')){
                    return posY;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else{
        return 666;
    }
}


/// POSSO ANDAR? DIREITA ///

int Game::rightCheck(Character* car,float dist){
    int i, posY = (int)car->getY();
    
    if(car->isUp()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)car->getX(), (int)(car->getY() + dist)); i = i - 55, posY++){
                if((car->getY() + dist) >  posY && posY > car->getY()  && (matrix[i+2] == '.' || matrix[i+2] == 'b')){
                    return posY;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else if(car->isDown()){
        if(check(car, dist)){
            for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)car->getX(), (int)(car->getY() - dist)); i = i + 55, posY--){
                if((car->getY() - dist) <  posY && posY < car->getY()  && (matrix[i+2] == '.' || matrix[i+2] == 'b')){
                    return posY;
                }
            }
        }
        return 666; //numero absurdo caso nao possa virar
    }
    else{
        return 666;
    }
}
// POSSO ANDAR? mesma direccao em que estou //

int Game::check(Character* car, float dist){
    
    if(car->isUp()){

        int i, posY = (int)car->getY();
        for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)car->getX(), (int)(car->getY() + dist)); i = i - 55, posY++){
            if((car->getY() + dist) > posY && (matrix[i-110] == 'w')){
                car->setY(posY);
                car->resetMove();
                return 0;
            }
        }
        return 1;
    }
    else if(car->isDown()){  
        int i, posY = (int)car->getY();
        for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)car->getX(), (int)(car->getY() - dist)); i = i + 55, posY--){
            if((car->getY() - dist) < posY && (matrix[i+110] == 'w')){
                
                car->setY(posY);
                car->resetMove();
                return 0;
            }
        }
        return 1;
    }
    else if(car->isLeft()){
        int i, posX = (int)car->getX();
        for(i = matrixPosition((int)car->getX(),(int)car->getY()); i >= matrixPosition((int)(car->getX()-dist), (int)(car->getY())); i = i -1, posX--){
            if(posX == -29){
                car->setX(29);
                return 1;
            }
            if((car->getX() - dist) <  posX && (matrix[i-2] == 'w')){
                car->setX(posX);
                car->resetMove();
                return 0;
            }
        }
        return 1;
    }
    else if(car->isRight()){
        int i, posX = (int)car->getX();
        for(i = matrixPosition((int)car->getX(),(int)car->getY()); i <= matrixPosition((int)(car->getX()+dist), (int)(car->getY())); i = i+1, posX++){
            if(posX == 29){
                car->setX(-29);
                return 1;
            }
            if((car->getX() + dist) >  posX && (matrix[i+2] == 'w')){
                car->setX(posX);
                car->resetMove();
                return 0;
            }
        }
        return 1;
    }
    else {
        return 0;
    }
}


int Game::chaseDirection(Ghost* g){
    float vec_x = _pac->getX() - g->getX();
    float vec_y = _pac->getY() - g->getY();
    
    if(abs(vec_x) >= abs(vec_y)){
        if(vec_x > 0){
            return 3;
        }
        else {
            return 2;
        }
    }
    else if(abs(vec_x) < abs(vec_y)){
        if(vec_y > 0){
            return 0;   
        }
        else {
            return 1;
        }
    }
    return -1;
}

int Game::runAwayDirection(Ghost* g){
    float vec_x = _pac->getX() - g->getX();
    float vec_y = _pac->getY() - g->getY();
    
    if(abs(vec_x) >= abs(vec_y)){
        if(vec_x > 0){
            return 3;
        }
        else {
            return 2; 
        }
    }
    else if(abs(vec_x) < abs(vec_y)){
        if(vec_y > 0){
            return 0; 
        }
        else {
            return 1;
        }
    }
    return -1;
}

void Game::getOut(Character* g){
    if(g->_upPressed){
        g->up();
    }
    else if(g->_downPressed){
        g->down();
    }
    else if(g->_leftPressed){
        g->left();
    }
    else if(g->_rightPressed){
        g->right();
    }
}

void Game::ghostsTrouble(){
    _ghostOne->setTrouble(true);
    _ghostTwo->setTrouble(true);
    _ghostThree->setTrouble(true);
}

void Game::moveGhost(Ghost * ghost, float dist){
    
    //srand(glutGet(GLUT_ELAPSED_TIME)+ghost->_ghostId*time(NULL));
    
    if(ghost->isStopped()){
        int i = rand()%4;
        switch(i){
            case 0:
                ghost->up();
                break;
            case 1:
                ghost->down();
                break;
            case 2:
                ghost->left();
                break;
            case 3:
                ghost->right();
                break;
        }
        return;
    }
    
    int rightY = rightCheck(ghost, dist);
    int leftY = leftCheck(ghost, dist);
    int upX = upCheck(ghost, dist);
    int downX = downCheck(ghost, dist);
    
    bool lucky = rand()%4 != 0;
    
   // if(ghost->_trouble) lucky = !lucky; //A troubled ghost is an unlucky one
    
    bool options[] = {false, false, false, false};
    
    int pacDirection[2]; // 2 options always
    
    float vec_x = _pac->getX() - ghost->getX();
    float vec_y = _pac->getY() - ghost->getY();
    
    // Check PacMan Direction possibilites
    if(vec_x == 0){
        if(vec_y >= 0){
            if(ghost->_trouble)
                pacDirection[0] = 1;
            else
                pacDirection[0] = 0;
        }
        else {
            if(ghost->_trouble)
                pacDirection[0] = 0;
            else pacDirection[0] = 1;
        }
        if(rand()%2==0)
            pacDirection[1] = 1;
        else pacDirection[1] = 0;
    } 
    else if(vec_y == 0){
        if(vec_x >= 0){
            if(ghost->_trouble)
                pacDirection[0] = 2;
            else pacDirection[0] = 3;
        }
        else {
            if(ghost->_trouble)
                pacDirection[0] = 3;
            else pacDirection[0] = 2;
        }
        if(rand()%2==0)
            pacDirection[1] = 0;
        else pacDirection[1] = 1; 
    } 
    else if(abs(vec_x) >= abs(vec_y)){
        if(vec_x >= 0){
            if(ghost->_trouble)
                pacDirection[0] = 2;
            else pacDirection[0] = 3;
        }
        else {
            if(ghost->_trouble)
                pacDirection[0] = 3;
            else pacDirection[0] = 2;
        }
        if(vec_y >= 0){
            if(ghost->_trouble)
                pacDirection[1] = 1;
            else pacDirection[1] = 0;
        }
        else {
            if(ghost->_trouble)
                pacDirection[1] = 0;
            else pacDirection[1] = 1;
        }
    }
    else if(abs(vec_x) < abs(vec_y)){
        if(vec_y >= 0){
            if(ghost->_trouble)
                pacDirection[0] = 1;
            else pacDirection[0] = 0;
        }
        else {
            if(ghost->_trouble)
                pacDirection[0] = 0;
            else pacDirection[0] = 1;
        }
        if(vec_x >= 0){
            if(ghost->_trouble)
                pacDirection[1] = 2;
            else pacDirection[1] = 3;
        }
        else {
            if(ghost->_trouble)
                pacDirection[1] = 3;
            else pacDirection[1] = 2;
        }
    }
    
    
    if(ghost->isUp()){ // GOING UP
        
        if(check(ghost,dist)){
            options[0] = true; //Se ainda pode andar para cima mantém
        } else {
            options[1] = true;
        }
        
        options[2] = leftY != 666;
        options[3] = rightY != 666;
        
        if(lucky){ // VAMOS TENTAR IR ATRÁS DO PACMAN
            
            int dir;
            if(options[pacDirection[0]]){
                dir = pacDirection[0];
            } else if(options[pacDirection[1]]){
                dir = pacDirection[1];
            } else {
                dir = 4; //Does nos exist!
            }

            switch(dir){
                case 0:
                    ghost->move(dist);
                    return;
                    break;
                case 1:
                    ghost->down();
                    ghost->move(dist);
                    return;
                    break;
                case 2:
                    ghost->left();
                    ghost->setY(leftY);
                    return;
                    break;
                case 3:
                    ghost->right();
                    ghost->setY(rightY);
                    return;
                    break;
            } //Se não encontrar nenhum vai ao calhas!
        }
        
        // Direcção ao calhass
            
        int i = rand()%4; // Some randomness
        while(options[i] != true){
            i = (i+1)%4;
        }
        switch(i){
            case 0:
                ghost->move(dist);
                break;
            case 1:
                ghost->down();
                ghost->move(dist);
                break;
            case 2:
                ghost->left();
                ghost->setY(leftY);
                break;
            case 3:
                ghost->right();
                ghost->setY(rightY);
                break;
        }
        
        //Ver sorte do gajo, ver se pode virar, virá-lo
        
    } else if(ghost->isDown()){ // GOING DOWN
        
        if(check(ghost,dist)){
            options[1] = true; //Se ainda pode andar para baixo mantém
        } else {
            options[0] = true;
        }
        options[2] = leftY != 666;
        options[3] = rightY != 666;
        
        if(lucky){ // VAMOS TENTAR IR ATRÁS DO PACMAN
            
            int dir;
            if(options[pacDirection[0]]){
                dir = pacDirection[0];
            } else if(options[pacDirection[1]]){
                dir = pacDirection[1];
            } else {
                dir = 4; //Does nos exist!
            }
            
            switch(dir){
                case 0:
                    ghost->up();
                    ghost->move(dist);
                    return;
                    break;
                case 1:
                    ghost->move(dist);
                    return;
                    break;
                case 2:
                    ghost->left();
                    ghost->setY(leftY);
                    return;
                    break;
                case 3:
                    ghost->right();
                    ghost->setY(rightY);
                    return;
                    break;
            } //Se não encontrar nenhum vai ao calhas!
        }

        
        // Direcção ao calhass
            
        int i = rand()%4; // Some randomness
        while(options[i] != true){
            i = (i+1)%4;
        }
        switch(i){
            case 0:
                ghost->up();
                ghost->move(dist);
                break;
            case 1:
                ghost->move(dist);
                break;
            case 2:
                ghost->left();
                ghost->setY(leftY);
                break;
            case 3:
                ghost->right();
                ghost->setY(rightY);
                break;
        }
        
    } else if(ghost->isLeft()){ // GOING LEFT
        
        if(check(ghost,dist)){
            options[2] = true; //Se ainda pode andar para esqueda mantém
        } else {
            options[3] = true;
        }
        options[0] = upX != 666;
        options[1] = downX != 666;
        
        if(lucky){ // VAMOS TENTAR IR ATRÁS DO PACMAN
            
            int dir;
            if(options[pacDirection[0]]){
                dir = pacDirection[0];
            } else if(options[pacDirection[1]]){
                dir = pacDirection[1];
            } else {
                dir = 4; //Does nos exist!
            }
            
            switch(dir){
                case 0:
                    ghost->up();
                    ghost->setX(upX);
                    return;
                    break;
                case 1:
                    ghost->down();
                    ghost->setX(downX);
                    return;
                    break;
                case 2:
                    ghost->move(dist);
                    return;
                    break;
                case 3:
                    ghost->right();
                    ghost->move(dist);
                    return;
                    break;
            } //Se não encontrar nenhum vai ao calhas!
        }

        
        // Direcção ao calhass
            
        int i = rand()%4; // Some randomness
        while(options[i] != true){
            i = (i+1)%4;
        }
        switch(i){
            case 0:
                ghost->up();
                ghost->setX(upX);
                break;
            case 1:
                ghost->down();
                ghost->setX(downX);
                break;
            case 2:
                ghost->move(dist);
                break;
            case 3:
                ghost->right();
                ghost->move(dist);
                break;
        }
        
    } else if(ghost->isRight()){ // GOING RIGHT
        
        if(check(ghost,dist)){
            options[3] = true; //Se ainda pode andar para a direita mantém
        } else {
            options[2] = true;
        }
        options[0] = upX != 666;
        options[1] = downX != 666;
        
        if(lucky){ // VAMOS TENTAR IR ATRÁS DO PACMAN
            
            int dir;
            if(options[pacDirection[0]]){
                dir = pacDirection[0];
            } else if(options[pacDirection[1]]){
                dir = pacDirection[1];
            } else {
                dir = 4; //Does nos exist!
            }
            
            switch(dir){
                case 0:
                    ghost->up();
                    ghost->setX(upX);
                    return;
                    break;
                case 1:
                    ghost->down();
                    ghost->setX(downX);
                    return;
                    break;
                case 2:
                    ghost->left();
                    ghost->move(dist);
                    return;
                    break;
                case 3:
                    ghost->move(dist);
                    return;
                    break;
            } //Se não encontrar nenhum vai ao calhas!
        }
        
        // Direcção ao calhass

        int i = rand()%4; // Some randomness
        while(options[i] != true){
            i = (i+1)%4;
        }
        switch(i){
            case 0:
                ghost->up();
                ghost->setX(upX);
                break;
            case 1:
                ghost->down();
                ghost->setX(downX);
                break;
            case 2:
                ghost->left();
                ghost->move(dist);
                break;
            case 3:
                ghost->move(dist);
                break;
        }
    }
    else ghost->move(dist);
    
}


void Game::movePac(float dist){
    
    if(_pac->isStopped()){ //no caso do pac estar parado
        _pac->setUp(_pac->_upPressed);
        _pac->setDown(_pac->_downPressed);
        _pac->setLeft(_pac->_leftPressed);
        _pac->setRight(_pac->_rightPressed);
    }
    else{ //ja esta em andamentoooo
        
        if(_pac->_upPressed && !_pac->isUp()){
            if(_pac->isDown()){
                _pac->up();
                if(check(_pac, dist)){
                    _pac->move(dist);
                }
            }
            else{
                int x = upCheck(_pac,dist);
                if(x != 666){
                    _pac->up();
                    _pac->setX(x);
                }
                _pac->move(dist);
            }
        }
        else if(_pac->_downPressed && !_pac->isDown()){
            if(_pac->isUp()){
                _pac->down();
                if(check(_pac, dist))
                    _pac->move(dist);
            }
            else{
                int x = downCheck(_pac,dist);
                if(x != 666){
                    _pac->down();
                    _pac->setX(x);
                }
                _pac->move(dist);
            }
        }
        else if(_pac->_leftPressed && !_pac->isLeft()){
            if(_pac->isRight()){
                _pac->left();
                if(check(_pac, dist))
                    _pac->move(dist);
            }
            else{
                int y = leftCheck(_pac,dist);
                if(y != 666){
                    _pac->left();
                    _pac->setY(y);
                }
                _pac->move(dist);
            }
        }
        else if(_pac->_rightPressed && !_pac->isRight()){
            if(_pac->isLeft()){
                _pac->right();
                if(check(_pac, dist))
                    _pac->move(dist);
            }
            else{
                int y = rightCheck(_pac,dist);
                if(y != 666){
                    _pac->right();
                    _pac->setY(y);
                }
                _pac->move(dist);
            }
        }
        else {
            if(check(_pac, dist)){
                _pac->move(dist);
            }
        }
    }
    
    ballsEater();
    
    
}


// PROFESSOR = contemplar mais que uma bola de cada vez?
void Game::ballsEater(){
    int index = matrixPosition((int)_pac->getX(), (int)_pac->getY());
    if(_pac->isUp()){
        if(matrix[index] == 'b'){
            matrix[index] = '.';
            _balls--;
            _score += 1;
        }
        else if(matrix[index] == 'B') {
            matrix[index] = '.';
            _balls--;
            _score += 5;
            ghostsTrouble();
            bigBalls++;
            glutTimerFunc(10000, backToNormal, 1);
        }
    }
    if(_pac->isDown()){
        if(matrix[index] == 'b'){
            matrix[index] = '.';
            _balls--;
            _score += 1;
        }
        else if(matrix[index] == 'B') {
            matrix[index] = '.';
            _balls--;
            _score += 5;
            ghostsTrouble();
            bigBalls++;
            glutTimerFunc(10000, backToNormal, 1);
        }
    }
    if(_pac->isLeft()){
        if(matrix[index] == 'b'){
            matrix[index] = '.';
            _balls--;
            _score += 1;
        }
        else if(matrix[index] == 'B') {
            matrix[index] = '.';
            _balls--;
            _score += 5;
            ghostsTrouble();
            bigBalls++;
            glutTimerFunc(10000, backToNormal, 1);
        }
    }
    if(_pac->isRight()){
        if(matrix[index] == 'b'){
            matrix[index] = '.';
            _balls--;
            _score += 1;
        }
        else if(matrix[index] == 'B') {
            matrix[index] = '.';
            _balls--;
            _score += 5;
            ghostsTrouble();
            bigBalls++;
            glutTimerFunc(10000, backToNormal, 1);
        }
    }
}

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

void Game::detonate(){
    _detonator = true;
    _pac->_explodingTime = true;
    _explosion = new Explosion(_pac->getX(), _pac->getY(), _pac->getZ());
    _lives--;
}

bool Game::colision(Ghost* g){
    //ghost à direita do pacman
    if(!g->_hiddenTime && !_pac->_explodingTime && g->getX() > _pac->getX() && g->getY() == _pac->getY() && g->getX()-GHOST_RADIUS <= _pac->getX()+PAC_RADIUS){
        if(g->_trouble){
            g->_hiddenTime = true;
            stack->push_back(g);
            glutTimerFunc(5000, theComeBack, 0);
            _score +=50;
            return false;
        }
        else{
            detonate();
            return true;
        }
    }
    //ghost à esquerda do pacman
    else if(!g->_hiddenTime && !_pac->_explodingTime && g->getX() < _pac->getX() && g->getY() == _pac->getY() && g->getX()+GHOST_RADIUS >= _pac->getX()-PAC_RADIUS){

        if(g->_trouble){
            g->_hiddenTime = true;
            stack->push_back(g);
            glutTimerFunc(5000, theComeBack, 0);
            _score +=50;
            return false;
        }
        else{
            detonate();
            return true;
        }
    }
    //mesma coluna
    else if(!g->_hiddenTime && !_pac->_explodingTime && g->getX() == _pac->getX()){
        //ghost acima do pacman
        if(!g->_hiddenTime && !_pac->_explodingTime && g->getY() > _pac->getY() && g->getX() == _pac->getX() && g->getY()-GHOST_RADIUS <= _pac->getY()+PAC_RADIUS){

            if(g->_trouble){
                g->_hiddenTime = true;
                stack->push_back(g);
                glutTimerFunc(5000, theComeBack, 0);
                _score +=50;
                return false;
            }
            else{
                detonate();
                return true;
            }
        }
        //ghost abaixo do pacman
        else if(!g->_hiddenTime && !_pac->_explodingTime && g->getY() < _pac->getY() && g->getX() == _pac->getX() && g->getY()+GHOST_RADIUS >= _pac->getY()-PAC_RADIUS){

            if(g->_trouble){
                g->_hiddenTime = true;
                stack->push_back(g);
                glutTimerFunc(5000, theComeBack, 0);
                _score +=50;
                return false;
            }
            else{
                detonate();
                return true;
            }
        }
        else {
        }
    }
    return true;
}

void Game::draw(){
    
    glPushMatrix();
	
    if(!_balls && !_pac->_explodingTime){
        winnerRenderBitmapString();
    }
    
    else if(!_lives && !_pac->_explodingTime){
        loserRenderBitmapString();
    }
    
    else{
        
        //Camera
        _camera->setLookAt();
        
        //Lights
        _light->lightUs(_pac);
        
        
        _maze->draw();
        ballsInspector();
        
        
        if(_ghostOne->_trouble){
            _ghostOne->setColor(1, 1, 1);
            _ghostOne->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostOne->setColor(0,0,1);
            _ghostOne->setSpeed(GHOST_NORMAL_SPEED);
        }
        colision(_ghostOne);
        if(!_ghostOne->_hiddenTime){
            _ghostOne->draw();
        }
        
        
        if(_ghostTwo->_trouble){
            _ghostTwo->setColor(1, 1, 1);
            _ghostTwo->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostTwo->setColor(1,0,0);
            _ghostTwo->setSpeed(GHOST_NORMAL_SPEED);
        }
        colision(_ghostTwo);
        if(!_ghostTwo->_hiddenTime){
            _ghostTwo->draw();
        }
        
        
        if(_ghostThree->_trouble){
            _ghostThree->setColor(1, 1, 1);
            _ghostThree->setSpeed(GHOST_ESCAPE_SPEED);
        }
        else {
            _ghostThree->setColor(0, 1, 0);
            _ghostThree->setSpeed(GHOST_NORMAL_SPEED);
        }
        colision(_ghostThree);
        if(!_ghostThree->_hiddenTime){
            _ghostThree->draw();
        }
        
        //desenhar a explosao OU o pacman
        if(_detonator){
            _explosion->draw();
            if(!_explosion->_areThereAnyParticles){
                _detonator = false;
                _pac->backAgain();
                
            }
        }
        else{
            _pac->draw();
        }
        
        
        renderBitmapString();
        
    }
    
    glPopMatrix();
}







