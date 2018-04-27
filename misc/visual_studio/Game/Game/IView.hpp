#pragma once
#ifndef IView_hpp
#define IView_hpp
#include "WorldState.hpp"
#include "IKeyListener.hpp"

class IView {
public:
	virtual bool init(const char *title, int width, int height, bool fullscreen) = 0;
	virtual ~IView() {}
	virtual void render(WorldState * state) = 0;
protected:
	IKeyListener * kl;
};

#endif /* IView_hpp */