#pragma once
#ifndef Platform_hpp
#define Platform_hpp

#include "GameObj.hpp"

class Platform : public GameObj {
public:
    // Overloaded constructor
    Platform(b2World* world, float32 xStart,
             float32 yStart, float32 initSpeed);
    // Virtual destructor
    virtual ~Platform();
    // Returns the b2Body
    virtual b2Body* getBody() const;
    // Returns the landed flag
    bool getLanded() const;
    // Sets the landed flag
    void setLanded(bool flag);
    
private:
    // Speed at which to move the platform
    b2Vec2 speed;
    // Flag indicating whether or not the player has landed on this platform
    bool landed;
};

#endif /* Platform_hpp */

