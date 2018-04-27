#include <iostream>
#include <stdlib.h>
#include "GameController.hpp"
#define SDL_MAIN_HANDLED

/****************************** GLOBAL VARIABLES ******************************/

// Window dimensions
static const int WIDTH = 800;
static const int HEIGHT = 640;

/*************************** END OF GLOBAL VARIABLES **************************/

int main() {
    // Create a new game
    GameController* game = new GameController();
    
    // Initialize the game
    game->init("Game", WIDTH, HEIGHT, false);
    
    // Delete the game
    delete game;
    
    return 0;
}

