#pragma once
#ifndef Player_hpp
#define Player_hpp

#include "GameObj.hpp"

class Player : public GameObj {
public:
	Player(b2World * world, float32 xStart, float32 yStart);
	virtual ~Player();
	virtual b2Body * getBody();
	//virtual string getID();
	virtual bool jump();
	virtual void pushLeft();
	virtual void pushRight();
private:
	b2Vec2 * velocity;
	const b2Vec2 * const rightForce = new b2Vec2(100.0f, 0.0f);
	const b2Vec2 * const leftForce = new b2Vec2(-100.0f, 0.0f);
	const b2Vec2 * const jumpImpulse = new b2Vec2(0.0f, 40.0f);
};

#endif /* Player_hpp */