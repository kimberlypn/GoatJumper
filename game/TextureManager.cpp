#include "TextureManager.hpp"

map<string, SDL_Texture*> TextureManager::textures;

TextureManager::~TextureManager() {
    for (auto itr = TextureManager::textures.begin();
         itr != TextureManager::textures.end(); itr++)
        SDL_DestroyTexture(itr->second);
}

SDL_Texture* TextureManager::loadTexture(string tex, SDL_Renderer* renderer) {
    
    // Check if the texture already exists
    map<string, SDL_Texture*>::iterator itr = textures.find(tex);
    
    // If this is a new texture
    if (itr == TextureManager::textures.end()) {
        // Create a surface for the given texture
        SDL_Surface* tempSurf = IMG_Load(tex.c_str());
        //SDL_Surface* tempSurf = SDL_LoadBMP(tex);
        
        // Add the texture to the map
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurf);
        TextureManager::textures.insert(pair<string,
                                        SDL_Texture*>(tex, texture));
        
        // Get the added texture
        itr = TextureManager::textures.find(tex);
        
        // Clean up pointers
        SDL_FreeSurface(tempSurf);
    }
    
    // Return the new texture
    return itr->second;
}

SDL_Texture* TextureManager::loadText(const char* text,
                                      int fontSize,
                                      SDL_Color fontColor,
                                      SDL_Renderer* renderer) {
    // Initialize the font library
    TTF_Init();
    
    // Adding the folder location to the font address
    string address = "assets/fonts/PixelOperator.ttf";
    
    // Set the font and font size and then free the resource
    TTF_Font* font = TTF_OpenFont(address.c_str(), fontSize);
    
    // Add the text to a surface
    SDL_Surface* temp = TTF_RenderText_Solid(font, text, fontColor);
    
    // Turn the surface into a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
    
    // Clean up the temp surface because it is no longer needed
    SDL_FreeSurface(temp);
    
    // Close the font library
    TTF_CloseFont(font);
    
    // Return the new texture
    return texture;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,
                          SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, tex, &src, &dest);
}

void TextureManager::addText(SDL_Texture* tex, int xpos, int ypos,
                             SDL_Renderer* renderer) {
    // Use SDL_QueryTexture so that the text doesn't stretch to fill the window
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(tex, NULL, NULL, &texW, &texH);
    SDL_Rect dest = {xpos, ypos, texW, texH};
    
    SDL_RenderCopy(renderer, tex, NULL, &dest);
}

int TextureManager::getWidth(SDL_Texture* tex) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    return w;
}

int TextureManager::getHeight(SDL_Texture* tex) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    return h;
}

int TextureManager::getCenterX(int window_width, SDL_Texture* tex) {
    return (window_width - getWidth(tex)) / 2;
}

int TextureManager::getCenterY(int window_height, SDL_Texture* tex) {
    return (window_height - getHeight(tex)) / 2;
}
