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
#ifndef MC_VEC3D_H
#define MC_VEC3D_H

#include <math.h>
#include <assert.h>

class McVec3f;

/** This class provides a 3D vector of doubles.
 @see McVec2i, McVec3i, McVec4i, McVec2f, McVec3f, McVec4f
*/
class McVec3d
{
  public:

    typedef double BaseType;
    enum {DIM = 3};

    /// vector's first component.
    double x;
    /// vector's second component.
    double y;
    /// vector's third component.
    double z;

    /// Default constructor doesn't initialize anything.
    McVec3d() {}

    /// Constructor from floats.
    McVec3d(const float xx, const float yy, const float zz)
    { x=xx; y=yy; z=zz; }

    /// Constructor from doubles.
    McVec3d(const double xx, const double yy, const double zz)
    { x=xx; y=yy; z=zz; }

    /// Other constructor, useful for scale factors (x=y=z=value).
    explicit McVec3d(const double value) { x=y=z=value; }

    /// Copy constructor.
    McVec3d(const McVec3d& v) { x = v.x; y = v.y; z = v.z;}

    /// Conversion constructor out of McVec3f.
    explicit McVec3d(const McVec3f& v);

    /// Assignment.
    McVec3d& operator=(const McVec3d& v) {
        x=v.x; y=v.y; z=v.z; return *this;
    }

    /// Assignment of McVec3f.
    McVec3d& operator=(const McVec3f& v);

    /// Addition.
    McVec3d& operator+=(const McVec3d& v) {
        x+=v.x; y+=v.y; z+=v.z; return *this;
    }

    /// Addition.
    McVec3d& operator+=(const McVec3f& v);

    /// Subtraction.
    McVec3d& operator-=(const McVec3d& v) {
        x-=v.x; y-=v.y; z-=v.z; return *this;
    }

    /// Scalar multiplication with double.
    McVec3d& operator*=(double d) { x*=d; y*=d; z*=d; return *this; }

    /// Scalar division by double.
    McVec3d& operator/=(double d) { x/=d; y/=d; z/=d; return *this; }

    /// Index operator. Performs index check via assert().
    double& operator[](int i) { assert(i>=0 && i<=2); return (&x)[i]; }

    /// Const index operator. Performs index check via assert().
    const double& operator[](int i) const
    {assert(i>=0 && i<=2);return (&x)[i];}

    /// Sets the vectors components to _x, _y, and _z.
    void setValue(double _x, double _y, double _z) {
        x = _x; y =_y; z = _z;
    }
    // SPECIAL FUNCTIONS

    /// Euclidean length.
    double length() const {
        return sqrt(x*x + y*y + z*z);
    }

    /// absolute value of longest component
    double infnorm() const {
      double m = fabs(x);
      double t=fabs(y);
      if (t>m) m=t;
      t=fabs(z);
      if (t>m) m=t;
      return m;
    }

    /// Squared length.
    double length2() const { return x*x + y*y + z*z; }

    /// Normalizes the vector to a length of 1
    double normalize() {
        double len = length();
        if (len) {
            x/=len; y/=len; z/=len;
        }
        return len;
    }

    // FRIENDS

    /// Unary minus.
    friend McVec3d operator-(const McVec3d& a) {
        return McVec3d(-a.x,-a.y,-a.z);
    }

    /// Addition.
    friend McVec3d operator+(const McVec3d& a, const McVec3d& b) {
        return McVec3d(a.x+b.x, a.y+b.y, a.z+b.z);
    }

    /// Subtraction.
    friend McVec3d operator-(const McVec3d& a, const McVec3d& b)
        { return McVec3d(a.x-b.x, a.y-b.y, a.z-b.z); }

    /// Dot product.
    double dot(const McVec3d& a) const { return (x*a.x + y*a.y + z*a.z); }

    /// Cross product.
    McVec3d cross(const McVec3d& o) const {
        return McVec3d(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
    }

    /// Scalar multiplication from right with double.
    friend McVec3d operator*(const McVec3d& a, double d)
        { return McVec3d(d*a.x, d*a.y, d*a.z); }

    /// Scalar multiplication from left with double.
    friend McVec3d operator*(double d, const McVec3d& a)
        { return McVec3d(d*a.x, d*a.y, d*a.z); }

    /// Scalar division by double.
    friend McVec3d operator/(const McVec3d& a, double d)
        { return McVec3d(a.x/d, a.y/d, a.z/d); }

    /// Comparison.
    friend int operator == (const McVec3d& a, const McVec3d& b)
        { return (a.x==b.x) && (a.y==b.y) && (a.z==b.z); }

    /// equal with tolerance in length
    bool equals (const McVec3d& b, float tolerance = 1e-6) {
        if ((*this - b).length2() <= (tolerance * tolerance)) {
            return true;
        }
        return false;
    }

    /// Not equal.
    friend int operator != (const McVec3d& a, const McVec3d& b)
        { return !(a==b); }

    /// Less than.
    friend int operator < (const McVec3d& a, const McVec3d& b) {
        if ( a.x != b.x ) return (a.x < b.x);
        if ( a.y != b.y ) return (a.y < b.y);
        return (a.z < b.z);
    }

    /// Larger than.
    friend int operator > (const McVec3d& a, const McVec3d& b) {
        if ( a.x != b.x ) return (a.x > b.x);
        if ( a.y != b.y ) return (a.y > b.y);
        return (a.z > b.z);
    }

};

#ifndef MC_VEC3F_H
    #include "McVec3d_impl.h"
#endif

#endif

/// @}
