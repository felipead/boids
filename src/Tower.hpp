#ifndef _TOWER_
#define _TOWER_

#include <string>
#include <sstream>
using namespace std;

#include "OpenGL.hpp"

#include "GameObject.hpp"

class Tower : public GameObject 
{
    public:
         
        float radius;
        float height;
         
        Tower(GameEngine* gameEngine, Vector& position, float radius, float height) : GameObject(gameEngine, position)
        {
            this->radius = radius;
            this->height = height;
        }
        
         
        virtual void display() 
        {        
            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
            glColor4f(1.0, 1.0, 1.0, 0.4);
            
            glPushMatrix();

            glTranslatef(position.x, position.y, position.z);            
            gluCylinder(quadric, radius, 0, height, 64, 64);
            
            glPopMatrix();
        }
        
        
        virtual void init()
        {
            quadric = gluNewQuadric();
            
            // Update this object boundaries
            boundaries.right = position.x + radius;
            boundaries.left = position.x - radius;
            boundaries.top = position.y + radius;
            boundaries.bottom = position.y - radius;
            boundaries.front = position.z + height;
            boundaries.back = position.z - height;
        }
        
        
        virtual string toString()
        {
            stringstream txt;
            txt << "Tower [ position=" << position.toString() << " ]";
            return txt.str();
        }
        
        
    private:
        
        GLUquadricObj *quadric;
};

#endif