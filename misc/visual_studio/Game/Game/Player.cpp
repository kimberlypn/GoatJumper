#include "Player.hpp"

Player::Player(b2World * world, float32 xStart, float32 yStart) {// defining the player shape
	b2PolygonShape playerShape;
	playerShape.SetAsBox(1.0f, 1.0f);

	// defining the player fixture
	b2FixtureDef playerFix;
	playerFix.shape = &playerShape;
	playerFix.density = 1.0f;
	playerFix.friction = 0.25f;

	// defining the player
	b2BodyDef playerDef;
	playerDef.type = b2_dynamicBody;
	playerDef.position.Set(xStart, yStart);
	playerDef.angle = 0.0f;
	playerDef.fixedRotation = true;
	body = world->CreateBody(&playerDef);
	body->CreateFixture(&playerFix);
}

Player::~Player() {}

b2Body * Player::getBody() {
	return body;
}

//string Player::getID() {
//	return "player";
//}

bool Player::jump() {
	velocity = new b2Vec2(body->GetLinearVelocity().x, 0.0f);
	body->SetLinearVelocity(*velocity);
	body->ApplyLinearImpulseToCenter(*jumpImpulse, true);
	return true;
	// should not always be true, should check for contact to platform or something
}

void Player::pushLeft() {
	body->ApplyForceToCenter(*leftForce, true);
}

void Player::pushRight() {
	body->ApplyForceToCenter(*rightForce, true);
}