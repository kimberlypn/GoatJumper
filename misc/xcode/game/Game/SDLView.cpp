#include "SDLView.hpp"

SDLView::SDLView(IKeyListener* listener) {
    kl = listener;
    startTime = 0;
    mapType = 0;
}

bool SDLView::init(const char* title, int width, int height, bool fullscreen) {
    int flags = 0;
    
    // Check if the user wanted the game to be fullscreen
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;
    
    // If all of the subsystems have been initialized
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems initiated" << endl;
        // Create the window using the arguments given
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width, height, flags);
        
        // Check if the window has been created successfully
        if (window)
            cout << "Window created" << endl;
        
        // Create the renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        
        // Check if the renderer has been created successfully
        if (renderer) {
            // Set the background color to white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created" << endl;
        }
        
        // Set the window height and width and the scale
        window_height = height;
        window_width = width;
        scale = 10;
        
        return true;
    }
    // Initialization failed
    return false;
}

SDLView::~SDLView() {
    // Clean up pointers
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void SDLView::render(WorldState* state) {
    // Check for any key inputs
    check();
    
    SDL_RenderClear(renderer);
    
    // Render the background
    if (mapType != state->getMap()) {
        mapType = state->getMap();
        map.setMap(renderer, mapType);
    }
    map.drawMap(renderer);
    
    // If the player died, render the game over screen
    if (state->getGameOver()) {
        // Render the game over message
        renderLoser(state);
    }
    else {
        // Render the objects
        renderObjects(state);
        // Render any text
        renderStats(state);
    }
    
    SDL_RenderPresent(renderer);
}

void SDLView::renderObjects(WorldState* state) {
    // Get the game state
    vector<ObjState> states = state->getStates();
    
    // Loop through all of the objects to be rendered
    for (auto itr = states.begin(); itr != states.end(); itr++) {
        string tex = strdup(itr->imgSrc.c_str());
        
        // Load the image onto a surface
        SDL_Texture* texture = TextureManager::loadTexture(tex, renderer);
        
        // Use the full width and height of the image
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = TextureManager::getWidth(texture);
        srcRect.h = TextureManager::getHeight(texture);
        
        // Scale the image
        destRect.w = itr->width * scale;
        destRect.h = itr->height * scale;
        destRect.x = (itr->coordinates.xpos - itr->width / 2) * scale;
        destRect.y = window_height
        - (itr->coordinates.ypos + itr->height / 2) * scale;
        
        // Draw the image where it is supposed to be
        TextureManager::draw(texture, srcRect, destRect, renderer);
    }
}

void SDLView::renderStats(WorldState* state) {
    // Set the font color
    SDL_Color color = {145, 247, 181};
    
    // Get the time in seconds
    currTime = (SDL_GetTicks() - startTime) / 1000;
    // Build the message to be rendered
    const char* timeElapsed = strdup(("TIME ELAPSED: "
                                       + to_string(currTime) + " s").c_str());
    // Render the time
    SDL_Texture* t1 = TextureManager::loadText(timeElapsed, 30,
                                               color, renderer);
    TextureManager::addText(t1, 10, 10, renderer);
    
    // Get the platform score
    const char* platform = strdup(("PLATFORMS LANDED: "
                                    + to_string(state->getPlatformScore())).c_str());
    // Render the time
    SDL_Texture* t2 = TextureManager::loadText(platform, 30,
                                               color, renderer);
    TextureManager::addText(t2, 10, 40, renderer);
    
    // Clean up
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);
}

void SDLView::renderLoser(WorldState* state) {
    // Set the font color
    SDL_Color color = {145, 247, 181};
    // Render the game over message
    const char* msg = "GAME OVER";
    SDL_Texture* t1 = TextureManager::loadText(msg, 100,
                                               color, renderer);
    int t1X = TextureManager::getCenterX(window_width, t1);
    int t1Y = TextureManager::getCenterY(window_height, t1);
    // Set "GAME OVER" higher than the center since there is more text below
    TextureManager::addText(t1, t1X, t1Y - 70, renderer);
    
    // Render the time survived
    startTime = SDL_GetTicks();
    const char* timeSurvived = strdup(("TIME SURVIVED: "
                                        + to_string(currTime) + " s").c_str());
    SDL_Texture* t2 = TextureManager::loadText(timeSurvived, 40,
                                               color, renderer);
    int t2X = TextureManager::getCenterX(window_width, t2);
    // Set the time below the "GAME OVER" text
    int t2Y = t1Y + 30;
    TextureManager::addText(t2, t2X, t2Y, renderer);
    
    // Render the platform score
    const char* score = strdup(("PLATFORMS LANDED: "
                                 + to_string(state->getPlatformScore())).c_str());
    SDL_Texture* t3 = TextureManager::loadText(score, 40,
                                               color, renderer);
    int t3X = TextureManager::getCenterX(window_width, t3);
    // Set the score below the time text
    int t3Y = t2Y + 50;
    TextureManager::addText(t3, t3X, t3Y, renderer);
    
    // Render the "PLAY AGAIN" button
    SDL_Texture* t4 = TextureManager::loadText(">> PLAY AGAIN <<", 40,
                                               color, renderer);
    int t4X = TextureManager::getCenterX(window_width, t4);
    // Set the time below the "TIME SURVIVED" text
    int t4Y = t3Y + 50;
    TextureManager::addText(t4, t4X, t4Y, renderer);
    // Save the "PLAY AGAIN" dimensions
    resetX = t4X;
    resetY = t4Y;
    resetW = TextureManager::getWidth(t4);
    resetH = TextureManager::getHeight(t4);
    
    // Clean up
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);
    SDL_DestroyTexture(t3);
    SDL_DestroyTexture(t4);
}

void SDLView::check() {
    // Check current keyboard state for held down keys
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_LEFT])
        kl->handleKey(kl->LEFT_ARROW);
    if (keyboardState[SDL_SCANCODE_RIGHT])
        kl->handleKey(kl->RIGHT_ARROW);
    
    // Check for events, e.g. exiting and key-presses
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
            case SDL_MOUSEBUTTONDOWN:
                checkReset();
                break;
            default:
                break;
        }
    }
}

void SDLView::checkReset() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    // Check if the user pressed the "PLAY AGAIN" button (with some padding)
    bool xBound = ((resetX - 5) <= x) && (x <= (resetX + resetW + 5));
    bool yBound = ((resetY - 5) <= y) && (y <= (resetY + resetH + 5));
    if (xBound && yBound) {
        // Tell the controller to reset the model and view
        kl->handleKey(kl->RESET);
    }
}

void SDLView::reset() {
    startTime = SDL_GetTicks();
}

