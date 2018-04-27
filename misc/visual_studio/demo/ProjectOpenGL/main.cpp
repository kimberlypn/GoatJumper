#include "Header.h"

const int WIDTH = 640, HEIGHT = 640;

b2World * world;
b2Body* ground;
b2Vec2 groundPosn;
b2Body * player;
b2Vec2 playerPosn;
b2Vec2 * velocity;

const b2Vec2 * rightForce = new b2Vec2(150.0f, 0.0f);
const b2Vec2 * leftForce = new b2Vec2(-150.0f, 0.0f);
const b2Vec2 * jumpImpulse = new b2Vec2(0.0f, 2000.0f);

// NOT the same as framerate (ultimately)
float32 timeStep = 1.0f / 60.0f;

// iterations are balance between accuracy and performance.  These are recomended values.
int32 velocityIterations = 8;
int32 positionIterations = 3;

void progressWorld() {
	world->Step(timeStep, velocityIterations, positionIterations);
	playerPosn = player->GetPosition();
	groundPosn = ground->GetPosition();
}
// Renders a character in the center of the window
void display(void) {
	progressWorld();

	// Clear the buffer to preset values
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the vertices
	glBegin(GL_QUADS);

	glColor3ub(126, 168, 153); // Set the color
	glVertex3f(4.0 + playerPosn.x, 4.0 + playerPosn.y, 0.0); // Top left
	glVertex3f(6.0 + playerPosn.x, 4.0 + playerPosn.y, 0.0); // Bottom left
	glVertex3f(6.0 + playerPosn.x, 6.0 + playerPosn.y, 0.0); // Top right
	glVertex3f(4.0 + playerPosn.x, 6.0 + playerPosn.y, 0.0); // Bottom right

	glEnd();

	glBegin(GL_QUADS);

	glColor3ub(0, 0, 0); // Set the color
	glVertex3f(0.0 + groundPosn.x, 4.5 + groundPosn.y, 0.0); // Top left
	glVertex3f(10.0 + groundPosn.x, 4.5 + groundPosn.y, 0.0); // Bottom left
	glVertex3f(10.0 + groundPosn.x, 5.5 + groundPosn.y, 0.0); // Top right
	glVertex3f(0.0 + groundPosn.x, 5.5 + groundPosn.y, 0.0); // Bottom right

	glEnd();

	glFlush();
	glutPostRedisplay();
	// Swap buffers to ensure that only fully rendered frames are displayed
	glutSwapBuffers();

	Sleep(10);
}

// Moves the character according to the keyboard input
void move(int key, int x, int y) {
	switch (key) {
		// Move the character up
	case GLUT_KEY_UP:
		velocity = new b2Vec2(player->GetLinearVelocity().x, 0.0f);
		player->SetLinearVelocity(*velocity);
		player->ApplyForceToCenter(*jumpImpulse, true);
		break;
		// Move the character to the right
	case GLUT_KEY_RIGHT:
		player->ApplyForceToCenter(*rightForce, true);
		break;
		// Move the character down
	case GLUT_KEY_DOWN:
		break;
		// Move the character to the left
	case GLUT_KEY_LEFT:
		player->ApplyForceToCenter(*leftForce, true);
		break;
	}
	glutPostRedisplay();
}

// Creates the window
void createWindow() {
	// Set the window size
	glutInitWindowSize(WIDTH, HEIGHT);
	// Center the window in the middle of the screen
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
	// Set the window name
	glutCreateWindow("Demo");
	// Set the window's background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// Set the projection matrix in order to draw vertices
	glMatrixMode(GL_PROJECTION);
	// Set the matrix as the identity matrix
	glLoadIdentity();
	// Set up a 10x10x2 viewing world
	glOrtho(0, 10, 0, 10, -1, 1);
}

// Creates a world
void createWorld() {
	// Initialize the world with gravity
	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);

	// defining the ground shape
	b2PolygonShape groundShape;
	groundShape.SetAsBox(5.0f, 0.5f);

	// defining the ground fixture
	b2FixtureDef groundFix;
	groundFix.shape = &groundShape;
	groundFix.density = 1.0f;
	groundFix.friction = 0.25f;

	// defining the platform
	b2BodyDef groundDef;
	groundDef.type = b2_staticBody;
	groundDef.position.Set(0.0f, -5.0f);
	groundDef.angle = 0.0f;
	ground = world->CreateBody(&groundDef);
	ground->CreateFixture(&groundFix);

	// defining the player shape
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
	playerDef.position.Set(0.0f, 4.0f);
	playerDef.angle = 0.0f;
	playerDef.fixedRotation = true;
	player = world->CreateBody(&playerDef);
	player->CreateFixture(&playerFix);
}

void closeThings() {
	delete world;
}

int main(int argc, char **argv) {
	atexit(closeThings);

	// Initialize the GLUT library
	glutInit(&argc, argv);
	// Create the window
	createWindow();
	// Set up the world
	createWorld();
	// Render the character
	glutDisplayFunc(display);
	// Read keyboard inputs
	glutSpecialFunc(move);
	// Start an event processing loop
	glutMainLoop();

	return 0;
}