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
#ifndef MC_VEC4L_H
#define MC_VEC4L_H

#include "McWinDLLApi.h"
#include "McPrimType.h"

#include <math.h>
#include <assert.h>

/** This class provides a 4D vector of integers of type mclong.
 @see McVec2i, McVec3i, McVec2f, McVec3f, McVec4f, McVec3d, vsvolren/McVec3l
*/
class McVec4l
{
  public:
    /// vectors first component.
    mclong i;
    /// vectors second component.
    mclong j;
    /// vectors third component.
    mclong k;
    /// vectors fourth component.
    mclong l;

    /// Default constructor doesn't initialize anything.
    McVec4l() {}

    /// Constructor.
    McVec4l(const mclong _i, const mclong _j, const mclong _k, const mclong _l) {
        i=_i; j=_j; k=_k, l=_l;
    }

    /// Other constructor, useful for scale factors (i=j=k=l=value).
    McVec4l(const mclong value) { i=j=k=l=value; }

    /// from array
    McVec4l (const mclong v[4]) { i = v[0]; j = v[1]; k = v[2]; l = v[3]; };

    /// Int constructor, provided for conveniance.
    McVec4l(const int value) { i=j=k=l=value; }

    /// Int constructor, provided for conveniance.
    McVec4l (const int v[4]) { i = v[0]; j = v[1]; k = v[2]; l = v[3]; };

    /// Copy constructor.
    McVec4l(const McVec4l& v) { i=v.i; j=v.j; k=v.k; l=v.l; }

    /// Assignment.
    McVec4l& operator=(const McVec4l& v) {
        i=v.i; j=v.j; k=v.k; l=v.l; return *this;
    }

    /// Addition.
    McVec4l& operator+=(const McVec4l& v) {
        i+=v.i; j+=v.j; k+=v.k; l+=v.l; return *this;
    }

    /// Subtraction.
    McVec4l& operator-=(const McVec4l& v) {
        i-=v.i; j-=v.j; k-=v.k; l-=v.l; return *this;
    }

    /// Multiplication.
    McVec4l& operator*=(mclong d) { i*=d; j*=d; k*=d; l*=d; return *this; }

    /// Division.
    McVec4l& operator/=(mclong d) { i/=d; j/=d; k/=d; l/=d; return *this; }

    /// Index operator. Performs index check via assert().
    mclong& operator[](int n) { assert(n>=0&&n<=3); return (&i)[n]; }

    /// Const index operator. Performs index check via assert().
    const mclong& operator[](int n) const { assert(n>=0&&n<=3); return (&i)[n]; }

    /// Sets the vectors components to i, j, k, and l.
    void setValue(mclong _i, mclong _j, mclong _k, mclong _l) {
        i=_i; j=_j; k=_k; l=_l;
    }

    /// convert to an int[4] vector
    void toInt(int * out) const {
        out[0] = (int) i;
        out[1] = (int) j;
        out[2] = (int) k;
        out[3] = (int) l;
    }


    // FRIENDS

    /// Unary minus.
    friend McVec4l operator-(const McVec4l& a) {
        return McVec4l(-a.i,-a.j,-a.k,-a.l);
    }

    /// Addition.
    friend McVec4l operator+(const McVec4l& a, const McVec4l& b) {
        return McVec4l(a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l);
    }

    /// Subtraction.
    friend McVec4l operator-(const McVec4l& a, const McVec4l& b)
        { return McVec4l(a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l); }

    /// Scalar multiplication from right.
    friend McVec4l operator*(const McVec4l& a, mclong d)
        { return McVec4l(d*a.i, d*a.j, d*a.k, d*a.l); }

    /// Scalar multiplication from left.
    friend McVec4l operator*(mclong d, const McVec4l& a)
        { return McVec4l(d*a.i, d*a.j, d*a.k, d*a.l); }

    /// Scalar division.
    friend McVec4l operator/(const McVec4l& a, mclong d)
        { return McVec4l(a.i/d, a.j/d, a.k/d, a.l/d); }

    /// Dot product.
    mclong dot(const McVec4l& a) const { return (i*a.i + j*a.j + k*a.k + l*a.l); }


    /// Comparison.
    friend int operator == (const McVec4l& a, const McVec4l& b)
        { return (a.i==b.i) && (a.j==b.j) && (a.k==b.k) && (a.l==b.l); }

    /// Not equal.
    friend int operator != (const McVec4l& a, const McVec4l& b)
        { return !(a==b); }

    /// Component-wise quotient calculation.
    McVec4l compquot (const McVec4l& o) const {
        return McVec4l (i / o.i, j / o.j, k / o.k, l / o.l);
    }

    /// Component-wise product calculation.
    McVec4l compprod (const McVec4l& o) const {
        return McVec4l (i * o.i, j * o.j, k * o.k, l * o.l);
    }

    /// Component-wise modulo calculation.
    McVec4l compmod (const McVec4l& o) const {
        return McVec4l (i % o.i, j % o.j, k % o.k, l % o.l);
    }

};

#endif

/// @}
