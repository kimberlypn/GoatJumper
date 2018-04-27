#pragma once
#ifndef GameObj_hpp
#define GameObj_hpp

#include <Box2D/Box2D.h>

class GameObj {
public:
    // Virtual destructor
    virtual ~GameObj();
    // Returns the b2Body
    virtual b2Body* getBody() const;
    // Returns the ID of the object
    virtual int getID() const;
    // Returns the size of the object
    virtual b2Vec2 getSize() const;
    
    // Static constants corresponding to the object's type
    static const int NEUTRAL = 0;
    static const int PLAYER = 1;
    static const int PLATFORM = 2;
    static const int ENEMY = 3;
    
protected:
    // b2Body and b2Vec2 are needed for Box2D
    b2Body* body;
    b2Vec2 size;
    // Int corresponding to the object's type
    int* type;
};

#endif /* GameObj_hpp */

