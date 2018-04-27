#include "GameController.hpp"

GameController::GameController() {}

GameController::~GameController() {
    // Clean up pointers
    if (world != NULL)
        delete world;
    if (view != NULL)
        delete view;
    if (sl != NULL)
        delete sl;
}

void GameController::init(const char* title, int width,
                          int height, bool fullscreen) {
    // Create a new world (model)
    sl = new SoundListener();
    world = new World(sl);
    // Create a new view
    view = new SDLView(this);
    
    // Set the playing flag to true if the view and world are
    // successfully initialized
    if (view->init(title, width, height, fullscreen)
        && world->init(width, height))
        playing = true;
    // Else, throw an error
    else
        cerr << "Unable to initialize the game." << endl;
    
    // Start frame
    Uint32 frameStart;
    // Time frame
    int frameTime;
    
    // Main game loop
    while (playing) {
        // Set frameStart to number of ms since SDL was first initialized
        frameStart = SDL_GetTicks();
        // Render the world
        view->render(world->getState());
        // Set frameTime to number of ms it takes to handle events, update,
        // and render
        frameTime = SDL_GetTicks() - frameStart;
        
        // Check if rendering needs to be delayed until next frame for
        // smoother movement
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        
        // Advance the world by a tick
        world->tick();
    }
}

void GameController::handleKey(int key) {
    switch (key) {
            // Make the player jump
        case UP_ARROW:
            world->command(world->JUMP);
            break;
            // Make the player move to the left
        case LEFT_ARROW:
            world->command(world->LEFT);
            break;
            // Make the player move to the right
        case RIGHT_ARROW:
            world->command(world->RIGHT);
            break;
            // Close the game
        case EXIT:
            playing = false;
            break;
        case RESET:
            reset();
            break;
    }
}

void GameController::reset() {
    world->reset();
    view->reset();
}
