#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <string>
#include <sstream>
using namespace std;

#include "OpenGL.hpp"
#include "Drawing.hpp"

#include "Vector.hpp"
#include "Box.hpp"

#include "GameEngine.hpp"

// An abstract class that represents any object on the game world.
class GameObject 
{
    public:
     
        // Updates this object logic state. It's called at each game cycle.
        // The first parameter represents the current game time, given in milleseconds.
        // The second parameter is the difference of the current time and the time measured
        // on the last call to this method.
        virtual void update(long elapsedTime, int timeDifference)
        {
            // Does nothing by default.
        }
        
        // This method purpose is to initialize the graphics capabilities of the object.
        // It should be called as soon as the OpenGL engine is initialized.
        virtual void init() 
        {
            // Does nothing by default.
        }
                
        // An abstract method intended to draw this object on the screen. 
        // This method is called at each game cycle, after the update method.
        virtual void display() = 0;
    
        // Returns a box that defines the x, y and z boundaries of the game object.
        virtual const Box& getBoundaries() 
        {
            return boundaries;
        }

        // Returns a vector that defines the object current position in the game space.
        virtual const Vector& getPosition()
        {
            return position;
        }
    
        virtual void setPosition(float x, float y, float z) 
        {
            position.setValues(x, y, z);
        }
    
        virtual void setPosition(const Vector& newPosition)
        {
            position.copyFrom(newPosition);
        }
        
        virtual const Vector& getSpeed()
        {
            return speed;
        }
        
        virtual void setSpeed(const Vector& newSpeed)
        {
            speed.copyFrom(newSpeed);
        }
        
        virtual string toString() 
        {
            stringstream txt;
            txt << "GameObject [ position=" << position.toString() << ", speed=" << speed.toString() << " ]";
            return txt.str();
        }
    
    protected:
    
        // The object current position in the 3 dimensional space. This position usually
        // is relative to the object's geometrical center. 
        // But it relies on each implementation.
        Vector position;

        // The object speed vector.
        Vector speed;

        // A box that defines the object current x, y and z boundaries.
        Box boundaries;
        
        // A reference to the game engine.
        GameEngine* gameEngine;
        

        GameObject(GameEngine* gameEngine) : position(), speed() 
        {
            if (gameEngine == NULL)
                throw "Game Engine can't be NULL";
            this->gameEngine = gameEngine; 
        }
        
        GameObject(GameEngine* gameEngine, const Vector& initialPosition) 
            : position(initialPosition), speed() 
        {
            if (gameEngine == NULL)
                throw "Game Engine can't be NULL";
            this->gameEngine = gameEngine; 
        }
        
        GameObject(GameEngine* gameEngine, const Vector& initialPosition, const Vector& initialSpeed)
            : position(initialPosition), speed(initialSpeed)
        {
            if (gameEngine == NULL)
                throw "Game Engine can't be NULL";
            this->gameEngine = gameEngine; 
        }
};

#endif