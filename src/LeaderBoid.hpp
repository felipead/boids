#ifndef _LEADER_BOID_
#define _LEADER_BOID_

using namespace std;
#include <string>
#include <sstream>

#include <math.h>
#define PI 3.14159265

#include "Boid.hpp"


class LeaderBoid : public Boid
{
    public:
            
        // The leader boid has id = 0.        
        LeaderBoid(GameEngine* gameEngine) : Boid(0, gameEngine)
        {
            radius = 100;
                         
            position.x = radius;
            position.y = 0;
            position.z = 30;
        }

        
        virtual string toString()
        {
            stringstream txt;
            txt << "LeaderBoid [ position=" << position.toString() << ", speed=" << speed.toString() << " ]";
            return txt.str();
        }

        virtual void display();
        
        virtual void update(long elapsedTime, int timeDifference);
        
        virtual void init();
        
    private:
    
        // The radius of the leader boid circular movement around the (0, 0, z) line.
        int radius;

};

#endif
