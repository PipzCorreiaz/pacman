#ifndef PacmanLove_Ball_h
#define PacmanLove_Ball_h

class Ball{
    
public:
    Ball();
    ~Ball();
    
    void draw();
    void intoPlace(float posX, float posY);
	void growth(float scale);
    
private:
    float _posX;
    float _posY;
    float _posZ;
    float _scale;
    
};

#endif
