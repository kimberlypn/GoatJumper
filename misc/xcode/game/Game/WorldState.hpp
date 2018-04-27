#pragma once
#ifndef WorldState_hpp
#define WorldState_hpp

#include "ObjState.hpp"
#include <string>
#include <vector>
using namespace std;

class WorldState {
public:
    // Constructor
    WorldState();
    // Deconstructor
    ~WorldState();
    // Adds a state to the states vector
    void addState(string imgSrc, float xpos, float ypos,
                  int height, int width);
    // Returns the game objects
    vector<ObjState> getStates() const;
    // Sets the platform score
    void setPlatformScore(int score);
    // Returns the number of platforms that the player has landed on
    int getPlatformScore() const;
    // Sets the distance
    void setDistance(int dist);
    // Returns the distance that the player has travelled
    int getDistance() const;
    // Sets the current map
    void setMap(int map);
    // Gets the current map
    int getMap() const;
    // Sets the gameOver flag
    void setGameOver(bool flag);
    // Returns the gameOver flag
    bool getGameOver() const;
    
    static const int DESERT = 1;
    static const int CITY = 2;
    static const int VALLEY = 3;
    static const int NUM_MAPS = 3;
    
private:
    vector<ObjState> states;
    int platformScore;
    int distance;
    bool gameOver;
    int map;
};

#endif /* WorldState_hpp */

