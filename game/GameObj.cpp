#include "GameObj.hpp"

GameObj::~GameObj() {
    // Clean up pointers; cannot delete 'body' because would be calling
    // private destructor of class 'b2Body'
    if (type != NULL)
        delete type;
}

b2Body* GameObj::getBody() const {
    return body;
}

int GameObj::getID() const {
    return *type;
}

b2Vec2 GameObj::getSize() const {
    return size;
}
