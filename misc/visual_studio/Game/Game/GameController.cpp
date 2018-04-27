#include "GameController.hpp"

GameController::GameController() {}

GameController::~GameController() {
	delete world;
	delete view;
}

void GameController::init(const char *title, int width, int height, bool fullscreen) {
	world = new World();
	view = new SDLView(this);
	if (view->init(title, width, height, fullscreen) &&
		world->init(width, height)) {
		playing = true;
	}
	else {
		// do something to prematurely quit
	}

	// Start frame
	Uint32 frameStart;
	// Time frame
	int frameTime;

	// Main game loop
	while (playing) {
		// Ticking the world ahead
		world->tick();

		// Rendering the world
		view->render(world->getState());

		// Set frameStart to number of ms since SDL was first initialized
		frameStart = SDL_GetTicks();

		// Set frameTime to number of ms it takes to handle events, update, and render
		frameTime = SDL_GetTicks() - frameStart;

		// Check if we need to delay rendering the next frame for smoother movement
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}

void GameController::handleKey(int key) {
	switch (key) {
	case UP_ARROW:
		world->command(world->JUMP);
		break;
	case LEFT_ARROW:
		world->command(world->LEFT);
		break;
	case RIGHT_ARROW:
		world->command(world->RIGHT);
		break;
	case EXIT:
		playing = false;
	}
}