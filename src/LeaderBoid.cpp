#include "LeaderBoid.hpp"

void LeaderBoid::init()
{
    Boid::updateBoundaries();
}

void LeaderBoid::display()
{
    float headColor[] = { 0.65, 0.65, 0.65, 1.0 };
    float bodyColor[] = { 1.0, 0, 0, 1.0 };
    float tailColor[] = { 0.2, 0.2, 0.2, 0.5 };
    float wingColor[] = { 1.0, 1.0, 1.0, 1.0 };
    
    Boid::drawBoid(position, speed, wingAngle, headColor, bodyColor, tailColor, wingColor);
}

void LeaderBoid::update(long elapsedTime, int timeDifference)
{
    // This implementation assumes that the leader boid always rotates arround the z axis,
    // thus making a previsible circular movement.
    // TODO: implement the random walk algorithm for the leader boid movement.

    // Don't let the boid leave the orbit.
    if (position.x > radius)
        position.x = radius;
    else if (position.x < -radius)
        position.x = -radius;                
    if (position.y > radius)
        position.y = radius;
    else if (position.y < -radius)
        position.y = -radius;
    
    float angularSpeed = 0.0006f;
    
    // From http://en.wikipedia.org/wiki/Circular_motion
    Vector normal(0, 0, 1);
    normal.z *= angularSpeed;
    speed = position.crossProduct(normal);
        
    // Updates the position according to the object's speed.
    position.x += speed.x * timeDifference;
    position.y += speed.y * timeDifference;
    position.z += speed.z * timeDifference;
    
    // Update this object boundaries
    Boid::updateBoundaries();
    
    Boid::animateWings(timeDifference);
}