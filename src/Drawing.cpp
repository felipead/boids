#include "Drawing.hpp"

// Draws a simple, unidimensional pyramid.
// Use glScale3f before calling this method to alter the pyramid size.
// Use glTranslatef to set the pyramid position.
void drawPyramid()
{
    glBegin(GL_TRIANGLES);
    
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 0);
    
    glVertex3f(0, 1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, -1);
    
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, -1);
    glVertex3f(-1, 0, 0);
    
    glVertex3f(0, 1, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(0, 0, 1);
    
    glEnd();
}

void drawColorfulPyramid()
{
    glBegin(GL_TRIANGLES);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);
    glColor3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glColor3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -1);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -1);
    glColor3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glColor3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 1);
    
    glEnd();
}