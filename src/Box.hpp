#ifndef _BOX_
#define _BOX_

// Represents a box, i.e., a rectangle in the 3 dimensional space that is aligned with the
// x, y and z lines.
class Box
{
    public:
    
        // The x coordinate of the left side of the 3D rectangle 
        float left;

        // The x coordinate of the right side of the 3D rectangle     
        float right;
    
        // The y coordinate of the bottom side of the 3D rectangle     
        float bottom;

        // The y coordinate of the top side of the 3D rectangle         
        float top;
    
        // The z coordinate of the back side of the 3D rectangle     
        float back;
    
        // The z coordinate of the front side of the 3D rectangle
        float front;
    
        Box() 
        {
            setValues(0, 0, 0, 0, 0, 0);
        }
    
        Box(float left, float right, float bottom, float top, float back, float front) 
        {
            setValues(left, right, bottom, top, back, front);
        }

        void setValues(float left, float right, float bottom, float top, float back, float front) 
        {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
            this->back = back;
            this->front = front;
        }

        float getWidth() 
        {
            return right - left;
        }
    
        float getHeight()
        {
            return top - bottom;
        }
    
        float getDepth()
        {
            return front - back;
        }
};

#endif