#pragma once
#ifndef GameObj_hpp
#define GameObj_hpp

#include <Box2D.h>
#include <string>
#include <iostream>

using namespace std;

class GameObj {
public:
	virtual ~GameObj();
	virtual b2Body * getBody();
	//virtual string getID() = 0;
protected:
	//string ID;
	b2Body * body;
};

#endif /* GameObj_hpp */