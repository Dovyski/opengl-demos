#ifndef _VECTOR_H__
#define _VECTOR_H__

#include <math.h>

class Vector  
{
public:
   float x, y, z;

   Vector()
   {
      x = y = z = 0;
   }

   Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

   float dot(const Vector& v) const
   {
      float ret;
      ret = x*v.x + y*v.y + z*v.z;
      return ret;
   }
  
   void normalize()
   {
      float norm = (float)sqrt(x*x + y*y + z*z);
      x /= norm;
      y /= norm;
      z /= norm;
   }
   
   Vector operator - ( const Vector& v )
   {
      Vector aux( x - v.x, y - v.y, z - v.z );
      return( aux );
   }
   
};

#endif
