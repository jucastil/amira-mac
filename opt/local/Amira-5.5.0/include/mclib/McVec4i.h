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
#ifndef MC_VEC4I_H
#define MC_VEC4I_H

#include "McWinDLLApi.h"

#include <math.h>
#include <assert.h>

/** This class provides a 4D vector of integers.
 @see McVec2i, McVec3i, McVec2f, McVec3f, McVec4f, McVec3d
*/
class McVec4i
{
  public:
    /// vectors first component.
    int i;
    /// vectors second component.
    int j;
    /// vectors third component.
    int k;
    /// vectors fourth component.
    int l;

    /// Default constructor doesn't initialize anything.
    McVec4i() {}

    /// Constructor.
    McVec4i(const int _i, const int _j, const int _k, const int _l) {
        i=_i; j=_j; k=_k, l=_l;
    }

    /// Other constructor, useful for scale factors (i=j=k=l=value).
    McVec4i(const int value) { i=j=k=l=value; }

    /// from array
    McVec4i (const int v[4]) { i = v[0]; j = v[1]; k = v[2]; l = v[3]; };

    /// Copy constructor.
    McVec4i(const McVec4i& v) { i=v.i; j=v.j; k=v.k; l=v.l; }

    /// Assignment.
    McVec4i& operator=(const McVec4i& v) {
        i=v.i; j=v.j; k=v.k; l=v.l; return *this;
    }

    /// Addition.
    McVec4i& operator+=(const McVec4i& v) {
        i+=v.i; j+=v.j; k+=v.k; l+=v.l; return *this;
    }

    /// Subtraction.
    McVec4i& operator-=(const McVec4i& v) {
        i-=v.i; j-=v.j; k-=v.k; l-=v.l; return *this;
    }

    /// Multiplication.
    McVec4i& operator*=(int d) { i*=d; j*=d; k*=d; l*=d; return *this; }

    /// Division.
    McVec4i& operator/=(int d) { i/=d; j/=d; k/=d; l/=d; return *this; }

    /// Index operator. Performs index check via assert().
    int& operator[](int n) { assert(n>=0&&n<=3); return (&i)[n]; }

    /// Const index operator. Performs index check via assert().
    const int& operator[](int n) const { assert(n>=0&&n<=3); return (&i)[n]; }

    /// Sets the vectors components to i, j, k, and l.
    void setValue(int _i, int _j, int _k, int _l) {
        i=_i; j=_j; k=_k; l=_l;
    }

    // FRIENDS

    /// Unary minus.
    friend McVec4i operator-(const McVec4i& a) {
        return McVec4i(-a.i,-a.j,-a.k,-a.l);
    }

    /// Addition.
    friend McVec4i operator+(const McVec4i& a, const McVec4i& b) {
        return McVec4i(a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l);
    }

    /// Subtraction.
    friend McVec4i operator-(const McVec4i& a, const McVec4i& b)
        { return McVec4i(a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l); }

    /// Scalar multiplication from right.
    friend McVec4i operator*(const McVec4i& a, int d)
        { return McVec4i(d*a.i, d*a.j, d*a.k, d*a.l); }

    /// Scalar multiplication from left.
    friend McVec4i operator*(int d, const McVec4i& a)
        { return McVec4i(d*a.i, d*a.j, d*a.k, d*a.l); }

    /// Scalar division.
    friend McVec4i operator/(const McVec4i& a, int d)
        { return McVec4i(a.i/d, a.j/d, a.k/d, a.l/d); }

    /// Comparison.
    friend int operator == (const McVec4i& a, const McVec4i& b)
        { return (a.i==b.i) && (a.j==b.j) && (a.k==b.k) && (a.l==b.l); }

    /// Not equal.
    friend int operator != (const McVec4i& a, const McVec4i& b)
        { return !(a==b); }
};

#endif

/// @}
