#pragma once
#ifndef Enemy_hpp
#define Enemy_hpp

#include "GameObj.hpp"

class Enemy : public GameObj {
public:
    // Overloaded constructor
    Enemy(b2World* world, float32 width, float32 height,
          float32 xStart, float32 yStart, float32 xSpeed, float32 ySpeed);
    // Virtual destructor
    virtual ~Enemy();
};

#endif /* Enemy_hpp */
