#pragma once
#ifndef Obstacle_hpp
#define Obstacle_hpp

#include "GameObj.hpp"

class Obstacle : public GameObj {
public:
    // Overloaded constructor
    Obstacle(b2World* world, float32 size, float32 xStart, float32 yStart,
             float32 xSpeed, float32 ySpeed);
    Obstacle(b2World* world, float32 xSize, float32 ySize, float32 xStart,
             float32 yStart, float32 xSpeed, float32 ySpeed);
    // Virtual destructor
    virtual ~Obstacle();
    
private:
    // Finishes the initialization
    void commonInit(b2Shape * shape, b2World* world, float32 xStart,
                    float32 yStart, float32 xSpeed, float32 ySpeed);
};

#endif /* Obstacle_hpp */

