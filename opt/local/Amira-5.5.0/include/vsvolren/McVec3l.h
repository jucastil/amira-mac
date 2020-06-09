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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef MC_VEC3L_H
#define MC_VEC3L_H

#include <mclib/McVec3f.h>
#include <mclib/McPrimType.h>

#include <math.h>
#include <assert.h>

/** This class provides a 3D vector of integers.
    @see McVec2i, McVec4i, McVec2f, McVec3f, McVec4f, McVec3d
*/
class McVec3l
{
  public:
    /// vector's first component.
    mclong i;
    /// vector's second component.
    mclong j;
    /// vector's third component.
    mclong k;

    /// Default constructor doesn't initialize anything.
    McVec3l() {}

    /// Constructor.
    McVec3l(const mclong _i, const mclong _j, const mclong _k) {
        this->i=_i; this->j=_j; this->k=_k;
    }

    /// Other constructor, useful for scale factors (i=j=k=value).
    McVec3l(const mclong value) { i=j=k=value; }

    /// from array
    McVec3l (const mclong v[3]) { i = v[0]; j = v[1]; k = v[2]; };

    /// Int constructor, provided for conveniance.
    McVec3l(const int value) { i=j=k=value; }

    /// Int constructor, provided for conveniance.
    McVec3l (const int v[3]) { i = v[0]; j = v[1]; k = v[2]; };

    /// Copy constructor.
    McVec3l(const McVec3l& v) { i=v.i; j=v.j; k=v.k;}

    /// Assignment.
    McVec3l& operator=(const McVec3l& v) {
        i=v.i; j=v.j; k=v.k; return *this;
    }

    /// Addition.
    McVec3l& operator+=(const McVec3l& v) {
        i+=v.i; j+=v.j; k+=v.k; return *this;
    }

    /// Subtraction.
    McVec3l& operator-=(const McVec3l& v) {
        i-=v.i; j-=v.j; k-=v.k; return *this;
    }

    /// Multiplication.
    McVec3l& operator*=(mclong d) { i*=d; j*=d; k*=d; return *this; }

    /// Division.
    McVec3l& operator/=(mclong d) { i/=d; j/=d; k/=d; return *this; }

    /// Index operator. Performs index check via assert().
    mclong& operator[](mclong n) { assert(n>=0&&n<=2); return (&i)[n]; }

    /// Const index operator. Performs index check via assert().
    const mclong& operator[](mclong n) const { assert(n>=0&&n<=2); return (&i)[n]; }

    /// Sets the vectors components to i, j, and k.
    void setValue(mclong _i, mclong _j, mclong _k) { this->i=_i; this->j=_j; this->k=_k; }

    /// Set the vectors components to ceiling (next bigger)
    /// of f-vec's components.
    void setCeil(const McVec3f& o) {
      this->i = (mclong) ceil(o.x);
      this->j = (mclong) ceil(o.y);
      this->k = (mclong) ceil(o.z);
    }

    /// Set the vectors components to floor (next smaller)
    /// of f-vec's components.
    void setFloor(const McVec3f& o) {
      this->i = (mclong) floor(o.x);
      this->j = (mclong) floor(o.y);
      this->k = (mclong) floor(o.z);
    }

    /// convert to an int[3] vector
    void toInt(int * out) const {
        out[0] = (int) i;
        out[1] = (int) j;
        out[2] = (int) k;
    }

    // FRIENDS

    /// Unary minus.
    friend McVec3l operator-(const McVec3l& a) {
        return McVec3l(-a.i,-a.j,-a.k);
    }

    /// Addition.
    friend McVec3l operator+(const McVec3l& a, const McVec3l& b) {
        return McVec3l(a.i+b.i, a.j+b.j, a.k+b.k);
    }

    /// Subtraction.
    friend McVec3l operator-(const McVec3l& a, const McVec3l& b)
        { return McVec3l(a.i-b.i, a.j-b.j, a.k-b.k); }

    /// Scalar multiplication from right.
    friend McVec3l operator*(const McVec3l& a, mclong d)
        { return McVec3l(d*a.i, d*a.j, d*a.k); }

    /// Scalar multiplication from left.
    friend McVec3l operator*(mclong d, const McVec3l& a)
        { return McVec3l(d*a.i, d*a.j, d*a.k); }

    /// Scalar division.
    friend McVec3l operator/(const McVec3l& a, mclong d)
        { return McVec3l(a.i/d, a.j/d, a.k/d); }

    /// Dot product.
    mclong dot(const McVec3l& a) const { return (i*a.i + j*a.j + k*a.k); }

    /// Comparison.
    friend mclong operator == (const McVec3l& a, const McVec3l& b)
        { return (a.i==b.i) && (a.j==b.j) && (a.k==b.k); }

    /// Not equal.
    friend mclong operator != (const McVec3l& a, const McVec3l& b)
        { return !(a==b); }

    /// Component-wise quotient calculation.
    McVec3l compquot (const McVec3l& o) const {
        return McVec3l (i / o.i, j / o.j, k / o.k);
    }

    /// Component-wise product calculation.
    McVec3l compprod (const McVec3l& o) const {
        return McVec3l (i * o.i, j * o.j, k * o.k);
    }

    /// Component-wise modulo calculation.
    McVec3l compmod (const McVec3l& o) const {
        return McVec3l (i % o.i, j % o.j, k % o.k);
    }
};

#endif

/// @}
