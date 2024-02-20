#ifndef _BOID_
#define _BOID_

using namespace std;
#include <string>
#include <sstream>

#include <cmath>

#include "OpenGL.hpp"

#include "GameEngine.hpp"
#include "GameObject.hpp"


#define SPEED_MEMORY_SIZE 15


class Boid : public GameObject
{
    public:
                
        // Creates a new boid with a given initial position and speed. 
        // The id is intendend to be the unique identifier of the boid within the game world.
        Boid(int id, GameEngine* gameEngine, Vector& initialPosition, Vector& initialSpeed) :
            GameObject(gameEngine, initialPosition, initialSpeed)
        {
            if (id == 0)
                throw "Boid ID can't be zero.";
            
            this->id = id;
            this->speedMemoryIndex = 0;
        }
        
        virtual void init();
        
        virtual void update(long elapsedTime, int timeDifference);
        
        virtual void display();
        
        virtual string toString()
        {
            stringstream txt;
            txt << "Boid [ id=" << id << ", position=" << position.toString() << ", speed=" << speed.toString() << " ]";
            return txt.str();
        }
        
        int getID() 
        {
            return id;
        }
        
        
    protected:
            
        // The boid unique identifier.
        int id;
        
        // This variable is used to set up the wing movement. It specifies
        // the current angle of the wings.
        int wingAngle;
        
        // This variable is used to set up the direction of the wings movement.
        // Zero or positive values will produce ascending movement;
        // negative values will produce descending movement.
        int wingDirection;
    
        
        Boid(int id, GameEngine* gameEngine) : GameObject(gameEngine)
        {        
            this->id = id;
            this->speedMemoryIndex = 0;
        }
        
        
        // Animate this boid wings.
        virtual void animateWings(int timeDifference);
        
        // Update the boundaries property of this boid, based on the current position.
        virtual void updateBoundaries();
        
        // Detect possible collisions with another objects, and calculates a speed
        // necessary to make a detour and avoid the collision. Returns the calculated
        // speed.
        virtual Vector detourObstacles(long elapsedTime, int timeDifference);
        
        // Draw the boid on the screen.
        static void drawBoid(Vector& position, Vector& speed, int wingAngle,
            float headColor[], float bodyColor[], float tailColor[], float wingColor[]);
            
    private:
        
        // A memory of n past speeds. Used to make the boid movement smoother.
        Vector speedMemory[SPEED_MEMORY_SIZE];
        
        // Current index in the speed memory array.
        int speedMemoryIndex;
        
        // Calculates the average speed, based on the speed memory.
        Vector averageSpeed();
};

#endif