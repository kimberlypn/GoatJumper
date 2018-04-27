#include "Enemy.hpp"

Enemy::Enemy(b2World* world, float32 width, float32 height,
             float32 xStart, float32 yStart, float32 xSpeed, float32 ySpeed) {
    // Set the type
    type = new int(ENEMY);
    
    // Define the shape
    b2PolygonShape jumpShape;
    jumpShape.SetAsBox(width / 2, height / 2);
    size = b2Vec2(width, height);
    
    // Define the fixture
    b2FixtureDef jumpFix;
    jumpFix.shape = &jumpShape;
    jumpFix.density = 1.0f;
    jumpFix.friction = 0;
    jumpFix.isSensor = true;
    
    // Define the platform
    b2BodyDef jumpDef;
    jumpDef.type = b2_dynamicBody;
    jumpDef.position.Set(xStart, yStart);
    jumpDef.angle = 0.0f;
    jumpDef.gravityScale = 0.5;
    
    // Create the platform
    body = world->CreateBody(&jumpDef);
    body->CreateFixture(&jumpFix);
    body->SetUserData(type);
    
    // Define the initial speed
    b2Vec2 speed(xSpeed, ySpeed);
    body->SetLinearVelocity(speed);
    body->SetUserData(this);
}

Enemy::~Enemy() {}

