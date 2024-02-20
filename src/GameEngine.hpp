#ifndef _GAME_
#define _GAME_

using namespace std;
#include <vector>
#include <iostream>
#include <stdlib.h>


// Necessary for cross reference resolution:
class GameObject;
class Boid;
class LeaderBoid;
class Tower;


// The game engine.
class GameEngine
{ 
    public:
        
        GameEngine();
        
        void update(long elapsedTime, int timeDifference);
        
        void display();
        
        void init();
        
        void resize(int width, int height);
        
        // Pauses or unpauses the game.
        void tooglePause();
        
        // Enables or disables debug mode.
        void toogleDebug();
        
        void createBoid();
        
        void destroyBoid();
        
        void setVisualizationMode(int mode) 
        {
            visualizationMode = mode;
        }
        
        // A list containing references to all objects that exist in the game space.
        // If an object is not listed here, it won't be updated neither displayed.
        std::vector<GameObject*> gameObjects;
        
        // A reference to all boids in the game, except the leader boid.
        std::vector<Boid*> boids;
        
        // A reference to the leader boid.
        LeaderBoid* leaderBoid;
        
        // A reference to the tower.
        Tower* tower;
        
    protected:      
        
         
        // Used to assign IDs to created boids.
        int firstAvailableBoidID;
        
        // The visualization mode;
        int visualizationMode;
        
        // Defines if the game is paused or playing.
        bool paused;

        // Enables or disables the display of debugging information.
        bool debugging;
        
        void showDebugMessage(const string msg);
        
        void debugGameObject(GameObject* g);
        
        void drawFloor();
};

#endif