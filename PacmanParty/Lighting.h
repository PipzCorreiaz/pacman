#ifndef __LIGHTNING_H__
#define __LIGHTNING_H__

#include "Character.h"

class Lighting {
    
public:
    
    Lighting();
    ~Lighting();
    void virtual lightUs(Character *pac) = 0;
    
};

#endif
