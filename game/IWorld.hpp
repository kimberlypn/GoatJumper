#pragma once
#ifndef IWorld_hpp
#define IWorld_hpp

#include <iostream>
#include "WorldState.hpp"
#include "ISoundListener.hpp"
using namespace std;

class IWorld {
public:
    // Virtual destructor
    virtual ~IWorld() {}
    // Initializes the world, given the window dimensions
    virtual bool init(int width, int height) = 0;
    // Advances the world by a tick
    virtual void tick() = 0;
    // Returns the game state
    virtual WorldState* getState() = 0;
    // Updates the game objects according to the key command
    virtual void command(int command) = 0;
    // Resets the world
    virtual void reset() = 0;
    
    // Static constants corresponding to various key commands
    static const int JUMP = 0;
    static const int LEFT = 1;
    static const int RIGHT = 2;
    
protected:
    // Handles sound events
    ISoundListener* sl;
};

#endif /* IWorld_hpp */

