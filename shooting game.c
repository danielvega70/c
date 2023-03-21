#include <iostream>
#include <cmath>
#include <GL/glut.h>

// Constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const float PLAYER_SPEED = 0.1f;

// Player variables
float playerX = 0.0f;
float playerY = 0.0f;
float playerZ = 0.0f;
float playerRotY = 0.0f;

// Projectile variables
bool isProjectileActive = false;
float projectileX = 0.0f;
float projectileY = 0.0f;
float projectileZ = 0.0f;
float projectileSpeed = 0.5f;
float projectileRotY = 0.0f;

// Camera variables
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;

// Function to initialize OpenGL
void initOpenGL() {
    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            playerX -= sin(playerRotY * M_PI / 180.0) * PLAYER_SPEED;
            playerZ -= cos(playerRotY * M_PI / 180.0) * PLAYER_SPEED;
            break;
        case 's':
            playerX += sin(playerRotY * M_PI / 180.0) * PLAYER_SPEED;
            playerZ += cos(playerRotY * M_PI / 180.0) * PLAYER_SPEED;
            break;
        case 'a':
            playerRotY -= 5.0f;
            break;
        case 'd':
            playerRotY += 5.0f;
            break;
        case ' ':
            if (!isProjectileActive) {
                isProjectileActive = true;
                projectileX = playerX;
                projectileY = playerY + 0.5f;
                projectileZ = playerZ;
                projectileRotY = playerRotY;
            }
            break;
    }
}

// Function to handle window resizing
void handleResize(int w, int h) {
    // Set the viewport to the entire window
    glViewport(0, 0, w, h);
    // Set the perspective projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 1.0f, 1000.0f);
}

// Function to draw the player
void drawPlayer() {
    glPushMatrix();
    // Translate the player to its position
    glTranslatef(playerX, playerY, playerZ);
    // Rotate the player based on its rotation
    glRotatef(playerRotY, 0.0f, 1.0f, 0.0f);
    // Draw the player as a cube
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Function to draw the projectile
void drawProjectile() {
    if (isProjectileActive) {
        glPushMatrix();
        // Translate the projectile to its position
        glTranslatef(projectileX, projectileY, projectileZ);
        // Rotate
