#include "Platform.hpp"

Platform::Platform(b2World * world, float32 xStart, float32 yStart, float32 initSpeed) {
	// defining the Platform shape
	b2PolygonShape PlatformShape;
	PlatformShape.SetAsBox(5.0f, 0.5f);

	// defining the platform fixture
	b2FixtureDef platformFix;
	platformFix.shape = &PlatformShape;
	platformFix.density = 1.0f;
	platformFix.friction = 0.25f;

	// defining the platform
	b2BodyDef platformDef;
	platformDef.type = b2_kinematicBody;
	platformDef.position.Set(xStart, yStart);
	platformDef.angle = 0.0f;
	body = world->CreateBody(&platformDef);
	body->CreateFixture(&platformFix);

	// defining the initial speed
	speed = b2Vec2(-initSpeed, 0);
	body->SetLinearVelocity(speed);
}

Platform::~Platform() {

}

b2Body * Platform::getBody() {
	return body;
}

//string Platform::getID() {
//	return "platform";
//}