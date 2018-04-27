#pragma once
#ifndef SDLView_hpp
#define SDLView_hpp

#include "IView.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

class SDLView : public IView {
public:
    // Overloaded constructor
    SDLView(IKeyListener* listener);
    // Destructor
    ~SDLView();
    // Initializes the window
    bool init(const char* title, int width, int height, bool fullscreen);
    // Renders the game
    void render(WorldState* state);
    // Renders the game objects
    void renderObjects(WorldState* state);
    // Renders the player's stats in the top left
    void renderStats(WorldState* state);
    // Renders the game over screen
    void renderLoser(WorldState* state);
    // Checks if any events have occurred (key press, exiting, etc.)
    void check();
    // Checks if the "PLAY AGAIN" button has been clicked
    void checkReset();
    // Resets the view
    void reset();
    
private:
    // Main game window
    SDL_Window* window;
    // Dimensions of main game window
    int window_height, window_width;
    // Scale for object coordinates
    int scale;
    // Used to render everything
    SDL_Renderer* renderer;
    // Event listener
    SDL_Event event;
    // Source and destination rectangles needed for rendering
    SDL_Rect srcRect, destRect;
    // Background for the game
    Map map;
    // Map type
    int mapType;
    // Time that the user started playing
    Uint32 startTime;
    // Current time; used for tracking score
    Uint32 currTime;
    // Position and dimensions of the reset button to calculate mouse event
    int resetX, resetY, resetW, resetH;
};

#endif /* SDLView_hpp */

