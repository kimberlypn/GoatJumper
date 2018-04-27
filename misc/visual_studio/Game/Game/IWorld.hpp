#pragma once
#ifndef IWorld_hpp
#define IWorld_hpp
#include "WorldState.hpp"
#include "ISoundListener.hpp"
#include "IEffectListener.hpp"

class IWorld {
public:
	virtual ~IWorld() {}
	virtual bool init(int width, int height) = 0;
	virtual void tick() = 0;
	virtual WorldState * getState() = 0;
	virtual void command(int command) = 0;

	static const int JUMP = 0;
	static const int LEFT = 1;
	static const int RIGHT = 2;
protected:
	ISoundListener * sl;
	IEffectListener * el;
};

#endif /* IWorld_hpp */