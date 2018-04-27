#include "Player.hpp"

Player::Player(b2World* world, float32 xStart, float32 yStart) {
    // Set the type
    type = new int(PLAYER);
    
    // Define the shape
    b2PolygonShape playerShape;
    playerShape.SetAsBox(4, 4);
    size = b2Vec2(8, 8);
    
    // Define the fixture
    b2FixtureDef playerFix;
    playerFix.shape = &playerShape;
    playerFix.density = 1.0f;
    playerFix.friction = 0.25f;
    
    // Define the player
    b2BodyDef playerDef;
    playerDef.type = b2_dynamicBody;
    playerDef.position.Set(xStart, yStart);
    playerDef.angle = 0.0f;
    playerDef.fixedRotation = true;
    
    // Create the player
    body = world->CreateBody(&playerDef);
    body->CreateFixture(&playerFix);
    body->SetUserData(this);
}

Player::~Player() {}

b2Body* Player::getBody() const {
    return body;
}

bool Player::jump() {
    b2Vec2 velocity(body->GetLinearVelocity().x, 20);
    body->SetLinearVelocity(velocity);
    
    return true;
}

void Player::pushLeft() {
    b2Vec2 velocity(body->GetLinearVelocity().x - 1,
                    body->GetLinearVelocity().y);
    body->SetLinearVelocity(velocity);
}

void Player::pushRight() {
    b2Vec2 velocity(body->GetLinearVelocity().x + 1,
                    body->GetLinearVelocity().y);
    body->SetLinearVelocity(velocity);
}

