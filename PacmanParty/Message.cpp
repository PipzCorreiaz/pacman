#include "Message.h"

#include <sstream>

Message::Message() {

}

Message::Message(char sender, float x, float y, int message) {
    _sender = sender;
    _x = x;
    _y = y;
    _message = message;
}

Message::~Message() {

}

char Message::getSender() {
    return _sender;
}

float Message::getX() {
    return _x;
}

float Message::getY() {
    return _y;
}

int Message::getMessage() {
    return _message;
}

std::string Message::toString() {
    std::ostringstream oss;

    oss << getSender() << " says: " << getMessage() << " at (" << getX() << ", " << getY() << ")";
    return oss.str();
}