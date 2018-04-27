#include "SDLView.hpp"

SDLView::SDLView(IKeyListener * listener) {
	kl = listener;
}

bool SDLView::init(const char *title, int width, int height, bool fullscreen) {
	int flags = 0;
	// Check if the user wanted the game to be fullscreen
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	// If all of the subsystems have been initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initiated" << std::endl;
		// Create the window using the arguments given
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		// Check if the window has been created successfully
		if (window)
			std::cout << "Window created" << std::endl;

		// Create the renderer
		renderer = SDL_CreateRenderer(window, -1, 0);

		// Check if the renderer has been created successfully
		if (renderer) {
			// Set the background color to white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		return true;
	}
	return false;
}

SDLView::~SDLView() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDLView::render(WorldState * state) {
	check();
	SDL_RenderClear(renderer);

	// ...

	SDL_RenderPresent(renderer);
}

void SDLView::check() {
	// Checking current keyboard state for held down keys
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT])
		kl->handleKey(kl->LEFT_ARROW);
	if (keyboardState[SDL_SCANCODE_RIGHT])
		kl->handleKey(kl->RIGHT_ARROW);

	// Checking for events, e.g. exitting and key-presses
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			// Window was closed
		case SDL_QUIT:
			kl->handleKey(kl->EXIT);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				kl->handleKey(kl->UP_ARROW);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void SDLView::draw(const char* address, SDL_Rect src, SDL_Rect dest) {
	// Create a surface for the given texture
	SDL_Surface * temp = SDL_LoadBMP(address);
	// Turn the surface into a texture
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, temp);
	// Clean up the temp surface because it is no longer needed
	SDL_FreeSurface(temp);
	// Rendering the surface
	SDL_RenderCopy(renderer, texture, &src, &dest);
}