#include "World.hpp"
#include <Box2D.h>

World::World() {}

World::~World() {
	delete world;
	delete player;
	//delete plat;
}

bool World::init(int x, int y) {
	timeStep = 1.0f / 60.0f;
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

	player = new Player(world, 20, 20);
	objects[new Platform(world, 20, 10, 0.1)] = "dirt.bmp";

	return true;
	// should probably check for errors, and return true if there are none
}

void World::tick() {
	// ticking the world ahead
	world->Step(timeStep, velocityIterations, positionIterations);
	if ((time % 200) == 0) {
		platGen();
	}

	// printing out all object positions (temporary measure)
	b2Vec2 temp = player->getBody()->GetPosition();
	std::cout << "Player: " << temp.x << ", " << temp.y << std::endl;
	for (auto itr = objects.begin(); itr != objects.end(); itr++) {
		b2Vec2 temp2 = (itr->first)->getBody()->GetPosition();
		std::cout << "Platform: " << temp2.x << ", " << temp2.y << std::endl;
	}
	std::cout << std::endl;
}

WorldState * World::getState() {
	return new WorldState();
}

void World::command(int command) {
	switch (command) {
	case LEFT:
		player->pushLeft();
		break;
	case RIGHT:
		player->pushRight();
		break;
	case JUMP:
		player->jump();
		break;
	}
}

void World::platGen() {
	objects[new Platform(world, 20, 10, 0.1)] = "dirt.bmp";
}