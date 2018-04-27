#pragma once
#ifndef World_hpp
#define World_hpp

#include <map>
#include "IWorld.hpp"
#include "Player.hpp"
#include "Platform.hpp"

class World : public IWorld {
public:
	World();
	virtual ~World();
	virtual bool init(int width, int height);
	virtual void tick();
	virtual WorldState * getState();
	virtual void command(int command);
private:
	int width;
	int height;
	b2World * world;
	Player * player;
	//GameObj * plat;
	map<GameObj *, string> objects;

	int time = 0;
	float32 timeStep;
	static const int32 velocityIterations = 8;
	static const int32 positionIterations = 3;

	virtual void platGen();
};

#endif /* World_hpp */