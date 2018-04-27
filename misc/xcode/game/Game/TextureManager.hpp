#pragma once
#ifndef TextureManager_h
#define TextureManager_h

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
using namespace std;

class TextureManager {
public:
    // Destructor
    ~TextureManager();
    // Creates a surface for the given texture
    static SDL_Texture* loadTexture(string tex, SDL_Renderer* renderer);
    // Creates a text texture
    static SDL_Texture* loadText(const char* text, int fontSize,
                                 SDL_Color fontColor, SDL_Renderer* renderer);
    // Draws the texture onto the screen
    static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,
                     SDL_Renderer* renderer);
    // Draws text onto the screen
    static void addText(SDL_Texture* tex, int xpos, int ypos,
                        SDL_Renderer* renderer);
    // Returns the width of a texture
    static int getWidth(SDL_Texture* tex);
    // Returns the height of a texture
    static int getHeight(SDL_Texture* tex);
    // Returns the xpos that should be used to center a texture on the screen
    static int getCenterX(int window_width, SDL_Texture* tex);
    // Returns the ypos that should be used to center a texture on the screen
    static int getCenterY(int window_height, SDL_Texture* tex);
    
private:
    // Holds existing textures to avoid recreation
    static map<string, SDL_Texture*> textures;
};

#endif /* TextureManager_h */


