#ifndef _VECTOR_
#define _VECTOR_

#include <string>
#include <sstream>
using namespace std;

#include <math.h>

// A vector in the 3 dimensional space. Not to be confused with the std::vector class.
class Vector
{
    public:
    
        float x;
        float y;
        float z;

        Vector() 
        {
            setValues(0, 0, 0);
        }

        Vector(float x, float y, float z) 
        {
            setValues(x, y, z);
        }
    
        Vector(const Vector& other) 
        {
            copyFrom(other);
        }
    
        void copyFrom(const Vector& other)
        {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }
    
        void setValues(float x, float y, float z) 
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        string toString()
        {
            stringstream txt;
            txt << "(" << x << "," << y << "," << z << ")";
            return txt.str();
        }
        
        // Calculates this vector magnitude.
        float getMagnitude()
	    {
		    return sqrtf(x * x + y * y + z * z);
	    }
	    
	    // Returns true iff this vector has all components equal to zero.
	    bool isZero()
	    {
            return (x == 0 && y == 0 && z == 0);
        }
	    
	 	// Multiply this vector by a scalar
	    Vector operator*(float num) const
	    {
		    return Vector(x * num, y * num, z * num);
	    }
	    
    	// Pass in a vector, pass in a scalar, return the product
	    friend Vector operator*(float num, Vector const &vec)
	    {
		    return Vector(vec.x * num, vec.y * num, vec.z * num);
	    }
	    
    	// Add two vectors
	    Vector operator+(const Vector &vec) const
	    {
		    return Vector(x + vec.x, y + vec.y, z + vec.z);
	    }
	    
	    // Subtract two vectors
	    Vector operator-(const Vector &vec) const
	    {
		    return Vector(x - vec.x, y - vec.y, z - vec.z);
	    }
	    
	    // Normalize this vector
	    void normalize()
	    {
            float magnitude = getMagnitude();

		    x /= magnitude;
		    y /= magnitude;
		    z /= magnitude;
	    }
	    
	    // Returns a versor of this vector, i.e., a copy
	    // with all components divided by the magnitude.
	    Vector getVersor()
	    {
            Vector copy(x, y, z);
            copy.normalize();
            return copy;
        }
	    
	    // Calculates the angle, in radians, between this vector and another.
	    float getAngleBetween(Vector& other) 
	    {	      
            Vector v1 = this->getVersor();
            Vector v2 = other.getVersor();            
            
            return acos((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
        }
	    
	    // Calculates the dot product between this vector and another vector.
	    float dotProduct(const Vector &vec) const
	    {
		    return x * vec.x + y * vec.y + z * vec.z;
	    }

        // Calculates the cross product between this vector and another vector.
	    Vector crossProduct(const Vector &vec) const
	    {
	        return Vector(y * vec.z - z * vec.y,
				          z * vec.x - x * vec.z,
				          x * vec.y - y * vec.x);
	    }
};

#endif