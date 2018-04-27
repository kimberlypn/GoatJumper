#include <iostream>
#include <Box2D.h>
#include <stdio.h>
#include <GL/glut.h>

// Window dimentions
int width = 640, height = 640;
// Initialize offsets for the square's position
float posnX = 0, posnY = 0;

// Renders a character in the center of the window
void display1(void) {
	// Clear the buffer to preset values
	glClear(GL_COLOR_BUFFER_BIT);
	// Set the color
	glColor3ub(126, 168, 153);
	// Begin drawing the vertices
	glBegin(GL_QUADS);
	// Top left
	glVertex3f(4.0 + posnX, 5.0 + posnY, 0.0);
	// Bottom left
	glVertex3f(5.0 + posnX, 5.0 + posnY, 0.0);
	// Top right
	glVertex3f(5.0 + posnX, 6.0 + posnY, 0.0);
	// Bottom right
	glVertex3f(4.0 + posnX, 6.0 + posnY, 0.0);
	// Stop drawing the vertices
	glEnd();
	// Run the GL commands
	glFlush();
	glutPostRedisplay();
	// Swap buffers to ensure that only fully rendered frames are displayed
	glutSwapBuffers();
}

// Moves the character according to the keyboard input
void move1(int key, int x, int y) {
	switch (key) {
		// Move the character up
	case GLUT_KEY_UP:
		// Check if the character is at the edge of the screen
		if (posnY != 4) {
			posnY = posnY + 1;
		}
		glutPostRedisplay();
		break;
		// Move the character to the right
	case GLUT_KEY_RIGHT:
		// Check if the character is at the edge of the screen
		if (posnX != 5) {
			posnX = posnX + 1;
		}
		glutPostRedisplay();
		break;
		// Move the character down
	case GLUT_KEY_DOWN:
		// Check if the character is at the edge of the screen
		if (posnY != -5) {
			posnY = posnY - 1;
		}
		glutPostRedisplay();
		break;
		// Move the character to the left
	case GLUT_KEY_LEFT:
		// Check if the character is at the edge of the screen
		if (posnX != -4) {
			posnX = posnX - 1;
		}
		glutPostRedisplay();
		break;
	}
}

void makeAWorld1() {
	// making world, with 2D vector for gravity
	b2Vec2 gravVect(0.0f, -10.0f);
	b2World world(gravVect);

	// making body definitions
	b2BodyDef groundDef;
	groundDef.type = b2_staticBody; // makes it a static body
	groundDef.position.Set(0.0f, -4.0f); // sets starting position
	groundDef.angle = 0; // sets starting angle

	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody; // makes it a dynamic body
	boxDef.position.Set(0.0f, 10.0f); // sets starting position
	boxDef.angle = 0; // sets starting angle

	// making the actual bodies
	b2Body * ground = world.CreateBody(&groundDef);
	b2Body * box = world.CreateBody(&boxDef);

	// giving them shapes and physical properties
	b2PolygonShape groundBox; // declaring a shape
	groundBox.SetAsBox(25.0f, 2.0f); //making it a 50x4 box
	ground->CreateFixture(&groundBox, 0.0f); // adds fixture, from shape and 0 density (static)

	b2PolygonShape boxBox; // declaring a shape
	boxBox.SetAsBox(2.0f, 2.0f); // making it a 2x2 box
	b2FixtureDef boxFixDef; // declaring a fixture definition
	boxFixDef.shape = &boxBox; // setting shape
	boxFixDef.density = 1.0f; // setting density
	boxFixDef.friction = 0.5; // setting friction
	box->CreateFixture(&boxFixDef); // adds fixture, from the fixture definition

	// starting up the simulation

	// NOT the same as framerate (ultimately, or shouldn't be at least)
	float32 timeStep = 1.0f / 60.0f;

	// iterations are balance between accuracy and performance.  These are recomended values.
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	// should show box dropping until it hits ground and stops
	for (int32 i = 0; i < 100; ++i) {
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = box->GetPosition();
		float32 angle = box->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// cleaning up
	world.DestroyBody(ground);
	world.DestroyBody(box);
}

int main1(int argc, char **argv) {

	// Box2D stuff
	{
		makeAWorld1();
	}

	system("pause");

	// OpenGL stuff
	{
		// Initialize the GLUT library
		glutInit(&argc, argv);
		// Set the window size
		glutInitWindowSize(width, height);
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
		// Render the character
		glutDisplayFunc(display1);
		// Read keyboard inputs
		glutSpecialFunc(move1);
		// Start an event processing loop
		glutMainLoop();
	}

	return 0;
}