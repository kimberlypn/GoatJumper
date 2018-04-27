#pragma once
#ifndef SDLView_hpp
#define SDLView_hpp
#include <SDL.h>
#include "IView.hpp"
#include <iostream>

class SDLView : public IView {
public:
	SDLView(IKeyListener * listener);
	~SDLView();
	bool init(const char *title, int width, int height, bool fullscreen);
	void render(WorldState * state);
	void check();
protected:
	virtual void draw(const char* address, SDL_Rect src, SDL_Rect dest);
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Event event;
};

#endif /* Renderer_hpp */