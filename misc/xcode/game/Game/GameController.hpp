#pragma once
#ifndef GameController_hpp
#define GameController_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "IKeyListener.hpp"
#include "ISoundListener.hpp"
#include "IWorld.hpp"
#include "IView.hpp"
#include "World.hpp"
#include "SoundListener.hpp"
#include "SDLView.hpp"
using namespace std;

class GameController : private IKeyListener {
public:
    // Constructor
    GameController();
    // Deconstructor
    ~GameController();
    // Initializes the game
    void init(const char* title, int xpos, int height, bool fullscreen);
    // Handles key inputs from the view
    virtual void handleKey(int command);
    // Resets the model and view
    void reset();
    
    // Static constants for smooth gameplay
    static const int FPS = 60;
    static const int frameDelay = 1000 / FPS;
    
private:
    // Flag indicating whether or not the game is in-progress
    bool playing;
    // Main world (model)
    IWorld* world;
    // Main view
    IView* view;
    // Handles sound events
    ISoundListener* sl;
};

#endif /* GameController_hpp */

