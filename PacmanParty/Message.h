#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#if defined (__APPLE__) || defined (MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <ostream>
#include <iostream>

class Message {
    
public:
    Message();
    Message(char sender, float x, float y, int message);
    ~Message();

    char getSender();
    float getX();
    float getY();
    int getMessage();

    std::string toString();

private:
    float _x;
    float _y;
    int _message;
    char _sender;
    
};

#endif