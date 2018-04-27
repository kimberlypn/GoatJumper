#include "Obstacle.hpp"

Obstacle::Obstacle(b2World* world, float32 radius, float32 xStart,
                   float32 yStart, float32 xSpeed, float32 ySpeed) {
    
    // Define the shape
    b2CircleShape * enemyShape = new b2CircleShape();
    enemyShape->m_radius = radius;
    size = b2Vec2(radius * 2, radius * 2);
    
    // Perform rest of initialization
    commonInit(enemyShape, world, xStart, yStart, xSpeed, ySpeed);
}

Obstacle::Obstacle(b2World* world, float32 xSize, float32 ySize, float32 xStart,
                   float32 yStart, float32 xSpeed, float32 ySpeed) {
    
    // Define the shape
    b2PolygonShape * enemyShape = new b2PolygonShape();
    enemyShape->SetAsBox(xSize, ySize);
    size = b2Vec2(xSize * 2, ySize * 2);
    
    // Perform rest of initialization
    commonInit(enemyShape, world, xStart, yStart, xSpeed, ySpeed);
}

void Obstacle::commonInit(b2Shape * shape, b2World* world, float32 xStart,
                          float32 yStart, float32 xSpeed, float32 ySpeed) {
    
    // Set the type
    type = new int(NEUTRAL);
    
    // Define the fixture
    b2FixtureDef enemyFix;
    enemyFix.shape = shape;
    enemyFix.density = 1.0f;
    enemyFix.friction = 0;
    enemyFix.restitution = 0.15;
    
    // Define the platform
    b2BodyDef enemyDef;
    enemyDef.type = b2_dynamicBody;
    enemyDef.position.Set(xStart, yStart);
    enemyDef.angle = 0.0f;
    
    // Create the platform
    body = world->CreateBody(&enemyDef);
    body->CreateFixture(&enemyFix);
    body->SetUserData(type);
    
    // Define the initial speed
    b2Vec2 speed(xSpeed, ySpeed);
    body->SetLinearVelocity(speed);
    body->SetUserData(this);
    
    delete shape;
}

Obstacle::~Obstacle() {}

