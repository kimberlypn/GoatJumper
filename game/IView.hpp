#pragma once
#ifndef IView_hpp
#define IView_hpp

#include <iostream>
#include <string>
#include "WorldState.hpp"
#include "IKeyListener.hpp"
using namespace std;

class IView {
public:
    // Virtual destructor
    virtual ~IView() {}
    // Initializes the main game window
    virtual bool init(const char* title, int width,
                      int height, bool fullscreen) = 0;
    // Renders the game state
    virtual void render(WorldState* state) = 0;
    // Resets the view
    virtual void reset() = 0;
    
protected:
    // Handles key events
    IKeyListener* kl;
};

#endif /* IView_hpp */

