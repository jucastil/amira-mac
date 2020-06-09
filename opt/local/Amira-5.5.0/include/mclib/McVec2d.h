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
#ifndef MC_VEC2D_H
#define MC_VEC2D_H

#include "McWinDLLApi.h"
#include "McVec3d.h"

#include <math.h>
#include <assert.h>

/** This class provides a 2D vector of doubles.
    @see McVec2i, McVec3i, McVec4i, McVec3f, McVec4f, McVec3d
*/
class McVec2d
{
  public:

    typedef double BaseType;
    enum {DIM = 2};

    /// Vector's first component.
    double x;
    /// Vector's second component.
    double y;

    /// Default constructor does not initialize anything.
    McVec2d() {}

    /// Initializing constructor.
    McVec2d(const double _x, const double _y) { this->x = _x; this->y = _y; }

    /// Other constructor, useful for scale factors (x=y=xy).
    McVec2d(const double xy) { this->x = xy; this->y = xy; }

    /// Copy constructor.
    McVec2d(const McVec2d& v) { x = v.x; y = v.y; }

    /// Sets vectors components to _x and _y.
    void setValue(double _x, double _y) { x = _x; y =_y; }

    /// Assignment.
    McVec2d& operator=(const McVec2d& v) { x=v.x; y=v.y; return *this; }

    /// Addition.
    McVec2d& operator+=(const McVec2d& v) { x+=v.x; y+=v.y; return *this; }

    /// Subtraction.
    McVec2d& operator-=(const McVec2d& v) { x-=v.x; y-=v.y; return *this; }

    /// Multiplication.
    McVec2d& operator*=(const double d) { x*=d; y*=d; return *this; }

    /// Division.
    McVec2d& operator/=(const double d) { x/=d; y/=d; return *this; }

    /// Index operator. Performs index check via assert().
    double& operator[](int i) { assert(i>=0 && i<=1); return (&x)[i]; }

    /// Const index operator. Performs index check via assert().
    const double& operator[](int i) const { assert(i>=0 && i<=1); return (&x)[i]; }

    // SPECIAL FUNCTIONS

    /// Euclidean length.
    double length() const {
        return MC_hypot(y,x);
    }

    /// Squared length.
    double length2() const { return x*x + y*y; }

    /// Distance to other vector
    double distance(const McVec2d& v) const {return MC_hypot(v.y-y,v.x-x);}

    /// Absolute value of longest component.
    double infnorm() const {
      double m = fabs(x);
      double t=fabs(y);
      if (t>m) m=t;
      return m;
    }

    /// Normalizes the vector to a length of 1.
    double normalize() {
        double len = length();
        if (len) {
            x/=len; y/=len;
        }
        return len;
    }

    /// returns the angle between two vectors in 3D space
    double angle(const McVec2d& other) const {
        assert(length()!=0 && other.length()!=0);
        const double ratio = this->dot(other) / (length()*other.length());
        if (ratio<-1) return M_PI;
        return (ratio>1) ? 0 : acos(ratio);
    }

    // FRIENDS

    /// Unary minus.
    friend McVec2d operator-(const McVec2d& a) { return McVec2d(-a.x,-a.y); }

    /// Addition.
    friend McVec2d operator+(const McVec2d& a, const McVec2d& b)
        { return McVec2d(a.x+b.x, a.y+b.y); }

    /// Subtraction.
    friend McVec2d operator-(const McVec2d& a, const McVec2d& b)
        { return McVec2d(a.x-b.x, a.y-b.y); }

    /// Scalar multiplication from right.
    friend McVec2d operator*(const McVec2d& a, const double d)
        { return McVec2d(d*a.x, d*a.y); }

    /// Scalar multiplication from left.
    friend McVec2d operator*(const double d, const McVec2d& a)
        { return McVec2d(d*a.x, d*a.y); }

    /// Scalar division.
    friend McVec2d operator/(const McVec2d& a, const double d)
        { return McVec2d(a.x/d, a.y/d); }

    /// Dot product.
    double dot(const McVec2d& a) const { return (x*a.x + y*a.y); }

    /// Cross product.
    double cross(const McVec2d& a) const { return (x*a.y - y*a.x); }

    /// Component-wise product.
    McVec2d compprod(const McVec2d& o) const {
        return McVec2d(x*o.x, y*o.y);
    }

    /// Comparison.
    friend int operator == (const McVec2d& a, const McVec2d& b)
        { return (a.x==b.x) && (a.y==b.y); }

    /// Equal with tolerance in length.
    bool equals (const McVec2d& b, double tolerance = 1e-6) {
        if ((*this - b).length2() <= (tolerance * tolerance)) {
            return true;
        }
        return false;
    }

    /// Not equal.
    friend int operator != (const McVec2d& a, const McVec2d& b)
        { return !(a==b); }

    /// Less than.
    friend int operator < (const McVec2d& a, const McVec2d& b) {
        if ( a.x != b.x ) return (a.x < b.x);
        return (a.y < b.y);
    }

    /// Larger than.
    friend int operator > (const McVec2d& a, const McVec2d& b) {
        if ( a.x != b.x ) return (a.x > b.x);
        return (a.y > b.y);
    }

    /// Computes new vector from minimal components of a and b.
    friend McVec2d mcmin(const McVec2d& a, const McVec2d& b)
        { return McVec2d((a.x<b.x)?a.x:b.x, (a.y<b.y)?a.y:b.y); }

    /// Computes new vector from maximal components of a and b.
    friend McVec2d mcmax(const McVec2d& a, const McVec2d& b)
        { return McVec2d((a.x>b.x)?a.x:b.x, (a.y>b.y)?a.y:b.y); }

    /// Tests whether the point is inside the triangle given by the three argument points.
    bool isInTriangle(const McVec2d& a, const McVec2d& b, const McVec2d& c, double eps=0) const {
        McVec3d localBarycentricCoords;

        // McMat3d(this->x, b.x, c.x,  this->y, b.y, c.y,  1, 1, 1).det();
        double area0 = this->x * (b.y-c.y) - b.x * (this->y - c.y) + c.x * (this->y - b.y);

        // McMat3d(a.x, this->x, c.x,  a.y, this->y, c.y,  1, 1, 1).det();
        double area1 = a.x * (this->y-c.y) - this->x * (a.y - c.y) + c.x * (a.y - this->y);

        // McMat3d(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1).det();
        double areaTotal = a.x * (b.y-c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        localBarycentricCoords[0] = area0/areaTotal;
        localBarycentricCoords[1] = area1/areaTotal;
        localBarycentricCoords[2] = 1 - localBarycentricCoords[0] - localBarycentricCoords[1];

        return (localBarycentricCoords[0]>=-eps && localBarycentricCoords[1]>=-eps && localBarycentricCoords[2]>=-eps);
    }

    /// compute the barycentric coords in the triangle given by the three argument points.
    McVec3d computeBarycentric(const McVec2d& a, const McVec2d& b, const McVec2d& c, double eps=0) const {
        McVec3d bary;

        // det(this->x, b.x, c.x,  this->y, b.y, c.y,  1, 1, 1)
        double area0 = x * (b.y-c.y) - b.x * (y - c.y) + c.x * (y - b.y);

        // det(a.x, this->x, c.x,  a.y, this->y, c.y,  1, 1, 1)
        double area1 = a.x * (y-c.y) - x * (a.y - c.y) + c.x * (a.y - y);

        // det(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1)
        double areaTotal = a.x * (b.y-c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        bary.x = area0 / areaTotal;
        if ( fabs(bary.x) < eps ){
            bary.x = 0.0;
        }
        else if ( fabs(1.0-bary.x) < eps ){
            bary.x = 1.0;
        }

        bary.y = area1 / areaTotal;
        if ( fabs(bary.y) < eps ){
            bary.y = 0.0;
        }
        else if ( fabs(1.0-bary.y) < eps ){
            bary.y = 1.0;
        }

        bary.z = 1.0 - bary.x - bary.y;

        return bary;
    }

    /// Return orientation (-1 -> clockwise, 0 -> collinear, 1 -> counterclockwise).
    static signed char orientation(const McVec2d &a, const McVec2d &b, const McVec2d &c, const double eps=0.0){
        // McMat3d(a.x, b.x, c.x,  a.y, b.y, c.y,  1, 1, 1).det();
        double det = a.x * (b.y-c.y) - b.x * (a.y - c.y) + c.x * (a.y - b.y);

        if (det>eps)
            return 1;
        else if (det<-eps)
            return -1;

        return 0;
    }

#ifdef _SB_LINEAR_
    /// Constructs a McVec2d from an Inventor SbVec2d.
    McVec2d(const SbVec2s& sv) {
        const short* v = sv.getValue();
        x=v[0]; y=v[1];
    }
#endif
};

#endif

/// @}
