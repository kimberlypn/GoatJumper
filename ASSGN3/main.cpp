#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <Box2D/Box2D.h>
#include <cstdlib>
#include "yse.hpp"
using namespace std;

// Window dimentions
const int WIDTH = 640, HEIGHT = 640;
// Initialize offsets for the square's position
float posnX = 0, posnY = 0;

// Global variables for the world
b2World* world;
b2Body* ground;
b2Body* box;
float32 timeStep = 1.0f / 60.0f;
// Iterations are a balance between accuracy and performance;
// these are the recomended values
int32 velocityIterations = 20;
int32 positionIterations = 3;

// Music player
YSE::sound sound;

// Renders rain droplets
void renderRain() {
    // Get the position of the droplets according to gravity
    world->Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = box->GetPosition();
    
    // Use two loops to draw the raindrops staggered
    for (int i = 2; i <= 10; i = i + 2) {
        for (int j = 100; j > -10; j = j - 2) {
            glColor3ub(61, 126, 229); // Set the color
            glVertex3f(i, j + position.y, 0.0); // Top left
            glVertex3f(i + 0.2, j + position.y, 0.0); // Bottom left
            glVertex3f(i + 0.2, j + 0.2 + position.y, 0.0); // Top right
            glVertex3f(i, j + 0.2 + position.y, 0.0); // Bottom right
        }
    }
    
    for (int i = 1; i <= 10; i = i + 2) {
        for (int j = 101; j > -10; j = j - 2) {
            glColor3ub(61, 126, 229); // Set the color
            glVertex3f(i, j + position.y, 0.0); // Top left
            glVertex3f(i + 0.2, j + position.y, 0.0); // Bottom left
            glVertex3f(i + 0.2, j + 0.2 + position.y, 0.0); // Top right
            glVertex3f(i, j + 0.2 + position.y, 0.0); // Bottom right
        }
    }
}

// Renders the objects in the window
void display(void) {
    // Clear the buffer to preset values
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_QUADS);
    // Render the rain
    renderRain();
    
    // Set the color of the character (represented as a square)
    glColor3ub(126, 168, 153);
    // Set the vertices
    glVertex3f(4.0 + posnX, 5.0 + posnY, 0.0); // Top left
    glVertex3f(5.0 + posnX, 5.0 + posnY, 0.0); // Bottom left
    glVertex3f(5.0 + posnX, 6.0 + posnY, 0.0); // Top right
    glVertex3f(4.0 + posnX, 6.0 + posnY, 0.0); // Bottom right
    glEnd();
    
    glFlush();
    glutPostRedisplay();
    // Swap buffers to ensure that only fully rendered frames are displayed
    glutSwapBuffers();
}

// Moves the character according to the keyboard input
void move(int key, int x, int y) {
    switch(key) {
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

// Creates the window
void createWindow() {
    // Set the window size
    glutInitWindowSize(WIDTH, HEIGHT);
    // Center the window in the middle of the screen
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
    // Set the window name
    glutCreateWindow ("Demo");
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
    world = new b2World(b2Vec2(gravity));
    
    b2BodyDef groundDef;
    // Make the ground a static body
    groundDef.type = b2_staticBody;
    // Set the starting position
    groundDef.position.Set(0.0f, -10.0f);
    // Set the starting angle
    groundDef.angle = 0;
    
    b2BodyDef boxDef;
    // Make the box a dynamic body
    boxDef.type = b2_dynamicBody;
    // Set the starting position
    boxDef.position.Set(0.0f, 4.0f);
    // Set the starting angle
    boxDef.angle = 0;
    
    // Make the actual bodies
    ground = world->CreateBody(&groundDef);
    box = world->CreateBody(&boxDef);
}

// Destroys the world
void destroyWorld() {
    // DestroyBody will delete the pointers
    world->DestroyBody(ground);
    world->DestroyBody(box);
    delete world;
}

// Initializes the sound playback
void initSound() {
    // Initialize the audio system
    YSE::System().init();
    
    // Load a sound in memory
    sound.create("drone.ogg", NULL, true);
    
    // Throw an error if the sound could not be laoded
    if (!sound.isValid()) {
        fprintf(stderr, "Audio file was not found.");
    }
}

// Closes everything that is still open once the game
// window has closed
void close() {
    // Clean up
    destroyWorld();
    // Close the sound system
    YSE::System().close();
}

int main(int argc, char **argv) {
    // Make sure things that need to be closed are closed
    atexit(close);
    // Initialize the sound
    initSound();
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
