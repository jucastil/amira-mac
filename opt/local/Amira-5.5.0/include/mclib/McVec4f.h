/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_VEC4F_H
#define MC_VEC4F_H

#include <math.h>
#include <assert.h>
#include "McStdlib.h"

/** This class provides a 4D vector of floats.
    @see McVec2i, McVec3i, McVec4i, McVec2f, McVec3f, McVec3d
*/
class McVec4f
{
  public:

    typedef float BaseType;
    enum {DIM = 4};

    /// vector's first component.
    float x;
    /// vector's second component.
    float y;
    /// vector's third component.
    float z;
    /// vector's fourth component.
    float t;

    /// Default constructor doesn't initialize anything.
    McVec4f()
    {
    }

    /// Constructor.
    McVec4f(const float _x, const float _y, const float _z, const float _t)
    {
        this->x = _x; this->y = _y; this->z = _z; this->t = _t;
    }

    /// Other constructor, useful for scale factors (x=y=z=t=value).
    McVec4f(const float value)
    {
        x=y=z=t=value;
    }

    /// Copy constructor.
    McVec4f(const McVec4f& v)
    {
        x = v.x; y = v.y; z=v.z; t=v.t;
    }

    /// Assignment.
    McVec4f & operator = (const McVec4f& v)
    {
        x=v.x; y=v.y; z=v.z; t=v.t;  return *this;
    }

    /// Addition.
    McVec4f & operator += (const McVec4f& v)
    {
        x+=v.x; y+=v.y; z+=v.z; t+=v.t; return *this;
    }

    /// Subtraction.
    McVec4f & operator -= (const McVec4f& v)
    {
        x-=v.x; y-=v.y; z-=v.z; t-=v.t; return *this;
    }

    /// Multiplication.
    McVec4f & operator *= (float d)
    {
        x*=d; y*=d; z*=d; t*=d; return *this;
    }

    /// Division.
    McVec4f & operator /= (float d)
    {
        x/=d; y/=d; z/=d; t/=d; return *this;
    }

    /// Index operator. Performs index check via assert().
    float & operator [] (int i)
    {
        assert(i>=0 && i<=3); return (&x)[i];
    }

    /// Const index operator. Performs index check via assert().
    const float & operator [] (int i) const
    {
        assert(i>=0 && i<=3);
        return (&x)[i];
    }

    /// Sets the vectors components to _x, _y, _z, and _t
    void setValue( float _x, float _y, float _z, float _t )
    {
        x = _x; y =_y; z = _z; t=_t;
    }

    ////////////////////////////////////
    // SPECIAL FUNCTIONS
    ////////////////////////////////////

    /// Euclidean length.
    float length() const
    {
        return MC_sqrtf(x*x + y*y + z*z + t*t);
    }

    /// Squared length.
    float length2() const
    {
        return x*x + y*y + z*z + t*t;
    }

    /// Normalizes the vector to a length of 1
    float normalize()
    {
        float len = length();
        if (len)
        {
            x/=len; y/=len; z/=len; t/=len;
        }
        return len;
    }

    // FRIENDS

    /// Unary minus.
    friend McVec4f operator-(const McVec4f& a)
    {
        return McVec4f(-a.x,-a.y,-a.z,-a.t);
    }

    /// Addition.
    friend McVec4f operator+(const McVec4f& a, const McVec4f& b)
    {
        return McVec4f(a.x+b.x, a.y+b.y, a.z+b.z, a.t+b.t);
    }

    /// Subtraction.
    friend McVec4f operator-(const McVec4f& a, const McVec4f& b)
    {
        return McVec4f(a.x-b.x, a.y-b.y, a.z-b.z, a.t-b.t);
    }

    /// Scalar multiplication from right.
    friend McVec4f operator*(const McVec4f& a, float d)
    {
        return McVec4f(d*a.x, d*a.y, d*a.z, d*a.t);
    }

    /// Scalar multiplication from left.
    friend McVec4f operator*(float d, const McVec4f& a)
    {
        return McVec4f(d*a.x, d*a.y, d*a.z, d*a.t);
    }

    /// Scalar division.
    friend McVec4f operator/(const McVec4f& a, float d)
    {
        return McVec4f(a.x/d, a.y/d, a.z/d, a.t/d);
    }

    /// Dot product.
    float dot(const McVec4f& a) const
    {
        return (x*a.x + y*a.y + z*a.z + t*a.t);
    }

    /// Comparison.
    friend int operator == (const McVec4f& a, const McVec4f& b)
    {
        return (a.x==b.x) && (a.y==b.y) && (a.z==b.z) && (a.t==b.t);
    }

    /// equal with tolerance in length
    bool equals (const McVec4f& b, float tolerance = 1e-6)
    {
        if ((*this - b).length2() <= (tolerance * tolerance))
        {
            return true;
        }
        return false;
    }

    /// Not equal.
    friend int operator != (const McVec4f& a, const McVec4f& b)
    {
        return !(a==b);
    }

    /// Less than.
    friend int operator < (const McVec4f& a, const McVec4f& b)
    {
        if ( a.x != b.x ) return (a.x < b.x);
        if ( a.y != b.y ) return (a.y < b.y);
        if ( a.z != b.z ) return (a.z < b.z);
        return (a.t < b.t);
    }

    /// Larger than.
    friend int operator > (const McVec4f& a, const McVec4f& b)
    {
        if ( a.x != b.x ) return (a.x > b.x);
        if ( a.y != b.y ) return (a.y > b.y);
        if ( a.z != b.z ) return (a.z > b.z);
        return (a.t > b.t);
    }

#ifdef _SB_LINEAR_

    /// Constructs a McVec4f from an Inventor SbVec4f.
    McVec4f(const SbVec4f& sv)
    {
        const float* v = sv.getValue();
        x=v[0]; y=v[1]; z=v[2]; t=v[3];
    }

    /// Assigns an Inventor SbVec4f to a McVec4f.
    McVec4f& operator=(const SbVec3f& sv)
    {
        const float* v = sv.getValue();
        x=v[0]; y=v[1]; z=v[2]; t=v[3]; return *this;
    }

    /// conversion operator back to SbVec4f.
    operator SbVec4f() const
    {
        return SbVec4f (x, y, z, t);
    }

#endif
};

#endif

/// @}
