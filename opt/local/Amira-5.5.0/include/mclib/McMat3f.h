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
#ifndef MC_MAT3F_H
#define MC_MAT3F_H

#include "McWinDLLApi.h"
#include "McVec3f.h"

#include <stdio.h>

#ifdef HX_HAS_STDIOSTREAM
    #include <iostream>
    using std::ostream;
#else
    #include <iostream.h>
#endif

/// Represents a 3x3 matrix of floats.
class MCLIB_API McMat3f
{
public:
    /// Default constructor. Does not initialize the matrix.
    McMat3f() {};

    /// Copy constructor.
    McMat3f( const McMat3f& m ) { setValue(m); }

    /// Constructor.
    McMat3f( const float m[3][3] ) { setValue(m); }

    /// Another constructor.
    McMat3f( float a11, float a12, float a13,
             float a21, float a22, float a23,
             float a31, float a32, float a33 );

    /// Constructor that assigns the same value to all components of the matrix.
    explicit McMat3f( const float value );

    /// A constructor that takes three column vectors
    McMat3f( const McVec3f &a, const McVec3f &b, const McVec3f &c);

    /// Initializes the matrix.
    McMat3f& setValue( const McMat3f& m );

    /// Initializes the matrix.
    McMat3f& setValue( const float m[3][3] );

    /// Initializes the matrix.
    McMat3f& setValue( float a11, float a12, float a13,
                       float a21, float a22, float a23,
                       float a31, float a32, float a33);

    /// Print matrix to given file pointer
    void print(FILE *fp) const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                fprintf(fp, "%10.5g%c", mat[i][j], j < 2 ? '\t' : '\n');
    }

    /// Copies matrix elements into array of floats.
    void getValue( float m[3][3] ) const;

    /// Set matrix to the identity matrix.
    void makeIdentity();

    /// Returns the identity matrix.
    static McMat3f identity();

    /// Computes the determinant of the matrix.
    float det() const {
        float ad1 = mat[0][0] * (mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1]);
        float ad2 = mat[0][1] * (mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0]);
        float ad3 = mat[0][2] * (mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);

        return ad1 - ad2 + ad3;
    }

    /// Computes the subdeterminant i,j [0..2] of the matrix including sign.
    float subdet(int row, int col) const {
        return( (mat[(row+1)%3][(col+1)%3] * mat[(row+2)%3][(col+2)%3]) -
                (mat[(row+1)%3][(col+2)%3] * mat[(row+2)%3][(col+1)%3]) );
    }

    /// Computes the trace
    float trace() const {
        return mat[0][0] + mat[1][1] + mat[2][2];
    }

    /** Returns the inverse of the matrix. The result is undefined if
        the matrix is singular and cannot be inverted. */
    McMat3f inverse() const;

    /** Returns the inverse of the matrix. The method expects the
        determinant of the matrix to be specified as parameter. In this way
        the caller can check for singularity in advance. */
    McMat3f inverse(float det) const;

    /** Returns the inverse if the matrix is known to by symmetrical.
        This method is slightly faster than the standard code. */
    McMat3f symmInverse(float det) const;

    /** Performs an in-place LU decomposition. The algorithm does row
        pivoting. The actual row permutation is returned in @c index.
        The parameter @c d returns the parity of the permutation. */
    int LUDecomposition( int index[3], float &d );

    /** Computes eigen values and eigen vectors.  In contrast to the
        jacobi function, this function also works for non-symmetric
        matrices.

        A 3x3 matrix can either have 3 real or 1 real and two complex
        eigen values and eigen vectors.

        The function returns the number of real solutions.  The result
        encoding depends on the return value.  If it is 3, all eigen
        values and eigen vectors are real.  If it is 1, the real eigen
        value and vector is stored in eigVal[0] and eigVec[0],
        respectively. The complex eigen values and vectors are given
        by (eigVal[1] + i eigVal[2]) and (eigVec[1] + i eigVec[2]) and
        its complex conjugate, i.e. (eigVal[1] - i eigVal[2]) and
        (eigVec[1] - i eigVec[2]).

        Note, that the computed eigen vectors are only correct, if the
        dimensionality of the eigen space of the associated eigen
        value is 1, i.e. the eigen value occurs only once.
    */
    int solveEigenSystem(float eigVal[3], McVec3f eigVec[3]);

    /// Computes eigen values and eigen vectors for symmetric matrices.
    void jacobi(float eigVal[3], McVec3f eigVec[3], int &numRot);

    /// Performs an LU backsubstitution, not yet implemented.
    void LUBackSubstitution( int index[4], float b[4] ) const;

    /// Returns the transposed matrix.
    McMat3f transpose() const;

    /// Performs a matrix multiplication from the right.
    McMat3f& multRight( const McMat3f &m ) { return setValue((*this)*m); }

    /// Performs a matrix multiplication from the left.
    McMat3f& multLeft( const McMat3f &m ) { return setValue(m*(*this)); }

    /// Multiplies a column vector from the right.
    void multMatrixVec( const McVec3f &src, McVec3f &dst ) const;

    /// Multiplies a row vector from the left.
    void multVecMatrix( const McVec3f &src, McVec3f &dst ) const;

    /// Index operator.
    float* operator[]( int i ) { return &mat[i][0]; }

    /// Const index operator.
    const float* operator[]( int i ) const { return &mat[i][0]; }

    /// Assignment operator.
    McMat3f& operator=( const float m[3][3] );

    /// Another assignment operator
    McMat3f& operator=( const McMat3f &m );

    /// Matrix multiplication from the right.
    McMat3f& operator*=( const McMat3f &m ) { return setValue((*this)*m);}

    /// Generic matrix multiplication.
    friend McMat3f operator*(const McMat3f& m1, const McMat3f& m2) {
        McMat3f out;
        for ( int i=0; i<3; i++ ) {
            for ( int j=0; j<3; j++ )
                out.mat[i][j] = m1.mat[i][0]*m2.mat[0][j] +
                                m1.mat[i][1]*m2.mat[1][j] +
                                m1.mat[i][2]*m2.mat[2][j];
        }
        return out;
    }

    /// Check for equality.
    friend int operator ==( const McMat3f &m1, const McMat3f &m2 ) {
        return (m1.mat[0][0] == m2.mat[0][0] &&
                m1.mat[0][1] == m2.mat[0][1] &&
                m1.mat[0][2] == m2.mat[0][2] &&
                m1.mat[1][0] == m2.mat[1][0] &&
                m1.mat[1][1] == m2.mat[1][1] &&
                m1.mat[1][2] == m2.mat[1][2] &&
                m1.mat[2][0] == m2.mat[2][0] &&
                m1.mat[2][1] == m2.mat[2][1] &&
                m1.mat[2][2] == m2.mat[2][2]);
    }

    /// Check for inequality.
    friend int operator !=( const McMat3f &m1, const McMat3f &m2 )
        { return !( m1 == m2 ); }

    /// Component-wise multiplication.
    friend McMat3f operator*(const McMat3f& m, float f) { return f*m; }

    /// Component-wise division.
    friend McMat3f operator/(float f, const McMat3f& m) { return (1.f/f)*m; }

    /// Component-wise division.
    friend McMat3f operator/(const McMat3f& m, float f) { return (1.f/f)*m; }

    /// Component-wise multiplication.
    friend McMat3f operator*(float f, const McMat3f& m) {
        return McMat3f(
            f*m[0][0], f*m[0][1], f*m[0][2],
            f*m[1][0], f*m[1][1], f*m[1][2],
            f*m[2][0], f*m[2][1], f*m[2][2]);
    }

    /// Matrix addition.
    friend McMat3f operator+(const McMat3f& a, const McMat3f& b) {
        return McMat3f(
            a[0][0]+b[0][0],a[0][1]+b[0][1],a[0][2]+b[0][2],
            a[1][0]+b[1][0],a[1][1]+b[1][1],a[1][2]+b[1][2],
            a[2][0]+b[2][0],a[2][1]+b[2][1],a[2][2]+b[2][2]);
    }

    /// Matrix subtraction.
    friend McMat3f operator-(const McMat3f& a, const McMat3f& b) {
        return McMat3f(
            a[0][0]-b[0][0],a[0][1]-b[0][1],a[0][2]-b[0][2],
            a[1][0]-b[1][0],a[1][1]-b[1][1],a[1][2]-b[1][2],
            a[2][0]-b[2][0],a[2][1]-b[2][1],a[2][2]-b[2][2]);
    }

    /// Write matrix elements to given output stream
    friend ostream& operator<<(ostream& os, const McMat3f& mat);

protected:
    /// The 3 x 3 matrix elements.
    float mat[3][3];
};

#endif

/// @}
