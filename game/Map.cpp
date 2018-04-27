#include "Map.hpp"
#include "World.hpp"

Map::Map() {
    // Set the source and destination; all maps are 640x800
    src.h = 640;
    src.w = 800;
    src.x = 0;
    src.y = 0;
    
    // Scale the image
    dest.w = src.w;
    dest.h = src.h;
    dest.x = 0;
    dest.y = 0;
}

Map::~Map() {
    // Clean up pointers
    SDL_DestroyTexture(map);
}

void Map::setMap(SDL_Renderer* renderer, int mapType) {
    // Set the map; load  images instead if .png does not work
    switch (mapType) {
        case WorldState::CITY:
            map = TextureManager::loadTexture("assets/images/map-city.png",
                                              renderer);
            break;
        case WorldState::DESERT:
            map = TextureManager::loadTexture("assets/images/map-desert.png",
                                              renderer);
            break;
        case WorldState::VALLEY:
            map = TextureManager::loadTexture("assets/images/map-valley.png",
                                              renderer);
            break;
    }
}

void Map::drawMap(SDL_Renderer* renderer) {
    TextureManager::draw(map, src, dest, renderer);
}
