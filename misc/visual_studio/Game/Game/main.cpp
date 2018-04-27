#include <iostream>
#include <stdlib.h>
#include "GameController.hpp"
#define SDL_MAIN_HANDLED

static const int WIDTH = 800;
static const int HEIGHT = 640;

int main(int argc, char * argv[]) {
    // Create a new game
    GameController * game = new GameController();

    // Initialize the game
    game->init("Game", WIDTH, HEIGHT, false);

	// Deleting game
	delete game;

    return 0;
}
