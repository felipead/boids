#include "GameEngine.hpp"

#include "GameObject.hpp"
#include "Boid.hpp"
#include "LeaderBoid.hpp"
#include "Tower.hpp"


GameEngine::GameEngine()
{
    paused = false;
    debugging = true;
    
    // The Leader Boid always contains ID = 0.
    firstAvailableBoidID = 1;
}


void GameEngine::init() 
{
    // General OpenGL settings:
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0, 0, 0, 0);			            	// Black Background
    glClearDepth(1.0);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Nice Perspective Calculations

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Game state variables
    visualizationMode = 1;

    // Creates initial game objects.
    
    // The leader boid
    leaderBoid = new LeaderBoid(this);
    gameObjects.push_back(leaderBoid);
    
    // The tower
    Vector towerBaseCenter(0, 0, 0);
    tower = new Tower(this, towerBaseCenter, 5, 75);
    gameObjects.push_back(tower);
    
    // Initialize all game objects.
    std::vector<GameObject*>::iterator i;
    for (i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {
        GameObject* gameObject = *i;
        gameObject->init();
    }
}


void GameEngine::update(long elapsedTime, int timeDifference) 
{
    if (paused) 
        return;
    
    // Debug information
    stringstream s;
    s << endl << "** NEW CYCLE [ elapsedTime=" << elapsedTime 
      << ", timeDifference=" << timeDifference << " ] **";
    showDebugMessage(s.str());
    
    // Updates all game objects.
    std::vector<GameObject*>::iterator i;
    for (i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {                
        GameObject* gameObject = *i;
        
        // Debug information
        debugGameObject(gameObject);                
        gameObject->update(elapsedTime, timeDifference);
    }
}


void GameEngine::display()
{                        
    glLoadIdentity();
    
    Vector pos = leaderBoid->getPosition();
    
    switch (visualizationMode) 
    {
        case 0:            
            gluLookAt(0, 0, tower->height + 20, // eye position
                      pos.x, pos.y, pos.z,  // center position
                      0, 0, 1);  // up vector
            break;
    
        case 1:
            gluLookAt(-50, -50, 50,  // eye position
                      pos.x, pos.y, pos.z,   // center position
                      0, 0, 1);  // up vector
            break;
            
        default:
            throw "Invalid visualization mode.";
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glNormal3f(0, 0, 1);

    // Display the floor
    drawFloor();
        
    // Displays all game objects.
    std::vector<GameObject*>::iterator i;
    for (i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {                
        GameObject* gameObject = *i;
        gameObject->display();
    }
    
    glutSwapBuffers();
}


void GameEngine::drawFloor()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
    const int z = 0;
    const int floorLength = 500;
    const int squareSize = 20;

    glPushMatrix();
        glBegin(GL_QUADS);
        for (int x = -floorLength; x < floorLength; x += squareSize) {
            for (int y = -floorLength; y < floorLength; y += squareSize) {
                int n = ((x+y)/squareSize) % 2;
                if (n == 0)
                    glColor3f(0.8, 0.8, 0.8); // White
                else
                    glColor3f(0.5, 0.5, 0.5); // Gray
        
                glVertex3f(x, y, z);
                glVertex3f(x, y + squareSize, z);
                glVertex3f(x + squareSize, y + squareSize, z);
                glVertex3f(x + squareSize, y, z);
            }
        }
	    glEnd();	
    glPopMatrix();
}


void GameEngine::resize(int width, int height)
{
    // Projection matrix
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	// The aspect ratio of the window
    float aspectRatio = (height > 0)? width/height : width;

	gluPerspective(60, aspectRatio, 0.1, 500);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Pauses or unpauses the game.
void GameEngine::tooglePause() 
{
    if (paused) {
        showDebugMessage("Game Unpaused");
        paused = false;
    }
    else {
        showDebugMessage("Game Paused");
        paused = true;
    }
}


void GameEngine::toogleDebug()
{
    debugging = !debugging;
}


void GameEngine::createBoid()
{
    // TODO: allocate random initial coordinates
    // http://www.cplusplus.com/reference/clibrary/cstdlib/rand/
    Vector initialPosition(10, 10, 20);
    Vector initialSpeed(0.001, 0.001, 0.001);
    
    Boid* boid = new Boid(firstAvailableBoidID, this, initialPosition, initialSpeed);
    boid->init();
    
    stringstream s;
    s << "Created a new boid with id " << boid->getID();
    showDebugMessage(s.str());
    
    firstAvailableBoidID++;
    
    gameObjects.push_back(boid);
    boids.push_back(boid);
}


// Selects randomly a boid from the flock and destroy it.
void GameEngine::destroyBoid()
{
    int size = boids.size();
    if (size > 0) {
        int randomIndex = rand() % size;
        
        Boid* boidToDestroy = boids[randomIndex];
        boids.erase(boids.begin() + randomIndex);
        
        std::vector<GameObject*>::iterator i;
        for (i = gameObjects.begin(); i != gameObjects.end(); ++i)
        {            
            GameObject* gameObject = *i;
            if (gameObject == boidToDestroy) {
                gameObjects.erase(i);
                break;
            }
        }
        
        stringstream s;
        s << "Destroyed a boid with id " << boidToDestroy->getID();
        showDebugMessage(s.str());
        
        delete boidToDestroy;
    }
}


void GameEngine::showDebugMessage(const string msg)
{
    if (debugging) {
        cout << msg << endl;
    }
}


void GameEngine::debugGameObject(GameObject* g)
{
    if (debugging) {
        cout << g->toString() << endl;
    }
}