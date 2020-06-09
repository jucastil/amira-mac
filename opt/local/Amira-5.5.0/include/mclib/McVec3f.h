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
#ifndef MC_VEC3F_H
#define MC_VEC3F_H

#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "McStdlib.h"
#include "McVec3d.h"

class McVec3i;

/** This class provides a 3D vector of floats.
    @see McVec2i, McVec3i, McVec4i, McVec2f, McVec4f, McVec3d
*/
class McVec3f
{
  public:

    typedef float BaseType;
    enum {DIM = 3};

    /// vector's first component.
    float x;
    /// vector's second component.
    float y;
    /// vector's third component.
    float z;

    /// Default constructor doesn't initialize anything.
    McVec3f() {}

    /// Constructor.
    McVec3f(const float _x, const float _y, const float _z) {
        this->x = _x; this->y = _y; this->z = _z;
    }

    /// Other constructor, useful for scale factors (x=y=z=value).
    explicit McVec3f(const float value) { x=y=z=value; }

    /// Copy constructor.
    McVec3f(const McVec3f& v) { x = v.x; y = v.y; z=v.z; }

    /// Conversion constructor out of McVec3d.
    explicit McVec3f(const McVec3d& v) { x = float(v.x); y = float(v.y); z = float(v.z); }

    /// Conversion constructor out of McVec3i.
    McVec3f(const McVec3i& v);

    /// Assignment of McVec3x
    template < typename T >
    McVec3f& operator=(const T& v) {
        x=double(v.x); y=double(v.y); z=double(v.z); return *this;
    }

    /// Addition.
    McVec3f& operator+=(const McVec3f& v) {
        x+=v.x; y+=v.y; z+=v.z; return *this;
    }

    /// Addition of McVec3d.
    McVec3f& operator+=(const McVec3d& v) {
        x+=float(v.x); y+=float(v.y); z+=float(v.z); return *this;
    }

    /// Subtraction.
    McVec3f& operator-=(const McVec3f& v) {
        x-=v.x; y-=v.y; z-=v.z; return *this;
    }

    /// Multiplication.
    McVec3f& operator*=(float d) { x*=d; y*=d; z*=d; return *this; }

    /// Division.
    McVec3f& operator/=(float d) { x/=d; y/=d; z/=d; return *this; }

    /// Index operator. Performs index check via assert().
    float& operator[](int i) { assert(i>=0 && i<=2); return (&x)[i]; }

    /// Const index operator. Performs index check via assert().
    const float& operator[](int i) const {assert(i>=0 && i<=2);return (&x)[i];}

    /// Sets the vectors components to _x, _y, and _z.
    void setValue(float _x, float _y, float _z) {
        x = _x; y =_y; z = _z;
    }
    // SPECIAL FUNCTIONS

    /// Euclidean length.
    float length() const {
        return MC_sqrtf(x*x + y*y + z*z);
}

    /// Squared length.
    float length2() const { return x*x + y*y + z*z; }

    /// absolute value of longest component
    float infnorm() const {
      float m = fabs(x);
      float t=fabs(y);
      if (t>m) m=t;
      t=fabs(z);
      if (t>m) m=t;
      return m;
    }

    /// returns the angle between two vectors in 3D space
    double angle(const McVec3f& other) const {
        const float d = dot(other);
        const float denom = length()*other.length();
        const float ratio = denom ? d/denom : 0.f;
        if (ratio<-1) return M_PI;
        return (ratio>1) ? 0 : acos(ratio);
    }

    /// Normalizes the vector to a length of 1
    float normalize() {
        float len = length();
        if (len) {
            x/=len; y/=len; z/=len;
        }
        return len;
    }

    // FRIENDS

    /// Unary minus.
    friend McVec3f operator-(const McVec3f& a) {
        return McVec3f(-a.x,-a.y,-a.z);
    }

    /// Addition.
    friend McVec3f operator+(const McVec3f& a, const McVec3f& b) {
        return McVec3f(a.x+b.x, a.y+b.y, a.z+b.z);
    }

    /// Subtraction.
    friend McVec3f operator-(const McVec3f& a, const McVec3f& b)
        { return McVec3f(a.x-b.x, a.y-b.y, a.z-b.z); }

    /// Dot product.
    float dot(const McVec3f& a) const { return (x*a.x + y*a.y + z*a.z); }

    /// Cross Product.
    McVec3f cross(const McVec3f& o) const {
        return McVec3f(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
    }

    /// Compute component-wise product.
    McVec3f compprod(const McVec3f& o) const {
        return McVec3f(x*o.x, y*o.y, z*o.z);
    }

    /// Compute Component-wise quotient.
    McVec3f compquot(const McVec3f& o) const {
        return McVec3f(x/o.x, y/o.y, z/o.z);
    }

    /// Scalar multiplication from right.
    friend McVec3f operator*(const McVec3f& a, float d)
        { return McVec3f(d*a.x, d*a.y, d*a.z); }

    /// Scalar multiplication from left.
    friend McVec3f operator*(float d, const McVec3f& a)
        { return McVec3f(d*a.x, d*a.y, d*a.z); }

    /// Scalar division.
    friend McVec3f operator/(const McVec3f& a, float d)
        { return McVec3f(a.x/d, a.y/d, a.z/d); }

    /// Comparison.
    friend int operator == (const McVec3f& a, const McVec3f& b)
        { return (a.x==b.x) && (a.y==b.y) && (a.z==b.z); }

    /// equal with tolerance in length
    bool equals (const McVec3f& b, float tolerance = 1e-6) const {
        if ((*this - b).length2() <= (tolerance * tolerance)) {
            return true;
        }
        return false;
    }

    /// Not equal.
    friend int operator != (const McVec3f& a, const McVec3f& b)
        { return !(a==b); }

    /// Less than.
    friend int operator < (const McVec3f& a, const McVec3f& b) {
        if ( a.x != b.x ) return (a.x < b.x);
        if ( a.y != b.y ) return (a.y < b.y);
        return (a.z < b.z);
    }

    /// Larger than.
    friend int operator > (const McVec3f& a, const McVec3f& b) {
        if ( a.x != b.x ) return (a.x > b.x);
        if ( a.y != b.y ) return (a.y > b.y);
        return (a.z > b.z);
    }

    /// Returns principal axis that is closest (based on maximum dot product) to this vector.
    McVec3f getClosestAxis() const {
        McVec3f axis(0.0f, 0.0f, 0.0f);
        McVec3f bestAxis(0.0f, 0.0f, 0.0f);
        float d, max = -1.0f;

        for (int m=0; m<3; ++m) {
            axis[m] = 1.0f;
            if ((d = dot(axis)) > max) { max=d; bestAxis=axis; }
            axis[m] = -1.0f;
            if ((d = dot(axis)) > max) { max=d; bestAxis=axis; }
            axis[m] = 0.0f;
        }

        return bestAxis;
    }

    /// Performs a linear interpolation between this and another vector.
    McVec3f lerp(McVec3f const& other,float s) {
        assert(s>=0 && s<=1);
        return McVec3f(
            x+(other.x-x)*s,
            y+(other.y-y)*s,
            z+(other.z-z)*s
        );
    }

    /// Prints McVec3f to given file pointer
    void print(FILE *fp) const {
        fprintf(fp, "%10.5g %10.5g %10.5g\n", x,y,z);
    }

#if defined _SB_LINEAR_ || defined COIN_SBVEC3F_H
    /// Constructs a McVec3f from an Inventor SbVec3f.
    McVec3f(const SbVec3f& sv) {
        const float* v = sv.getValue();
        x=v[0]; y=v[1]; z=v[2];
    }

    /// Assigns an Inventor SbVec3f to a McVec3f.
    McVec3f& operator=(const SbVec3f& sv) {
        const float* v = sv.getValue();
        x=v[0]; y=v[1]; z=v[2]; return *this;
    }

    /// Conversion operator to SbVec3f.
    operator SbVec3f() const { return SbVec3f (x, y, z); }
#endif

    /// Return pointer to the values.
    const float* getValue() const { return &x; }
};

#include "McVec3d_impl.h"

#ifndef MC_VEC3I_H
    #include "McVec3f_impl.h"
#endif

#endif

/// @}
