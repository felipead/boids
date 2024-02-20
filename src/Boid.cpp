#include "Boid.hpp"

#include "LeaderBoid.hpp"
#include <vector>
#include <iostream>
using namespace std;


void Boid::init()
{
    updateBoundaries();
}


void Boid::update(long elapsedTime, int timeDifference)
{
    
    // Calculates the speed necessary to detour obstacles.
    Vector detourSpeed = detourObstacles(elapsedTime, timeDifference);

    // Calculates the target speed. Every boid tries to follow the leader.
    
    LeaderBoid* leaderBoid = gameEngine->leaderBoid;
    Vector leaderBoidSpeed = leaderBoid->getSpeed();
    Vector leaderBoidPosition = leaderBoid->getPosition();
    
    const float targetSpeedModule = leaderBoidSpeed.getMagnitude() * 0.08;
    Vector targetDirection = (leaderBoidPosition - position);
    targetDirection.normalize();
    
    Vector targetSpeed;    
    targetSpeed.x = targetDirection.x * targetSpeedModule * timeDifference;
    targetSpeed.y = targetDirection.y * targetSpeedModule * timeDifference;
    targetSpeed.z = targetDirection.z * targetSpeedModule * timeDifference;    

    // Calculates the average speed, based on n past speeds.    
    Vector avgSpeed = averageSpeed();


    // The actual speed is the sum of the target speed, the detour speed and the average past speed.
    
    speed.setValues(0, 0, 0);
    
    float detourWeight = 3.0;
    float targetWeight = 2.0;
    float avgWeight = 1.0;
    float totalWeight = detourWeight + targetWeight + avgWeight;

    speed.x = (detourWeight * detourSpeed.x) + (targetWeight * targetSpeed.x) + (avgWeight * avgSpeed.x);
    speed.y = (detourWeight * detourSpeed.y) + (targetWeight * targetSpeed.y) + (avgWeight * avgSpeed.y);
    speed.z = (detourWeight * detourSpeed.z) + (targetWeight * targetSpeed.z) + (avgWeight * avgSpeed.z);
    speed.x /= totalWeight;
    speed.y /= totalWeight;
    speed.z /= totalWeight;    
    
    
    // Updates the position according to the object's speed.
    position.x += speed.x * timeDifference;
    position.y += speed.y * timeDifference;
    position.z += speed.z * timeDifference;
    
    
    speedMemory[speedMemoryIndex].copyFrom(speed);
    speedMemoryIndex = (speedMemoryIndex + 1) % SPEED_MEMORY_SIZE;
    
    
    updateBoundaries();    
    animateWings(timeDifference);
}


void Boid::display()
{
    float headColor[] = { 0.65, 0.65, 0.65, 0.5 };
    float bodyColor[] = { 0, 0, 1.0, 1.0 };
    float tailColor[] = { 0.2, 0.2, 0.2, 0.5 };
    float wingColor[] = { 1.0, 1.0, 1.0, 1.0 };
    
    Vector avgSpeed = averageSpeed();
    
    Boid::drawBoid(position, avgSpeed, wingAngle, headColor, bodyColor, tailColor, wingColor);
}


void Boid::updateBoundaries()
{
    const float width = 10;
    const float height = 10;
    const float depth = 10;
    boundaries.right = position.x + width;
    boundaries.left = position.x - width;
    boundaries.top = position.y + height;
    boundaries.bottom = position.y - height;
    boundaries.front = position.z + depth;
    boundaries.back = position.z - depth;
}


Vector Boid::averageSpeed()
{
    Vector averageSpeed;
    int n = 0;
    for (int i = 0; i < SPEED_MEMORY_SIZE; i++)
    {
        // Only count non-zero speeds.
        if (!speedMemory[i].isZero())
        {
            averageSpeed.x += speedMemory[i].x;
            averageSpeed.y += speedMemory[i].y;
            averageSpeed.z += speedMemory[i].z;
            n++;
        }
    }
    
    n = (n == 0? 1 : n);
    averageSpeed.x /= (float)n;
    averageSpeed.y /= (float)n;
    averageSpeed.z /= (float)n;
    
    return averageSpeed;
}


Vector Boid::detourObstacles(long elapsedTime, int timeDifference)
{
    const float accelerationModule = 0.001;
    
    Vector detourSpeed(0, 0, 0);
    
    // This boid boundaries.
    Box A = boundaries;
    
    // For each object in the game space, verifies a possible collision.
    std::vector<GameObject*>::iterator i;    
    for (i = gameEngine->gameObjects.begin(); i != gameEngine->gameObjects.end(); ++i)
    {  
        GameObject* gameObject = (*i);
        if (gameObject == this)
            continue;
        
        Box B = gameObject->getBoundaries();

        bool xIntersection = false;
        bool leftIntersection = false;
        bool rightIntersection = false;

        // Checks for intersections in the x axis.
        if (A.left <= B.left && A.right <= B.right && B.left <= A.right) {
            xIntersection = true;
            leftIntersection = true;
        }
        else if (A.left >= B.left && A.right <= B.right) {
            xIntersection = true;
        }
        else if (A.left >= B.left && A.right >= B.right && A.left <= B.right) {
            xIntersection = true;
            rightIntersection = true;
        }

        bool yIntersection = false;
        bool topIntersection = false;
        bool bottomIntersection = false;

        // Checks for intersections in the y axis.
        if (A.top >= B.top && A.bottom >= B.bottom && A.bottom <= B.top) {
            yIntersection = true;
            topIntersection = true;
        }
        else if (A.top <= B.top && A.bottom >= B.bottom) {
            yIntersection = true;
        }
        else if (A.top <= B.top && A.bottom <= B.bottom && A.top >= B.bottom) {
            yIntersection = true;
            bottomIntersection = true;
        }

        bool zIntersection = false;
        bool backIntersection = false;
        bool frontIntersection = false;

        // Checks for intersections in the z axis.
        if (A.back <= B.back && A.front <= B.front && B.back <= A.front) {
            zIntersection = true;
            backIntersection = true;
        }
        else if (A.back >= B.back && A.front <= B.front) {
            zIntersection = true;
        }
        else if (A.back >= B.back && A.front >= B.front && A.back <= B.front) {
            zIntersection = true;
            frontIntersection = true;
        }

        // A collision only occurs when there is intersection in the x, y and z axis.
        if (xIntersection && yIntersection && zIntersection) 
        {
            Vector accelerationDirection(0,0,0);
            
            if (leftIntersection)
                accelerationDirection.x = -1;
            else if (rightIntersection)
                accelerationDirection.x = 1;
            
            if (bottomIntersection)
                accelerationDirection.y = -1;            
            else if (topIntersection)
                accelerationDirection.y = 1;
            
            if (backIntersection)
                accelerationDirection.z = -1;
            else if (frontIntersection)
                accelerationDirection.z = 1;
            
            if (!(leftIntersection || rightIntersection || 
                bottomIntersection || topIntersection || backIntersection || frontIntersection))
            {
                // Avoid dead-locks by choosing a random direction.
                accelerationDirection.x = (rand() % 2 == 0 ? -1 : +1);
                accelerationDirection.y = (rand() % 2 == 0 ? -1 : +1);
                accelerationDirection.z = (rand() % 2 == 0 ? -1 : +1);
            }
            
            detourSpeed.x += accelerationDirection.x * (accelerationModule * timeDifference);
            detourSpeed.y += accelerationDirection.y * (accelerationModule * timeDifference);
            detourSpeed.z += accelerationDirection.z * (accelerationModule * timeDifference);

            break;
        }
    }
    
    return detourSpeed;
}


// Draws the wing movement animation.
void Boid::animateWings(int timeDifference)
{
    // Calculates the movement of the wings.
    int wingAngleIncrement = timeDifference % 20;
    if (wingDirection >= 0) {
        wingAngle += wingAngleIncrement;
        if (wingAngle > 30) {
            wingAngle = 30;
            wingDirection = -1;
        }
    }
    else {
        wingAngle -= wingAngleIncrement;
        if (wingAngle < -30) {
            wingAngle = -30;
            wingDirection = +1;
        }
    }
}


// Draws a boid.
void Boid::drawBoid(Vector& position, Vector& speed, int wingAngle, 
    float headColor[], float bodyColor[], float tailColor[], float wingColor[])
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glPushMatrix();
    
    glTranslatef(position.x, position.y, position.z);    
 
    // Rotates the body of the boid, so it can be drawn following the direction of 
    // the boid's speed vector.
    if (speed.x != 0 || speed.y != 0 || speed.z != 0) 
    {
        // The y line vector, normal to the xz plane.
        Vector y(0, 1, 0);
        // Calculates the cross product between y and the speed vector
        Vector u = y.crossProduct(speed);
        // The angle between y and the speed vector, converted from radians to degrees
        float theta = y.getAngleBetween(speed) * (180.0 / PI);

        glRotatef(theta, u.x, u.y, u.z);
    }
    
    glPushMatrix();

        // Scale and rotation adjustments for the following drawings.
        glScalef(1, 1.2, 1);    
        glRotatef(-45, 0, 1, 0);

        // Draws the head
        glColor4fv(headColor);
        glPushMatrix();
            glNormal3f(0, 0, 1);
            glScalef(1, 1, 1);
            drawPyramid();
        glPopMatrix();

        // Draws the body
        glColor4fv(bodyColor);
        glPushMatrix();
            glNormal3f(0, 0, -1);
            glRotatef(180, 1, 0, 0);
            glScalef(1, 4, 1);
            drawPyramid();
        glPopMatrix();

        // Draws the tail
        glColor4fv(tailColor);
        glPushMatrix();
            glNormal3f(0, 0, 1);
            glTranslatef(0, -5, 0);
            glScalef(0.5, 1, 0.5);
            drawPyramid();
        glPopMatrix();

        // This angle was calculated using the "right triangle calculator", available at 
        // http://www.mathworksheetsgo.com/trigonometry-calculators/right-triangle-calculator-online.php
        const float magicAngle = 7.125;
        const float magicDistance = 1.25;

        glColor4fv(wingColor);

        // Draws the left wing
        glPushMatrix();
            glNormal3f(0, 1, 0);
            glRotatef(15 + wingAngle, 0, 1, 0);    // The wing rotation    
            glPushMatrix();            
                glTranslatef(-0.5, 0, 0.5);
                glRotatef(90.0f + magicAngle, 1, 0, 1);
                glTranslatef(-magicDistance, -0.2, magicDistance);
                glRotatef(45, 0, 1, 0);
                glScalef(1.4, 4, 0.2);
                drawPyramid();
            glPopMatrix();
        glPopMatrix();

        // Draws the right wing
        glPushMatrix();
            glNormal3f(0, -1, 0);
            glRotatef(15 - wingAngle, 0, 1, 0);    // The wing rotation
            glPushMatrix();
                glTranslatef(0.5, 0, -0.5);
                glRotatef(-(90.0f + magicAngle), 1, 0, 1);
                glTranslatef(magicDistance, -0.2, -magicDistance);
                glRotatef(45, 0, 1, 0);
                glScalef(1.4, 4, 0.2);
                drawPyramid();
            glPopMatrix();
        glPopMatrix();
     
     glPopMatrix();
     
     glPopMatrix();
}