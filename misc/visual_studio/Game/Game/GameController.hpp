#ifndef GameController_hpp
#define Controller_hpp

#include <SDL.h>
#include "SDL_image.h"
#include <Box2D.h>
#include <iostream>
#include "IKeyListener.hpp"
#include "IWorld.hpp"
#include "IView.hpp"
#include "World.hpp"
#include "SDLView.hpp"

class GameController : private IKeyListener {
public:
    // Constructor
	GameController();
    // Deconstructor
    ~GameController();
    // Initializes the game
    void init(const char *title, int xpos, int height, bool fullscreen);
	// Handles key inputs from the view
	virtual void handleKey(int command);
    
	static const int FPS = 60;
	static const int frameDelay = 1000 / FPS;
private:
	bool playing;
	IWorld * world;
	IView * view;
	ISoundListener * ls;
};

#endif /* GameController_hpp */
