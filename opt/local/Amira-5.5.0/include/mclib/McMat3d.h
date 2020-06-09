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
#ifndef MC_MAT3D_H
#define MC_MAT3D_H

#include "McWinDLLApi.h"
#include <mclib/McVec3d.h>

/// Represents a 3x3 matrix of doubles.
class MCLIB_API McMat3d
{
public:
    /// Default constructor. Does not initialize the matrix.
    McMat3d() {};

    /// Copy constructor.
    McMat3d( const McMat3d& m ) { setValue(m); }

    /// Constructor.
    McMat3d( const double m[3][3] ) { setValue(m); }

    /// Another constructor.
    McMat3d( double a11, double a12, double a13,
             double a21, double a22, double a23,
             double a31, double a32, double a33 );

    /// Constructor that assigns the same value to all components of the matrix.
    explicit McMat3d( const double value ); 

    /// A constructor that takes three column vectors
    McMat3d( const McVec3d &a, const McVec3d &b, const McVec3d &c);

    /// Initializes the matrix.
    McMat3d& setValue( const McMat3d& m );

    /// Initializes the matrix.
    McMat3d& setValue( const double m[3][3] );

    /// Initializes the matrix.
    McMat3d& setValue( double a11, double a12, double a13,
                       double a21, double a22, double a23,
                       double a31, double a32, double a33);

    /// Copies matrix elements into array of doubles.
    void getValue( double m[3][3] ) const;

    /// Set matrix to the identity matrix.
    void makeIdentity();

    /// Returns the identity matrix.
    static McMat3d identity();

    /// Computes the determinant of the matrix.
    double det() const {
        double ad1 = mat[0][0] * (mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1]);
        double ad2 = mat[0][1] * (mat[1][0]*mat[2][2] - mat[1][2]*mat[2][0]);
        double ad3 = mat[0][2] * (mat[1][0]*mat[2][1] - mat[1][1]*mat[2][0]);

        return ad1 - ad2 + ad3;
    }

    /// Computes the subdeterminant i,j [0..2] of the matrix including sign.
    double subdet(int row, int col) const {
        return( (mat[(row+1)%3][(col+1)%3] * mat[(row+2)%3][(col+2)%3]) -
                (mat[(row+1)%3][(col+2)%3] * mat[(row+2)%3][(col+1)%3]) );
    }

    /// Computes the trace
    double trace() const {
        return mat[0][0] + mat[1][1] + mat[2][2];
    }

    /** Returns the inverse of the matrix. The result is undefined if
        the matrix is singular and cannot be inverted. */
    McMat3d inverse() const;

    /** Returns the inverse of the matrix. The method expects the
        determinant of the matrix to be specified as parameter. In this way
        the caller can check for singularity in advance. */
    McMat3d inverse(double det) const;

    /** Returns the inverse if the matrix is known to by symmetrical.
        This method is slightly faster than the standard code. */
    McMat3d symmInverse(double det) const;

    /** Performs an in-place LU decomposition. The algorithm does row
        pivoting. The actual row permutation is returned in @c index.
        The parameter @c d returns the parity of the permutation. */
    int LUDecomposition( int index[3], double &d );

    /// Performs an LU backsubstitution, not yet implemented.
    void LUBackSubstitution( int index[4], double b[4] ) const;

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
    int solveEigenSystem(double eigVal[3], McVec3d eigVec[3]);

    /// Computes eigen values and eigen vectors for symmetric matrices.
    void jacobi(double eigVal[3], McVec3d eigVec[3], int &numRot);

    /// Returns the transposed matrix.
    McMat3d transpose() const;

    /// Performs a matrix multiplication from the right.
    McMat3d& multRight( const McMat3d &m ) { return setValue((*this)*m); }

    /// Performs a matrix multiplication from the left.
    McMat3d& multLeft( const McMat3d &m ) { return setValue(m*(*this)); }

    /// Multiplies a column vector from the right.
    void multMatrixVec( const McVec3d &src, McVec3d &dst ) const;

    /// Multiplies a row vector from the left.
    void multVecMatrix( const McVec3d &src, McVec3d &dst ) const;

    /// Index operator.
    double* operator[]( int i ) { return &mat[i][0]; }

    /// Const index operator.
    const double* operator[]( int i ) const { return &mat[i][0]; }

    /// Assignment operator.
    McMat3d& operator=( const double m[3][3] );

    /// Another assignment operator
    McMat3d& operator=( const McMat3d &m );

    /// Matrix multiplication from the right.
    McMat3d& operator*=( const McMat3d &m ) { return setValue((*this)*m);}

    /// Generic matrix multiplication.
    friend McMat3d operator*(const McMat3d& m1, const McMat3d& m2) {
        McMat3d out;
        for ( int i=0; i<3; i++ ) {
            for ( int j=0; j<3; j++ )
                out.mat[i][j] = m1.mat[i][0]*m2.mat[0][j] +
                                m1.mat[i][1]*m2.mat[1][j] +
                                m1.mat[i][2]*m2.mat[2][j];
        }
        return out;
    }

    /// Check for equality.
    friend int operator ==( const McMat3d &m1, const McMat3d &m2 ) {
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
    friend int operator !=( const McMat3d &m1, const McMat3d &m2 )
        { return !( m1 == m2 ); }

    /// Component-wise multiplication.
    friend McMat3d operator*(const McMat3d& m, double f) { return f*m; }

    /// Component-wise division.
    friend McMat3d operator/(double f, const McMat3d& m) { return (1./f)*m; }

    /// Component-wise division.
    friend McMat3d operator/(const McMat3d& m, double f) { return (1./f)*m; }

    /// Component-wise multiplication.
    friend McMat3d operator*(double f, const McMat3d& m) {
        return McMat3d(
            f*m[0][0], f*m[0][1], f*m[0][2],
            f*m[1][0], f*m[1][1], f*m[1][2],
            f*m[2][0], f*m[2][1], f*m[2][2]);
    }

    /// Matrix addition.
    friend McMat3d operator+(const McMat3d& a, const McMat3d& b) {
        return McMat3d(
            a[0][0]+b[0][0],a[0][1]+b[0][1],a[0][2]+b[0][2],
            a[1][0]+b[1][0],a[1][1]+b[1][1],a[1][2]+b[1][2],
            a[2][0]+b[2][0],a[2][1]+b[2][1],a[2][2]+b[2][2]);
    }

    /// Matrix subtraction.
    friend McMat3d operator-(const McMat3d& a, const McMat3d& b) {
        return McMat3d(
            a[0][0]-b[0][0],a[0][1]-b[0][1],a[0][2]-b[0][2],
            a[1][0]-b[1][0],a[1][1]-b[1][1],a[1][2]-b[1][2],
            a[2][0]-b[2][0],a[2][1]-b[2][1],a[2][2]-b[2][2]);
    }


protected:
    /// The 3 x 3 matrix elements.
    double mat[3][3];
};

#endif

/// @}
