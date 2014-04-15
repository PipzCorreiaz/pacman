#ifndef PacmanLove_MinerHat_h
#define PacmanLove_MinerHat_h

#include <cmath>

class MinerHat {
    
public:
    MinerHat();
    ~MinerHat();
    
    void draw();
    void intoPlace(float posX, float posY, float posZ);
	void drawFace(float angle);
   
    
private:
    float _posX;
    float _posY;
    float _posZ;
    
};


#endif
