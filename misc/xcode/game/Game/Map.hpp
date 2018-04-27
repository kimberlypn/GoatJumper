#pragma once
#ifndef Map_hpp
#define Map_hpp

#include "TextureManager.hpp"

class Map {
public:
    // Constructor
    Map();
    // Destructor
    ~Map();
    // Sets the current map
    void setMap(SDL_Renderer* renderer, int mapType);
    // Draws the game map
    void drawMap(SDL_Renderer* renderer);
    
private:
    // Source and destination for rendering
    SDL_Rect src, dest;
    // Map to be rendered
    SDL_Texture* map;
};

#endif /* Map_hpp */

