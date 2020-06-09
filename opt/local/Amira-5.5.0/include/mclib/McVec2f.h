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
#ifndef MC_VEC2F_H
#define MC_VEC2F_H

#include "McWinDLLApi.h"
#include "McVec3f.h"

#include <math.h>
#include <assert.h>

/** This class provides a 2D vector of floats.
    @see McVec2i, McVec3i, McVec4i, McVec3f, McVec4f, McVec3d
*/
class McVec2f
{
  public:

    typedef float BaseType;
    enum {DIM = 2};

    /// Vector's first component.
    float x;
    /// Vector's second component.
    float y;

    /// Default constructor does not initialize anything.
    McVec2f() {}

    /// Initializing constructor.
    McVec2f(const float _x, const float _y) { this->x = _x; this->y = _y; }

    /// Other constructor, useful for scale factors (x=y=xy).
    McVec2f(const float xy) { this->x = xy; this->y = xy; }

    /// Copy constructor.
    McVec2f(const McVec2f& v) { x = v.x; y = v.y; }

    /// Sets vectors components to _x and _y.
    void setValue(float _x, float _y) { x = _x; y =_y; }

    /// Assignment.
    McVec2f& operator=(const McVec2f& v) { x=v.x; y=v.y; return *this; }

    /// Addition.
    McVec2f& operator+=(const McVec2f& v) { x+=v.x; y+=v.y; return *this; }

    /// Subtraction.
    McVec2f& operator-=(const McVec2f& v) { x-=v.x; y-=v.y; return *this; }

    /// Multiplication.
    McVec2f& operator*=(const float d) { x*=d; y*=d; return *this; }

    /// Division.
    McVec2f& operator/=(const float d) { x/=d; y/=d; return *this; }

    /// Index operator. Performs index check via assert().
    float& operator[](int i) { assert(i>=0 && i<=1); return (&x)[i]; }

    /// Const index operator. Performs index check via assert().
    const float& operator[](int i) const { assert(i>=0 && i<=1); return (&x)[i]; }

    // SPECIAL FUNCTIONS

    /// Euclidean length.
    float length() const {
        return MC_fhypot(y,x);
    }

    /// Squared length.
    float length2() const { return x*x + y*y; }

    /// Distance to other vector
    float distance(const McVec2f& v) const {return MC_fhypot(v.y-y,v.x-x);}

    /// Absolute value of longest component.
    float infnorm() const {
      float m = fabs(x);
      float t=fabs(y);
      if (t>m) m=t;
      return m;
    }

    /// Normalizes the vector to a length of 1.
    float normalize() {
        float len = length();
        if (len) {
            x/=len; y/=len;
        }
        return len;
    }

    /// returns the angle between two vectors in 3D space
    double angle(const McVec2f& other) const {
        assert(length()!=0 && other.length()!=0);
        const double ratio = this->dot(other) / (length()*other.length());
        if (ratio<-1) return M_PI;
        return (ratio>1) ? 0 : acos(ratio);
    }

    // FRIENDS

    /// Unary minus.
    friend McVec2f operator-(const McVec2f& a) { return McVec2f(-a.x,-a.y); }

    /// Addition.
    friend McVec2f operator+(const McVec2f& a, const McVec2f& b)
        { return McVec2f(a.x+b.x, a.y+b.y); }

    /// Subtraction.
    friend McVec2f operator-(const McVec2f& a, const McVec2f& b)
        { return McVec2f(a.x-b.x, a.y-b.y); }

    /// Scalar multiplication from right.
    friend McVec2f operator*(const McVec2f& a, const float d)
        { return McVec2f(d*a.x, d*a.y); }

    /// Scalar multiplication from left.
    friend McVec2f operator*(const float d, const McVec2f& a)
        { return McVec2f(d*a.x, d*a.y); }

    /// Scalar division.
    friend McVec2f operator/(const McVec2f& a, const float d)
        { return McVec2f(a.x/d, a.y/d); }

    /// Dot product.
    float dot(const McVec2f& a) const { return (x*a.x + y*a.y); }

    /// Cross product.
    float cross(const McVec2f& a) const { return (x*a.y - y*a.x); }

    /// Component-wise product.
    McVec2f compprod(const McVec2f& o) const {
        return McVec2f(x*o.x, y*o.y);
    }

    /// Comparison.
    friend int operator == (const McVec2f& a, const McVec2f& b)
        { return (a.x==b.x) && (a.y==b.y); }

    /// Equal with tolerance in length.
    bool equals (const McVec2f& b, float tolerance = 1e-6) const {
        if ((*this - b).length2() <= (tolerance * tolerance)) {
            return true;
        }
        return false;
    }

    /// Not equal.
    friend int operator != (const McVec2f& a, const McVec2f& b)
        { return !(a==b); }

    /// Less than.
    friend int operator < (const McVec2f& a, const McVec2f& b) {
        if ( a.x != b.x ) return (a.x < b.x);
        return (a.y < b.y);
    }

    /// Larger than.
    friend int operator > (const McVec2f& a, const McVec2f& b) {
        if ( a.x != b.x ) return (a.x > b.x);
        return (a.y > b.y);
    }

    /// Computes new vector from minimal components of a and b.
    friend McVec2f mcmin(const McVec2f& a, const McVec2f& b)
        { return McVec2f((a.x<b.x)?a.x:b.x, (a.y<b.y)?a.y:b.y); }

    /// Computes new vector from maximal components of a and b.
    friend McVec2f mcmax(const McVec2f& a, const McVec2f& b)
        { return McVec2f((a.x>b.x)?a.x:b.x, (a.y>b.y)?a.y:b.y); }

    /// Tests whether the point is inside the triangle given by the three argument points.
    bool isInTriangle(const McVec2f& a, const McVec2f& b, const McVec2f& c, float eps=0) const {
        McVec3f localBarycentricCoords;

        // McMat3f(this->x, b.x, c.x,  this->y, b.y, c.y,  1, 1, 1).det();
        float area0 = this->x * (b.y-c.y) - b.x * (this->y - c.y) + c.x * (this->y - b.y);

        // McMat3f(a.x, this->x, c.x,  a.y, this->y, c.y,  1, 1, 1).det();
        float area1 = a.x * (this->y-c.y) - this->x * (a.y - c.y) + c.x * (a.y - this->y);

        // McMat3f(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1).det();
        float areaTotal = a.x * (b.y-c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        localBarycentricCoords[0] = area0/areaTotal;
        localBarycentricCoords[1] = area1/areaTotal;
        localBarycentricCoords[2] = 1 - localBarycentricCoords[0] - localBarycentricCoords[1];

        return (localBarycentricCoords[0]>=-eps && localBarycentricCoords[1]>=-eps && localBarycentricCoords[2]>=-eps);
    }

    /// compute the barycentric coords in the triangle given by the three argument points.
    McVec3f computeBarycentric(const McVec2f& a, const McVec2f& b, const McVec2f& c, float eps=0) const {
        McVec3f bary;

        // det(this->x, b.x, c.x,  this->y, b.y, c.y,  1, 1, 1)
        float area0 = x * (b.y - c.y) - b.x * (y - c.y) + c.x * (y - b.y);

        // det(a.x, this->x, c.x,  a.y, this->y, c.y,  1, 1, 1)
        float area1 = a.x * (y - c.y) - x * (a.y - c.y) + c.x * (a.y - y);

        // det(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1)
        float areaTotal = a.x * (b.y - c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        bary.x = area0 / areaTotal;
        if ( fabs(bary.x) < eps ){
            bary.x = 0.0f;
        }
        else if ( fabs(1.0f-bary.x) < eps ){
            bary.x = 1.0f;
        }

        bary.y = area1 / areaTotal;
        if ( fabs(bary.y) < eps ){
            bary.y = 0.0f;
        }
        else if ( fabs(1.0f-bary.y) < eps ){
            bary.y = 1.0f;
        }

        bary.z = 1.0f - bary.x - bary.y;

        return bary;
    }

    /// Return orientation (-1 -> clockwise, 0 -> collinear, 1 -> counterclockwise).
    static signed char orientation(const McVec2f &a, const McVec2f &b, const McVec2f &c, const float eps=0.0){
        // McMat3f(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1).det();
        float det = a.x * (b.y-c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        if (det>eps)
            return 1;
        else if (det<-eps)
            return -1;

        return 0;
    }

#ifdef _SB_LINEAR_
    /// Constructs a McVec2f from an Inventor SbVec2f.
    McVec2f(const SbVec2s& sv) {
        const short* v = sv.getValue();
        x=v[0]; y=v[1];
    }
#endif
};

#endif

/// @}
