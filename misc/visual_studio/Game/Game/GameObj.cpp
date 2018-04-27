#include "GameObj.hpp"

GameObj::~GameObj() {

}

b2Body * GameObj::getBody() {
	return body;
}