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
#ifndef MC_VEC2I_H
#define MC_VEC2I_H

#include "McWinDLLApi.h"
#include "McStdlib.h"

#include <math.h>
#include <assert.h>

/** This class provides a 2D vector of integers.
    @see McVec3i, McVec4i, McVec2f, McVec3f, McVec4f, McVec3d
*/
class McVec2i
{
  public:
    /// Vector's first component.
    int x;
    /// Vector's second component.
    int y;

    /// Default constructor does not initialize anything.
    McVec2i() {}

    /// Initializing constructor.
    McVec2i(const int _x, const int _y) { this->x = _x; this->y = _y; }

    /// Other constructor, useful for scale factors (x=y=xy).
    McVec2i(const int xy) { this->x = xy; this->y = xy; }

    /// Copy constructor.
    McVec2i(const McVec2i& v) { x = v.x; y = v.y; }

    /// Sets the vectors components to x and y.
    void setValue(const int _x, const int _y) { this->x = _x; this->y = _y; }

    /// Assignment.
    McVec2i& operator=(const McVec2i& v) { x=v.x; y=v.y; return *this; }

    /// Addition.
    McVec2i& operator+=(const McVec2i& v) { x+=v.x; y+=v.y; return *this; }

    /// Subtraction.
    McVec2i& operator-=(const McVec2i& v) { x-=v.x; y-=v.y; return *this; }

    /// Multiplication.
    McVec2i& operator*=(const int d) { x*=d; y*=d; return *this; }

    /// Division.
    McVec2i& operator/=(const int d) { x/=d; y/=d; return *this; }

    /// Index operator. Performs index check via assert().
    int& operator[](int i) { assert(i>=0 && i<=1); return (&x)[i]; }

    /// Const index operator. Performs index check via assert().
    const int& operator[](int i) const { assert(i>=0 && i<=1); return (&x)[i]; }

    // SPECIAL FUNCTIONS

    /// Euclidean length.
    float length() const {
        return MC_fhypot(y,x);
    }

    /// Squared length.
    int length2() { return x*x + y*y; }

    // FRIENDS

    /// Unary minus.
    friend McVec2i operator-(const McVec2i& a) { return McVec2i(-a.x,-a.y); }

    /// Addition.
    friend McVec2i operator+(const McVec2i& a, const McVec2i& b)
    { return McVec2i(a.x+b.x, a.y+b.y); }

    /// Subtraction.
    friend McVec2i operator-(const McVec2i& a, const McVec2i& b)
    { return McVec2i(a.x-b.x, a.y-b.y); }

    /// Scalar multiplication from right.
    friend McVec2i operator*(const McVec2i& a, const int d)
    { return McVec2i(d*a.x, d*a.y); }

    /// Scalar multiplication from left.
    friend McVec2i operator*(const int d, const McVec2i& a)
    { return McVec2i(d*a.x, d*a.y); }

    /// Scalar division.
    friend McVec2i operator/(const McVec2i& a, const int d)
    { return McVec2i(a.x/d, a.y/d); }

    /// Dot product.
    int dot(const McVec2i& a) { return (x*a.x + y*a.y); }

    /// Comparison.
    friend int operator == (const McVec2i& a, const McVec2i& b)
    { return (a.x==b.x) && (a.y==b.y); }

    /// Not equal.
    friend int operator != (const McVec2i& a, const McVec2i& b)
    { return !(a==b); }

    /// Computes new vector from minimal components of a and b.
    friend McVec2i mcmin(const McVec2i& a, const McVec2i& b);

    /// Computes new vector from maximal components of a and b.
    friend McVec2i mcmax(const McVec2i& a, const McVec2i& b);
};

inline McVec2i mcmin(const McVec2i& a, const McVec2i& b)
    { return McVec2i((a.x<b.x)?a.x:b.x, (a.y<b.y)?a.y:b.y); }

inline McVec2i mcmax(const McVec2i& a, const McVec2i& b)
    { return McVec2i((a.x>b.x)?a.x:b.x, (a.y>b.y)?a.y:b.y); }

#endif

/// @}
