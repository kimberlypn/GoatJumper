#include "WorldState.hpp"

WorldState::WorldState() {
    platformScore = 0;
    distance = 0;
    gameOver = false;
}

WorldState::~WorldState() {
}

void WorldState::addState(string imgSrc, float xpos, float ypos,
                          int height, int width) {
    // Create a Posn using the given coordinates
    Posn p = Posn();
    p.xpos = xpos;
    p.ypos = ypos;
    
    // Create an ObjState
    ObjState obj = ObjState();
    obj.imgSrc = imgSrc;
    obj.coordinates = p;
    obj.height = height;
    obj.width = width;
    
    // Add the ObjState to the vector
    this->states.push_back(obj);
}

vector<ObjState> WorldState::getStates() const {
    return states;
}

void WorldState::setPlatformScore(int score) {
    platformScore = score;
}

int WorldState::getPlatformScore() const {
    return platformScore;
}

void WorldState::setDistance(int dist) {
    distance = dist;
}

int WorldState::getDistance() const {
    return distance;
}

void WorldState::setMap(int mapType) {
    map = mapType;
}

int WorldState::getMap() const {
    return map;
}

void WorldState::setGameOver(bool flag) {
    gameOver = flag;
}

bool WorldState::getGameOver() const {
    return gameOver;
}

