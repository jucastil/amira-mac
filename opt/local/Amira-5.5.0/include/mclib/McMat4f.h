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
#ifndef MC_MAT4_H
#define MC_MAT4_H

#include "McWinDLLApi.h"
#include "McVec3f.h"
#include "McVec4f.h"
#include "McRotation.h"

#include <stdio.h>

/// Represents a 4x4 matrix of floats.
class MCLIB_API McMat4f
{
  public:
    /// Default constructor.
    McMat4f() {}

    /// Copy constructor.
    McMat4f( const McMat4f& m ) { setValue(m); }

    /// Constructor.
    McMat4f( const float m[4][4] ) { setValue(m); }

    /// Another constructor.
    McMat4f( float a11, float a12, float a13, float a14,
               float a21, float a22, float a23, float a24,
               float a31, float a32, float a33, float a34,
               float a41, float a42, float a43, float a44 );

    /// Initializes the matrix.
    McMat4f& setValue( const McMat4f& m );

    /// Initializes the matrix.
    McMat4f& setValue( const float m[4][4] );

    /// Initializes the matrix.
    McMat4f& setValue( float a11, float a12, float a13, float a14,
                   float a21, float a22, float a23, float a24,
                   float a31, float a32, float a33, float a34,
                   float a41, float a42, float a43, float a44 );

    /// Copies matrix elements into array of floats.
    void getValue( float m[4][4] ) const;

    /// Set matrix to the identity matrix.
    void makeIdentity();

    /// Returns the identity matrix.
    static McMat4f identity();

    /// Sets matrix to rotate by given rotation.
    void setRotate( const McRotation &q );

    /// Sets matrix to scale by given scale factor.
    void setScale( float s );

    /// Sets matrix to scale by given scale vector.
    void setScale( const McVec3f &s );

    /// Sets matrix to translate by given translation vector.
    void setTranslate( const McVec3f &t );

    /// Composes the matrix based on a translation, rotation, and scale.
    void setTransform( const McVec3f &translation,
                       const McRotation &rotation,
                       const McVec3f &scaleFactor ) {
        setTransform(translation,rotation,scaleFactor,McRotation(0,0,0,1),McVec3f(0,0,0));
    }

    /** Composes the matrix based on a translation, rotation, scale,
        and orientation for scale. @c scaleOrientation chooses the
        primary axes for the scale. */
    void setTransform( const McVec3f &translation,
                       const McRotation &rotation,
                       const McVec3f &scaleFactor,
                       const McRotation &scaleOrientation ) {
        setTransform(translation,rotation,scaleFactor,scaleOrientation,McVec3f(0,0,0));
    }

    /** Composes the matrix based on a translation, rotation, scale,
        orientation for scale, and center. @c center is the center
        point for scaling and rotation. @c scaleOrientation chooses the
        primary axes for the scale. */
    void setTransform( const McVec3f &translation,
                       const McRotation &rotation,
                       const McVec3f &scaleFactor,
                       const McRotation &scaleOrientation,
                       const McVec3f &center );

    /** Decomposes matrix in translation, rotation, scalefactor,
        scaleOrientation. */
    void getTransform(McVec3f &translation,
                      McRotation &rotation,
                      McVec3f &scaleFactor,
                      McRotation &scaleOrientation,
                      const McVec3f &center) const;

    /** Decomposes matrix in translation, rotation, scalefactor,
        scaleOrientation. */
    void getTransform(McVec3f &t, McRotation &r,
                      McVec3f &s, McRotation &so) const
    { getTransform(t, r, s, so, McVec3f(0,0,0)); }

    /// Computes the determinant of the upper left 3x3matrix.
    float det3() const;

    /** Computes the determinant of 3x3matrix
        @f$(r_i, c_j)_{i,j}$, $i,j \in \{1,2,3\}@f$.*/
    float det3( int r1, int r2, int r3, int c1, int c2, int c3 ) const;

    /// Computes the determinant of the 4x4matrix.
    float det4() const;

    /** Factors a matrix m into 5 pieces: m = r s r^ u t, where r^
        means transpose of r, and r and u are rotations, s is a scale,
        and t is a translation. Any projection information is returned
        in proj (TODO: The latter is not implemented yet). */
    int factor( McMat4f &r, McVec3f &s, McMat4f &u,
                McVec3f &t, McMat4f &proj ) const;

    /** Returns the inverse of the matrix. The result is undefined if
        the matrix is singular and cannot be inverted. */
    McMat4f inverse() const;

    /// Computes the inverse of an affine matrix.
    int affine_inverse(const McMat4f &in, McMat4f &out) const;

    /** Performs an in-place LU decomposition. The algorithm does row
        pivoting. The actual row permutation is returned in @c index.
        The parameter @c d returns the parity of the permutation. */
    int LUDecomposition( int index[4], float &d );

    /// Performs an LU backsubstitution, not yet implemented.
    void LUBackSubstitution( int index[4], float b[4] ) const;

    /// Returns the transposed matrix.
    McMat4f transpose() const;

    /// Performs a matrix multiplication from the right.
    McMat4f& multRight( const McMat4f &m ) { return setValue((*this)*m); }

    /// Performs a matrix multiplication from the left.
    McMat4f& multLeft( const McMat4f &m ) { return setValue(m*(*this)); }

    /** Performs a matrix multiplication from right using homogeneous
        coordinates.
        @f$ \mbox{McMat4f} *
        \left( \begin{tabular}{c} src\\ 1 \\ \end{tabular} \right)
        =\left( \begin{tabular}{c} dst\\ 1 \\ \end{tabular} \right)@f$ */
    void multMatrixVec( const McVec3f &src, McVec3f &dst ) const;

    /** Performs a matrix multiplication from left using homogeneous
        coordinates.
        @f$ \left( \begin{tabular}{c} src\\ 1 \\ \end{tabular} \right) *
        \mbox{McMat4f}
        =\left( \begin{tabular}{c} dst\\ 1 \\ \end{tabular} \right)@f$ */
    void multVecMatrix( const McVec3f &src, McVec3f &dst ) const;

    /** Multiplies a row vector with the matrix. The vector is assumed to be a
        direction vector, thus the translation and perspective division parts of
        the matrix are not taken into account. */
    void multDirMatrix( const McVec3f &src, McVec3f &dst ) const;

    /// Multiplies a column vector from the right.
    void multMatrixVec( const McVec4f &src, McVec4f &dst ) const;

    /// Multiplies a row vector from the left.
    void multVecMatrix( const McVec4f &src, McVec4f &dst ) const;

    /// Diagonalize upper left 3x3 block matrix.
    void jacobi3(float evalues[3], McVec3f evectors[3], int &rots) const;

    /// Prints a formatted version of the matrix to the given file pointer.
    void print( FILE *fp ) const;

    /// Index operator.
    float* operator[]( int i ) { return &a[i][0]; }

    /// Const index operator.
    const float* operator[]( int i ) const { return &a[i][0]; }

    /// Assignment operator.
    McMat4f& operator=( const float m[4][4] );

    /// Another assignment operator
    McMat4f& operator=( const McMat4f &m );

    /// Set the matrix from a McRotation.
    McMat4f& operator=( const McRotation &q ) { setRotate(q); return *this; }

    /// Matrix multiplication from the right.
    McMat4f& operator*=( const McMat4f &m ) { return multRight(m); }

    /// Generic matrix multiplication.
    friend McMat4f operator*(const McMat4f& m1, const McMat4f& m2) {
        McMat4f out;
        for ( int i=0; i<4; i++ ) {
            for ( int j=0; j<4; j++ ) {
                out.a[i][j] = 0.0f;
                for ( int k=0; k<4; k++)
                    out.a[i][j] += m1.a[i][k] * m2.a[k][j];
            }
        }
        return out;
    }

    /// Check for equality.
    friend int operator ==( const McMat4f &m1, const McMat4f &m2 ) {
        return (m1.a[0][0] == m2.a[0][0] &&
                m1.a[0][1] == m2.a[0][1] &&
                m1.a[0][2] == m2.a[0][2] &&
                m1.a[0][3] == m2.a[0][3] &&
                m1.a[1][0] == m2.a[1][0] &&
                m1.a[1][1] == m2.a[1][1] &&
                m1.a[1][2] == m2.a[1][2] &&
                m1.a[1][3] == m2.a[1][3] &&
                m1.a[2][0] == m2.a[2][0] &&
                m1.a[2][1] == m2.a[2][1] &&
                m1.a[2][2] == m2.a[2][2] &&
                m1.a[2][3] == m2.a[2][3] &&
                m1.a[3][0] == m2.a[3][0] &&
                m1.a[3][1] == m2.a[3][1] &&
                m1.a[3][2] == m2.a[3][2] &&
                m1.a[3][3] == m2.a[3][3]);
    }

    /// Check for inequality.
    friend int operator !=( const McMat4f &m1, const McMat4f &m2 )
        { return !( m1 == m2 ); }

    /// Component-wise multiplication.
    friend McMat4f operator*(const McMat4f& m, float f) { return f*m; }

    /// Component-wise division.
    friend McMat4f operator/(const McMat4f& m, float f) { return (1.f/f)*m; }

    /// Component-wise multiplication.
    friend McMat4f operator*(float f, const McMat4f& m) {
        return McMat4f(
            f*m[0][0],f*m[0][1],f*m[0][2],f*m[0][3],
            f*m[1][0],f*m[1][1],f*m[1][2],f*m[1][3],
            f*m[2][0],f*m[2][1],f*m[2][2],f*m[2][3],
            f*m[3][0],f*m[3][1],f*m[3][2],f*m[3][3]);
    }

    /// Matrix addition.
    friend McMat4f operator+(const McMat4f& a, const McMat4f& b) {
        return McMat4f(
            a[0][0]+b[0][0],a[0][1]+b[0][1],a[0][2]+b[0][2],a[0][3]+b[0][3],
            a[1][0]+b[1][0],a[1][1]+b[1][1],a[1][2]+b[1][2],a[1][3]+b[1][3],
            a[2][0]+b[2][0],a[2][1]+b[2][1],a[2][2]+b[2][2],a[2][3]+b[2][3],
            a[3][0]+b[3][0],a[3][1]+b[3][1],a[3][2]+b[3][2],a[3][3]+b[3][3]);
    }

    /// Matrix subtraction.
    friend McMat4f operator-(const McMat4f& a, const McMat4f& b) {
        return McMat4f(
            a[0][0]-b[0][0],a[0][1]-b[0][1],a[0][2]-b[0][2],a[0][3]-b[0][3],
            a[1][0]-b[1][0],a[1][1]-b[1][1],a[1][2]-b[1][2],a[1][3]-b[1][3],
            a[2][0]-b[2][0],a[2][1]-b[2][1],a[2][2]-b[2][2],a[2][3]-b[2][3],
            a[3][0]-b[3][0],a[3][1]-b[3][1],a[3][2]-b[3][2],a[3][3]-b[3][3]);
    }

#ifndef WIN32
#ifdef _SB_LINEAR_
    McMat4f (const SbMatrix& m) {
        setValue (m.getValue ());
    }
#endif
#endif

  protected:
    /// The 4 x 4 matrix elements.
    float a[4][4];
};

#endif

/// @}
