#ifndef PacmanLove_Eyebrow_h
#define PacmanLove_Eyebrow_h

class Eyebrow{
    
public:
    Eyebrow();
    ~Eyebrow();
	
	void draw();
    void intoPlace(float posX, float posY, float posZ);
   	void adjust(float angle);
	
	
private:
    float _posX;
    float _posY;
    float _posZ;
    float _angle;
    
    
};

#endif
