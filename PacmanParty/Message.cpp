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
    std::string type;

    switch (getMessage()) {
        case TRANSFER_AMMUNITION:
            type = "TRANSFER_AMMUNITION";
            break;
        case BE_HEALED:
            type = "BE_HEALED";
            break;
        default:
            break;
    }

    oss << getSender() << " says: " << type << " at (" << getX() << ", " << getY() << ")";
    return oss.str();
}