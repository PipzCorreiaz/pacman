#include "Ghost.h"
#include "Wizard.h"


Ghost::Ghost(int posx, int posy, int id, float xColor, float yColor, float zColor, float shine) : Character() {
	_eye = new Eye();
	_posX = posx;
    _posY = posy; 
    _posZ = 0;
    _angle = DOWN_ANGLE;
    _direction = DOWN;
    _speed = GHOST_NORMAL_SPEED; // unidades do labirinto per second
    _trouble = false;
    _ghostId = id;
    _hidden = false;
    
    _previousX = 0.0;
    _previousY = 0.0;
    _lastSymbol = SMALL_BALL;

    _color.push_back(xColor);
    _color.push_back(yColor);
    _color.push_back(zColor);
    _color.push_back(shine);
}


bool Ghost::getTrouble() {
    return _trouble;
}


bool Ghost::getHidden() {
    return _hidden;
}

void Ghost::setSpeed(float speed){
    _speed = speed;
}


void Ghost::setTrouble(bool trouble){
    _trouble = trouble;
}


void Ghost::setHidden(bool value){
    _hidden = value;
}

void Ghost::move(float dist) {
    Wizard::getInstance().changeMap(getX(), getY(), _lastSymbol);
    
    Character::move(dist);
    if (getTrouble()) {
        setLastSymbol(Wizard::getInstance().getMapSymbol(getX(), getY()));
        Wizard::getInstance().changeMap(getX(), getY(), SCARED_GHOST);
    } else {
        setLastSymbol(Wizard::getInstance().getMapSymbol(getX(), getY()));
        Wizard::getInstance().changeMap(getX(), getY(), GHOST);
    }

}

void Ghost::update(float dt) {
    float dist = getSpeed() * dt;
    std::vector<float> nextPosition = Character::nextPosition(dist);
    
    
    if(!_hidden) {
        
        if (Wizard::getInstance().isWall(nextPosition[0], nextPosition[1], getDirection())) {
            move(dist);
            turn(Wizard::getInstance().availablePosition(nextPosition[0], nextPosition[1]));
            
            _previousX = round(getX());
            _previousY = round(getY());
            
        } else {
            
            if(Wizard::getInstance().canTurn(getX(), getY())) {
                if (! (_previousX == round(getX()) && _previousY == round(getY()))) {
                    turn(Wizard::getInstance().availablePosition(getX(), getY()));
                }
                _previousX = round(getX());
                _previousY = round(getY());
                move(dist);
            }else {
                move(dist);
            }
        }
    }
}


void Ghost::shoot(int i) {
    _life -= GUN_POWER;
    if (_life == 0) {
        setHidden(true);
        backAgain();
        glutTimerFunc(5000, theComeBack, i);
    }
}


void Ghost::backAgain(){
    _life = 100;
    setX(0.0f);
	setY(0.0f);
    setAngle(DOWN_ANGLE);
    setDirection(DOWN);
}

void Ghost::draw() {


    if(!getHidden()) {

        glPushMatrix();
        
        glTranslatef(getX(),getY(), getZ()); // colocar ghost na pos (x,y,z)

    	glRotatef(getAngle(), 0, 0, 1); // direccao do ghost

        _eye->intoPlace(0.4f, -1.28f, 2.0f); //olho direito
        _eye->draw();
        _eye->intoPlace(-0.4f, -1.28f, 2.0f); //olho esquerdo
        _eye->draw();

        int j=0;
    
        if(getTrouble()) {
            setColor(1, 1, 1, 100);
        }
        else {
            setColor(_color[j], _color[j+1], _color[j+2], 40.0);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);         
        }
    	
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

        if(!getTrouble()) {
            glDisable(GL_BLEND);
        }
        
        glPopMatrix();
    }
    
}


