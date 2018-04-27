#include "Platform.hpp"

Platform::Platform(b2World* world, float32 xStart,
                   float32 yStart, float32 initSpeed) {
    // Set the type
    type = new int(PLATFORM);
    
    // Set the flag
    landed = false;
    
    // Define the shape
    b2PolygonShape PlatformShape;
    PlatformShape.SetAsBox(10, 1);
    size = b2Vec2(20, 2);
    
    // Define the fixture
    b2FixtureDef platformFix;
    platformFix.shape = &PlatformShape;
    platformFix.density = 1.0f;
    platformFix.friction = 0.25f;
    
    // Define the platform
    b2BodyDef platformDef;
    platformDef.type = b2_kinematicBody;
    platformDef.position.Set(xStart, yStart);
    platformDef.angle = 0.0f;
    
    // Create the platform
    body = world->CreateBody(&platformDef);
    body->CreateFixture(&platformFix);
    body->SetUserData(type);
    
    // Define the initial speed
    speed = b2Vec2(-initSpeed, 0);
    body->SetLinearVelocity(speed);
    body->SetUserData(this);
}

Platform::~Platform() {}

b2Body* Platform::getBody() const {
    return body;
}

bool Platform::getLanded() const {
    return landed;
}

void Platform::setLanded(bool flag) {
    landed = flag;
}

