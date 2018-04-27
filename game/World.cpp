#include "World.hpp"

World::World() {}

World::World(ISoundListener* sl) {
    this->sl = sl;
}

World::~World() {
    // Clean up pointers; sl pointer gets cleaned up in GameController
    if (world != NULL)
        delete world;
    if (player != NULL)
        delete player;
}

bool World::init(int x, int y) {
    // Create a world with gravity
    timeStep = 1.0f / 20.0f;
    b2Vec2 gravity(0.0f, -15.0f);
    world = new b2World(gravity);
    world->SetContactListener(this);
    
    // Create the player
    player = new Player(world, 20, 20);
    objects[player] = "assets/images/player1.png";
    
    // Create a platform
    objects[new Platform(world, 20, 10, speed / 2)] =
    "assets/images/platform.png";
    
    // Scale the window dimensions
    width = x / 10;
    height = y / 10;
    
    // Add side boundaries
    makeBoundaries();
    
    //Start background music
    sl->playBackground();
    
    return true;
}

void World::tick() {
    if (!gameOver) {
        // Advance the world by a tick
        world->Step(timeStep, velocityIterations, positionIterations);
        time++;
        
        // Increase the platform speed every 100 ticks
        if ((time % 200) == 0)
            speed += 0.1;
        
        // Change the map every 1000 ticks
        if ((time % 1000) == 0) {
            mapType = (mapType == WorldState::NUM_MAPS) ? 1 : mapType + 1;
        }
        
        // Generate new platforms and enemies
        platGen();
        enemyGen();
        
        // Delete any objects that have gone out of bounds
        checkForDeletions();
    }
}

WorldState* World::getState() {
    WorldState* state = new WorldState;
    
    // Convert the GameObjs into ObjStates
    for (auto itr = objects.begin(); itr != objects.end(); itr++) {
        GameObj* obj = itr->first;
        
        // Add the object
        b2Vec2 posn = obj->getBody()->GetPosition();
        b2Vec2 size = obj->getSize();
        
        string img = itr->second;
        state->addState(img, posn.x, posn.y, size.y, size.x);
    }
    // Set the platform score
    state->setPlatformScore(platformScore);
    
    // Set the gameOver flag
    state->setGameOver(gameOver);
    
    // Setting the current map
    state->setMap(mapType);
    
    return state;
}

void World::command(int command) {
    switch (command) {
            // Move the player to the left
        case LEFT:
            player->pushLeft();
            if (forward)
                objects[player] = "assets/images/player2.png";
            forward = false;
            break;
            // Move the player to the right
        case RIGHT:
            player->pushRight();
            if (!forward)
                objects[player] = "assets/images/player1.png";
            forward = true;
            break;
            // Make the player jump
        case JUMP:
            // Only allow the player to single or double jump
            if (jumpsLeft > 0) {
                player->jump();
                jumpsLeft--;
                // Play a jump sound effect
                sl->playJumpSFX(jumpsLeft);
            }
            break;
    }
}

void World::reset() {
    // Reset the score
    platformScore = 0;
    
    // Reset the game over flag
    gameOver = false;
    
    // Reset the time and map
    time = 0;
    mapType = 1;
    
    // Clear the game objects map
    for (auto itr = objects.begin(); itr != objects.end(); itr++) {
        world->DestroyBody(itr->first->getBody());
        delete (itr->first);
    }
    objects.clear();
    
    // Re-initialize the world
    init(width * 10, height * 10);
}

void World::makeBoundaries() {
    // Define the shape
    b2PolygonShape boundaryShape;
    boundaryShape.SetAsBox(1, height);
    
    // Define the fixture
    b2FixtureDef boundaryFix;
    boundaryFix.shape = &boundaryShape;
    boundaryFix.density = 1.0f;
    boundaryFix.friction = 0;
    
    // Define the left boundary
    b2BodyDef boundaryDef;
    boundaryDef.type = b2_staticBody;
    boundaryDef.position.Set(-1, height / 2);
    boundaryDef.angle = 0.0f;
    boundaryDef.fixedRotation = true;
    b2Body * leftBoundary = world->CreateBody(&boundaryDef);
    leftBoundary->CreateFixture(&boundaryFix);
    
    // Switch definition to right boundary and define
    boundaryDef.position.Set(width + 1, height / 2);
    b2Body * rightBoundary = world->CreateBody(&boundaryDef);
    rightBoundary->CreateFixture(&boundaryFix);
}

void World::platGen() {
    if ((time % (int)(650 / speed)) == 0) {
        objects[new Platform(world, width * 1.25,
                             height * (random() * 2 / 3 + 1 / 10), speed)]
        = "assets/images/platform.png";
    }
}

void World::enemyGen() {
    switch (mapType) {
        case WorldState::CITY:
            if (time % (int)(100 / speed) == 0) {
                string address;
                switch ((int)(random() * 3)) {
                    case 0:
                        address = "assets/images/trash1.png";
                        break;
                    case 1:
                        address = "assets/images/trash2.png";
                        break;
                    case 2:
                        address = "assets/images/trash3.png";
                        break;
                }
                float32 size = 1 * random() + 1.5;
                float32 xStart = width * random();
                float32 yStart = height * 1.25;
                objects[new Obstacle(world, size, xStart, yStart, -speed, 0)]
                = address;
            }
            break;
        case WorldState::VALLEY:
            if (time % (int)(750 / speed) == 0) {
                float32 xStart = width * random() / 3;
                float32 yStart = -height / 5;
                float32 xSpeed = 10 + 10 * random();
                switch ((int)(random() * 2)) {
                    case 0:
                        objects[new Enemy(world, 9, 15, xStart, yStart, xSpeed,
                                          25)] = "assets/images/deer1.png";
                        break;
                    case 1:
                        xStart = width * (1 - random() / 3);
                        yStart = -height / 5;
                        xSpeed = -10 - 10 * random();
                        objects[new Enemy(world, 9, 15, xStart, yStart, xSpeed,
                                          25)] = "assets/images/deer2.png";
                        break;
                }
            }
            break;
        case WorldState::DESERT:
            if (time % (int)(350 / speed) == 0) {
                objects[new Obstacle(world, 3, 5,
                                     width * 1, height ,
                                     -10 - random() * 10,
                                     10 * (random() - 0.5))]
                = "assets/images/mummy.png";
            }
            break;
    }
}

float32 World::random() {
    return ((float) rand()) / RAND_MAX;
}

void World::checkForDeletions() {
    vector<GameObj*> toRemove;
    
    // Add all objects that are out of bounds to the toRemove vector
    for (auto itr = objects.begin(); itr != objects.end(); itr++) {
        GameObj* obj = itr->first;
        if (outOfBounds(obj))
            toRemove.push_back(obj);
    }
    
    // Destroy the out-of-bound objects
    while (toRemove.size() > 0) {
        if (toRemove.at(0)->getID() == GameObj::PLAYER)
            gameOver = true;
        //cout << "Destroying: " << toRemove.at(0)->getID() << endl;
        world->DestroyBody(toRemove.at(0)->getBody());
        objects.erase(toRemove.at(0));
        toRemove.erase(toRemove.begin());
    }
}

bool World::outOfBounds(GameObj* obj) {
    b2Vec2 posn = obj->getBody()->GetPosition();
    return (posn.x < -width / 2 || posn.y < -height / 2);
}

void World::BeginContact(b2Contact* contact) {
    // Pull fixtures
    GameObj* body1 = (GameObj*) contact->GetFixtureA()->GetBody()->GetUserData();
    GameObj* body2 = (GameObj*) contact->GetFixtureB()->GetBody()->GetUserData();
    //b2Vec2 normal = contact->GetManifold()->localNormal;
    
    // If either has no body (nullptr), then do nothing
    if (body1 == nullptr || body2 == nullptr) {
        return;
    }
    
    // Grab the integer ID for each body
    int body1Ptr = body1->getID();
    int body2Ptr = body2->getID();
    
    // If the player is in body 2, switch it with body 1
    if (body2Ptr == GameObj::PLAYER) {
        GameObj * tempBody = body1;
        body1 = body2;
        body2 = tempBody;
    }
    
    // If the player is involved in the contact
    if (body1Ptr == GameObj::PLAYER) {
        switch (body2Ptr) {
            case GameObj::PLATFORM:// Restock the player's jumps
                jumpsLeft = MAX_JUMPS;
                
                // Increment the platform score if applicable
                if (!((Platform*)body2)->getLanded())
                    platformScore = platformScore + 1;
                // Set the landed flag to true
                ((Platform*)body2)->setLanded(true);
                break;
            case GameObj::ENEMY:
                body1
                ->getBody()
                ->SetLinearVelocity(
                                    b2Vec2(
                                           body1->getBody()->GetLinearVelocity().x
                                           + body2->getBody()->GetLinearVelocity().x * 4,
                                           body1->getBody()->GetLinearVelocity().y));
                break;
            case GameObj::NEUTRAL:
                if ((body1
                     ->getBody()
                     ->GetPosition().y - body2->getBody()->GetPosition().y)
                    >= ((body1->getSize().y / 2)
                        + (body2->getSize().y / 2)) * 0.75) {
                        jumpsLeft = MAX_JUMPS;
                    }
        }
    }
}

void World::EndContact(b2Contact* contact) {
    /* Handle end event; needed for Box2D */
}

void World::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    /* Handle pre-solve event; needed for Box2D */
}

void World::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    /* Handle post-solve event; needed for Box2D */
}

