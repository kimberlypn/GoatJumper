#pragma once
#ifndef Platform_hpp
#define Platform_hpp

#include "GameObj.hpp"

class Platform : public GameObj {
public:
	Platform(b2World * world, float32 xStart, float32 yStart, float32 initSpeed);
	virtual ~Platform();
	virtual b2Body * getBody();
	//virtual string getID();
private:
	b2Vec2 speed;
};

#endif /* Platform_hpp */