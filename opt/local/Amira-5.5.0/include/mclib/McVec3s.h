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
#ifndef MC_VEC3S_H
#define MC_VEC3S_H

#include "McWinDLLApi.h"
#include "McVec3f.h"

#include <math.h>
#include <assert.h>

/** This class provides a 3D vector of shorts.
    @see McVec2i, McVec4i, McVec2f, McVec3f, McVec4f, McVec3d
*/
class McVec3s
{
  public:
    /// vector's first component.
    short i;
    /// vector's second component.
    short j;
    /// vector's third component.
    short k;

    /// Default constructor doesn't initialize anything.
    McVec3s() {}

    /// Constructor.
    McVec3s(const short i, const short j, const short k) {
        this->i=i; this->j=j; this->k=k;
    }

    /// Other constructor, useful for scale factors (i=j=k=value).
    McVec3s(const short value) { i=j=k=value; }

    /// Copy constructor.
    McVec3s(const McVec3s& v) { i=v.i; j=v.j; k=v.k;}

    /// Assignment.
    McVec3s& operator=(const McVec3s& v) {
        i=v.i; j=v.j; k=v.k; return *this;
    }

    /// Addition.
    McVec3s& operator+=(const McVec3s& v) {
        i+=v.i; j+=v.j; k+=v.k; return *this;
    }

    /// Subtraction.
    McVec3s& operator-=(const McVec3s& v) {
        i-=v.i; j-=v.j; k-=v.k; return *this;
    }

    /// Multiplication.
    McVec3s& operator*=(short d) { i*=d; j*=d; k*=d; return *this; }

    /// Division.
    McVec3s& operator/=(short d) { i/=d; j/=d; k/=d; return *this; }

    /// Index operator. Performs index check via assert().
    short& operator[](int n) { assert(n>=0&&n<=2); return (&i)[n]; }

    /// Const index operator. Performs index check via assert().
    const short& operator[](int n) const { assert(n>=0&&n<=2); return (&i)[n]; }

    /// Sets the vectors components to i, j, and k.
    void setValue(short i, short j, short k) { this->i=i; this->j=j; this->k=k; }

    /// Set the vectors components to ceiling (next bigger)
    /// of f-vec's components.
    void setCeil(const McVec3f& o) {
      this->i = (short) ceil(o.x);
      this->j = (short) ceil(o.y);
      this->k = (short) ceil(o.z);
    }

    /// Set the vectors components to floor (next smaller)
    /// of f-vec's components.
    void setFloor(const McVec3f& o) {
      this->i = (short) floor(o.x);
      this->j = (short) floor(o.y);
      this->k = (short) floor(o.z);
    }

    // FRIENDS

    /// Unary minus.
    friend McVec3s operator-(const McVec3s& a) {
        return McVec3s(-a.i,-a.j,-a.k);
    }

    /// Addition.
    friend McVec3s operator+(const McVec3s& a, const McVec3s& b) {
        return McVec3s(a.i+b.i, a.j+b.j, a.k+b.k);
    }

    /// Subtraction.
    friend McVec3s operator-(const McVec3s& a, const McVec3s& b)
        { return McVec3s(a.i-b.i, a.j-b.j, a.k-b.k); }

    /// Scalar multiplication from right.
    friend McVec3s operator*(const McVec3s& a, short d)
        { return McVec3s(d*a.i, d*a.j, d*a.k); }

    /// Scalar multiplication from left.
    friend McVec3s operator*(short d, const McVec3s& a)
        { return McVec3s(d*a.i, d*a.j, d*a.k); }

    /// Scalar division.
    friend McVec3s operator/(const McVec3s& a, short d)
        { return McVec3s(a.i/d, a.j/d, a.k/d); }

    /// Dot product.
    int dot(const McVec3s& a) const { return (i*a.i + j*a.j + k*a.k); }

    /// Comparison.
    friend int operator == (const McVec3s& a, const McVec3s& b)
        { return (a.i==b.i) && (a.j==b.j) && (a.k==b.k); }

    /// Not equal.
    friend int operator != (const McVec3s& a, const McVec3s& b)
        { return !(a==b); }
};

#endif

/// @}
