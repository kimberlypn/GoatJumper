#pragma once
#ifndef Player_hpp
#define Player_hpp

#include "GameObj.hpp"
#include <iostream>
using namespace std;

class Player : public GameObj {
public:
    // Overloaded constructor
    Player(b2World* world, float32 xStart, float32 yStart);
    // Virtual destructor
    virtual ~Player();
    // Returns the b2Body
    virtual b2Body* getBody() const;
    // Makes the player jump
    virtual bool jump();
    // Moves the player to the left
    virtual void pushLeft();
    // Moves the player to the right
    virtual void pushRight();
    
private:
    // Force to be applied to the player to move it
    const b2Vec2* const rightForce = new b2Vec2(200.0f, 0.0f);
    const b2Vec2* const leftForce = new b2Vec2(-200.0f, 0.0f);
    const float32 jumpSpeed = 20;
};

#endif /* Player_hpp */
