using namespace std;
#include <iostream>

#include "OpenGL.hpp"
#include "GameEngine.hpp"


// The time in milliseconds between timer ticks
#define TIMER_MILLISECONDS 17  // Gives a 60 FPS frame-rate


// global variables
GameEngine gameEngine;
long previousTime;
long startTime;


static void resize(int width, int height)
{
    gameEngine.resize(width, height);
}


static void display(void)
{
    gameEngine.display();
}


static void update(int value) 
{
	// Set up the next timer tick (do this first)
    glutTimerFunc(TIMER_MILLISECONDS, update, 0);
    
    long currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    long elapsedTime = currentTime - startTime;    
    int timeDifference = (int) currentTime - previousTime;
    previousTime = currentTime;
    
    gameEngine.update(elapsedTime, timeDifference);
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 'Q':
            exit(0);
            break;

        case '+':
        case '=':
            // Creates a new boid.
            gameEngine.createBoid();
            break;

        case 'p':
        case 'P':
            // Pauses/unpauses the game
            gameEngine.tooglePause();
            break;

        case 'd':
        case 'D':
            // Toogle debugging messages
            gameEngine.toogleDebug();
            break;

        case '-':
        case '_':
            // Deletes, randomly, a boid from the flock.
            gameEngine.destroyBoid();
            break;
            
        case '1':
            // First visualization mode.
            gameEngine.setVisualizationMode(0);
            break;
        
        case '2':
            // Second visualization mode.
            gameEngine.setVisualizationMode(1);
            break;
    }

    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Boids");
        
    gameEngine.init();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glutTimerFunc(TIMER_MILLISECONDS, update, 0);
    
	// Initialize the time variables
	startTime = glutGet(GLUT_ELAPSED_TIME);
	previousTime = startTime;
    
    glutMainLoop();

    return EXIT_SUCCESS;
}