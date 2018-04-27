#pragma once
#ifndef World_hpp
#define World_hpp

#include <map>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <functional>
#include "IWorld.hpp"
#include "Player.hpp"
#include "Platform.hpp"
#include "Obstacle.hpp"
#include "Enemy.hpp"
using namespace std;

class World : public IWorld, public b2ContactListener {
public:
    // Constructor
    World();
    // Overloaded constructor
    World(ISoundListener* sl);
    // Destructor
    ~World();
    // Initializes the world, given the window dimensions
    bool init(int width, int height);
    // Advances the world by a tick
    void tick();
    // Returns the game state
    WorldState* getState();
    // Updates the game objects according to the key command
    void command(int command);
    // Resets the world
    void reset();
    
    // Functions to handle collisions
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
private:
    // Scaled window dimensions
    int width;
    int height;
    
    // Main world
    b2World* world;
    // User's player
    Player* player;
    // Map of all of the objects in the world
    map<GameObj*, string> objects;
    // True if the game is over
    bool gameOver = false;
    // The current game map
    int mapType = 1;
    
    // Used to handle jumping
    static const int MAX_JUMPS = 2;
    int jumpsLeft = 0;
    
    // Used to switch image
    bool forward = true;
    
    // Platform score
    int platformScore = 0;
    
    // Used to handle ticking
    int time = 0;
    float32 speed = 5;
    float32 timeStep;
    static const int32 velocityIterations = 8;
    static const int32 positionIterations = 3;
    
    // Adds side boundaries for player
    void makeBoundaries();
    // Generates a platform every once in a while
    void platGen();
    // Generates an enemy every once in a while
    void enemyGen();
    // Generates a random height to place the platform
    float32 random();
    // Prunes any out-of-bound objects
    void checkForDeletions();
    // Returns true if an object is out of bounds
    bool outOfBounds(GameObj* obj);
};

#endif /* World_hpp */
