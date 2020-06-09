/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_MATRIX_
#define _SB_MATRIX_

#include <Inventor/SbBase.h>
#include <Inventor/STL/iostream>
#include <Inventor/SbVec.h>

class SbLine;
class SbRotation;
class SbRotationd;
class SbMatrixd;

typedef float SbMat[4][4];
typedef float SbMat3[3][3];
typedef double SbMatd[4][4];

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbMatrix
//
//  4x4 matrix of floating-point elements.
//
//////////////////////////////////////////////////////////////////////////////



/**
* 4x4 matrix class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4x4 matrix class/datatype used by many Open Inventor node and action classes.
* 
*   Matrices are stored in column-major order. So m[i][j] is the value in column 
*   i and row j (just like OpenGL matrices, but unlike classic C/C++ 2d arrays). 
*   For example, in a 4x4 transform matrix the translation X, Y, Z values are in 
*   m[3][0], m[3][1] and m[3][2].
*
*   Open Inventor considers coordinates to be row vectors.  Therefore use the
*   multVecMatrix() method to transform a position from object coordinates to 
*   world coordinates. However use the multDirMatrix() matrix to transform a 
*   normal vector (using the inverse transpose of the matrix).
*
*   Correspondingly transforms are applied "left to right".  So use the multLeft()
*   method to concatenate a transform onto the cumulative modeling matrix.
*
* @SEE_ALSO
*    SbMatrix3,
*    SbMatrixd,
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,16}]
*/

class INVENTORBASE_API SbMatrix {
public:

  /**
  * Default constructor.  The matrix is not initialized.
  */
  SbMatrix()    { }

  /**
  * Constructor.
  */
  SbMatrix(float a11, float a12, float a13, float a14,
    float a21, float a22, float a23, float a24,
    float a31, float a32, float a33, float a34,
    float a41, float a42, float a43, float a44);

  /**
  * Constructor.
  */
  SbMatrix(const SbMat &m);

  /**
  * Sets value from 4x4 array of elements.
  */
  void  setValue(const SbMat &m);
  /** [OIVJAVA-WRAPPER-NO-WRAP] */
  void    setValue(const float *pMat)
  {
    matrix[0][0] = *pMat++ ;
    matrix[0][1] = *pMat++ ;
    matrix[0][2] = *pMat++ ;
    matrix[0][3] = *pMat++ ;

    matrix[1][0] = *pMat++ ;
    matrix[1][1] = *pMat++ ;
    matrix[1][2] = *pMat++ ;
    matrix[1][3] = *pMat++ ;

    matrix[2][0] = *pMat++ ;
    matrix[2][1] = *pMat++ ;
    matrix[2][2] = *pMat++ ;
    matrix[2][3] = *pMat++ ;

    matrix[3][0] = *pMat++ ;
    matrix[3][1] = *pMat++ ;
    matrix[3][2] = *pMat++ ;
    matrix[3][3] = *pMat++ ;
  } ;

  /**
  * Sets value from a double precision matrix.
  */
  void  setValue(const SbMatrixd &md) ;

public:

  /**
  * Sets matrix to be identity.
  */
  void  makeIdentity();

  /**
  * Returns an identity matrix.
  */
  static SbMatrix  identity();

  /**
  * Sets matrix to rotate by given rotation.
  */
  void  setRotate(const SbRotation &q);

  /**
  * Sets matrix to scale by given uniform factor.
  */
  void  setScale(float s);

  /**
  * Sets matrix to scale by given vector.
  */
  void  setScale(const SbVec3f &s);

  /**
  * Sets matrix to translate by given vector.
  */
  void  setTranslate(const SbVec3f &t);

  /**
  * Composes the matrix based on a translation, rotation, scale, orientation for
  * scale, and center. The @B scaleOrientation @b chooses the primary axes for the scale.
  * The @B center @b is the center point for scaling and rotation.
  */
  void  setTransform(const SbVec3f &translation,
    const SbRotation &rotation,
    const SbVec3f &scaleFactor,
    const SbRotation &scaleOrientation,
    const SbVec3f &center);
  /**
  * Composes the matrix based on a translation, rotation, and scale.  A scale orientation
  * value of (0,0,0,1) is used. The center point for scaling and rotation is (0,0,0).
  */
  void setTransform(const SbVec3f &t, const SbRotation &r, const SbVec3f &s);

  /**
  * Composes the matrix based on a translation, rotation, scale, and orientation for
  * scale. The @B scaleOrientation @b chooses the primary axes for the scale. The
  * center point for scaling and rotation is (0,0,0).
  */
  void setTransform(const SbVec3f &t, const SbRotation &r,
    const SbVec3f &s, const SbRotation &so);

  /**
  * Decomposes the matrix into a translation, rotation, scale, and scale
  * orientation. Any projection information is discarded. The decomposition depends
  * upon choice of center point for rotation and scaling, which is optional as the
  * last parameter. Note that if the center is 0, decompose() is the same as
  * factor() where t is @B translation, @b u is @B rotation, @b s is
  * @B scaleFactor, @b and r is @B scaleOrientation. @b
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{Decomposition}]
  */
  void  getTransform(SbVec3f &translation,
    SbRotation &rotation,
    SbVec3f &scaleFactor,
    SbRotation &scaleOrientation,
    const SbVec3f &center) const;
  /**
  * Return translation, rotation, scale, and scale orientation components of the
  * matrix.
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{Decomposition}]
  */
  void  getTransform(SbVec3f &t, SbRotation &r,
    SbVec3f &s, SbRotation &so) const;


  // The following methods return matrix values and other info:

  /**
  * Returns 4x4 array of elements.
  */
  void  getValue(SbMat &m) const;

#ifdef _WIN32
  /**
  * Returns 4x4 array of elements.
  */
  SbMat &getValue() { SbMat &rMat = matrix; return rMat; }
#endif
  /**
  * Returns 4x4 array of elements.
  */
  const SbMat &getValue() const { return matrix; }


  /**
  * Returns determinant of 3x3 submatrix composed of given row and column indices
  * (0-3 for each).
  */
  float  det3(int r1, int r2, int r3, int c1, int c2, int c3) const;

  /**
  * Returns determinant of upper-left 3x3 submatrix.
  */
  float  det3() const { return det3(0, 1, 2, 0, 1, 2); }

  /**
  * Returns determinant of entire matrix.
  */
  float  det4() const;

  /**
  * Factors a matrix m into 5 pieces: m = r s r^ u t, where r^ means transpose of r,
  * and r and u are rotations, s is a scale, and t is a translation. Any projection
  * information is returned in @B proj@b.
  * [OIVJAVA-WRAPPER PACK{Factorization}]
  */
  SbBool factor(SbMatrix &r, SbVec3f &s, SbMatrix &u,
    SbVec3f &t, SbMatrix &proj) const;

  /**
  * Returns inverse of matrix. Results are undefined for singular matrices. Uses LU
  * decomposition.
  */
  SbMatrix  inverse() const;

  /**
  * Perform in-place LU decomposition of matrix. @B index @b is index of rows in
  * matrix. @B d @b is the parity of row swaps. Returns FALSE if singular.
  */
  SbBool  LUDecomposition(int index[4], float &d);

  /**
  * Perform back-substitution on LU-decomposed matrix. Index is permutation of rows
  * from original matrix.
  */
  void  LUBackSubstitution(int index[4], float b[4]) const;

  /**
  * Returns transpose of matrix.
  */
  SbMatrix  transpose() const;


  // The following methods provide Mx/mx and mx/vec arithmetic:

  /**
  * Multiplies matrix by given matrix on right.
  */
  SbMatrix &multRight(const SbMatrix &m);
  /**
  * Multiplies matrix by given matrix on left.
  */
  SbMatrix &multLeft(const SbMatrix &m);

  /**
  * Multiplies matrix by given column vector, giving vector result.
  */
  void  multMatrixVec(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result.
  */
  inline void  multVecMatrix(const SbVec3f &src, SbVec3f &dst) const
  {
    float    x,y,z,w;

    x = src[0]*matrix[0][0] + src[1]*matrix[1][0] +
        src[2]*matrix[2][0] + matrix[3][0];
    y = src[0]*matrix[0][1] + src[1]*matrix[1][1] +
        src[2]*matrix[2][1] + matrix[3][1];
    z = src[0]*matrix[0][2] + src[1]*matrix[1][2] +
        src[2]*matrix[2][2] + matrix[3][2];
    w = src[0]*matrix[0][3] + src[1]*matrix[1][3] +
        src[2]*matrix[2][3] + matrix[3][3];

    w = 1.f/w;
    dst.setValue(x*w, y*w, z*w);
  }

  /**
  * Multiplies matrix by given column vector, giving vector result in Homogeneous coordinate.
  * [OIVJAVA-WRAPPER NAME{multMatrixVec4}]
  */
  void  multMatrixVec(const SbVec3f &src, SbVec4f &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result in Homogeneous coordinates.
  * Use this method to transform points from object coordinates to world coordinates.
  * [OIVJAVA-WRAPPER NAME{multVec4Matrix}]
  */
  void  multVecMatrix(const SbVec3f &src, SbVec4f &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result. src is assumed to
  * be a direction vector, so translation part of matrix is ignored. Note: if you
  * wish to transform surface points and normals by a matrix, call
  * multVecMatrix() for the points and call multDirMatrix() on the
  * inverse transpose of the matrix for the normals.
  */
  void  multDirMatrix(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Multiplies the given line's origin by the matrix, and the line's direction by
  * the rotation portion of the matrix.
  */
  void  multLineMatrix(const SbLine &src, SbLine &dst) const;


  // The following methods are miscellaneous Mx functions:

  /**
  * Prints a formatted version of the matrix to the given file pointer.
  */
  void  print(FILE *fp) const;


  /**
  * Cast: returns pointer to storage of first element.
  */
  operator float *() { return &matrix[0][0]; }

  /**
  * Cast: returns reference to 4x4 array.
  */
  operator SbMat &() { return matrix; }

  /**
  * Make it look like a usual matrix (so you can do m[3][2]).
  */
  float * operator [](int i)   { return &matrix[i][0]; }

  /**
  * Make it look like a usual matrix (so you can do m[3][2]).
  */
  const float * operator [](int i) const  { return &matrix[i][0]; }

  /**
  * Sets value from 4x4 array of elements.
  */
  SbMatrix & operator =(const SbMat &m);

  /**
  * Set the matrix from another SbMatrix.
  */
  SbMatrix & operator =(const SbMatrix &m);

  /**
  * Set the matrix from an SbRotation.
  */
  SbMatrix & operator =(const SbRotation &q)  { setRotate(q); return *this; }

  /**
  * Performs right multiplication with another matrix.
  */
  SbMatrix & operator *=(const SbMatrix &m)  { return multRight(m); }

  /**
  * Binary multiplication of matrices.
  */
  INVENTORBASE_API friend SbMatrix operator *(const SbMatrix &m1, const SbMatrix &m2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbMatrix &m1, const SbMatrix &m2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbMatrix &m1, const SbMatrix &m2)
  { return !(m1 == m2); }

  /**
  * Equality comparison within given tolerance, for each component.
  */
  SbBool    equals(const SbMatrix &m, float tolerance) const;

SoINTERNAL public:
  /**
   * Diagonalizes 3x3 matrix
   */
  void jacobi3(float evalues[3], SbVec3f evectors[3], int &rots) const;

private:
  // Storage for 4x4 matrix
  SbMat matrix;

  SbBool affine_inverse(const SbMatrix &in, SbMatrix &out) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbMatrixd
//
//  4x4 matrix of double precision floating-point elements.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT 4x4 matrix class (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   4x4 double precision matrix class/datatype. Although Open Inventor fields still
*   store only single precision values, for certain applications it is useful and
*   convenient to be able to store and manipulate double precision values, for
*   example, double precision coordinate data or values that will be used for
*   further computation.
*
*   Matrices are stored in column-major order. So m[i][j] is the value in column 
*   i and row j (just like OpenGL matrices, but unlike classic C/C++ 2d arrays). 
*   For example, in a 4x4 transform matrix the translation X, Y, Z values are in 
*   m[3][0], m[3][1] and m[3][2].
*
*   Open Inventor considers coordinates to be row vectors.  Therefore use the
*   multVecMatrix() method to transform a position from object coordinates to 
*   world coordinates. However use the multDirMatrix() matrix to transform a 
*   normal vector (using the inverse transpose of the matrix).
*
*   Correspondingly transforms are applied "left to right".  So use the multLeft()
*   method to concatenate a transform onto the cumulative modeling matrix.
*
* @SEE_ALSO
*    SbMatrix,
*    SbMatrix3,
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,16}]
*/

class INVENTORBASE_API SbMatrixd {
public:

  /**
  * Default constructor.  The matrix is not initialized.
  */
  SbMatrixd()    { }

  /**
  * Constructor.
  */
  SbMatrixd(double a11, double a12, double a13, double a14,
    double a21, double a22, double a23, double a24,
    double a31, double a32, double a33, double a34,
    double a41, double a42, double a43, double a44);

  /**
  * Constructor.
  */
  SbMatrixd(const SbMatd &m);

  /**
  * Sets value from 4x4 array of elements.
  */
  void  setValue(const SbMatd &m);
  /** [OIVJAVA-WRAPPER-NO-WRAP] */
  void    setValue(const double *pMat)
  {
    matrix[0][0] = *pMat++ ;
    matrix[0][1] = *pMat++ ;
    matrix[0][2] = *pMat++ ;
    matrix[0][3] = *pMat++ ;

    matrix[1][0] = *pMat++ ;
    matrix[1][1] = *pMat++ ;
    matrix[1][2] = *pMat++ ;
    matrix[1][3] = *pMat++ ;

    matrix[2][0] = *pMat++ ;
    matrix[2][1] = *pMat++ ;
    matrix[2][2] = *pMat++ ;
    matrix[2][3] = *pMat++ ;

    matrix[3][0] = *pMat++ ;
    matrix[3][1] = *pMat++ ;
    matrix[3][2] = *pMat++ ;
    matrix[3][3] = *pMat++ ;
  } ;

  /**
  * Sets values from a single precision matrix.
  */
  void  setValue(const SbMatrix &m) ;

public:

  /**
  * Sets matrix to be identity.
  */
  void  makeIdentity();

  /**
  * Returns an identity matrix.
  */
  static SbMatrixd  identity();

  /**
  * Sets matrix to rotate by given rotation.
  */
  void  setRotate(const SbRotationd &q);

  /**
  * Sets matrix to scale by given uniform factor.
  */
  void  setScale(double s);

  /**
  * Sets matrix to scale by given vector.
  */
  void  setScale(const SbVec3d &s);

  /**
  * Sets matrix to translate by given vector.
  */
  void  setTranslate(const SbVec3d &t);

  /**
  * Composes the matrix based on a translation, rotation, scale, orientation for
  * scale, and center. The @B scaleOrientation @b chooses the primary axes for the scale.
  * The @B center @b is the center point for scaling and rotation.
  */
  void  setTransform(const SbVec3d &translation,
    const SbRotationd &rotation,
    const SbVec3d &scaleFactor,
    const SbRotationd &scaleOrientation,
    const SbVec3d &center);
  /**
  * Composes the matrix based on a translation, rotation, and scale.  A scale orientation
  * value of (0,0,0,1) is used. The center point for scaling and rotation is (0,0,0).
  */
  void setTransform(const SbVec3d &t, const SbRotationd &r, const SbVec3d &s);

  /**
  * Composes the matrix based on a translation, rotation, scale, and orientation for
  * scale. The @B scaleOrientation @b chooses the primary axes for the scale. The
  * center point for scaling and rotation is (0,0,0).
  */
  void setTransform(const SbVec3d &t, const SbRotationd &r,
    const SbVec3d &s, const SbRotationd &so);

  /**
  * Decomposes the matrix into a translation, rotation, scale, and scale
  * orientation. Any projection information is discarded. The decomposition depends
  * upon choice of center point for rotation and scaling, which is optional as the
  * last parameter. Note that if the center is 0, decompose() is the same as
  * factor() where t is @B translation, @b u is @B rotation, @b s is
  * @B scaleFactor, @b and r is @B scaleOrientation. @b
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{Decomposition}]
  */
  void  getTransform(SbVec3d &translation,
    SbRotationd &rotation,
    SbVec3d &scaleFactor,
    SbRotationd &scaleOrientation,
    const SbVec3d &center) const;
  /**
  * Return translation, rotation, scale, and scale orientation components of the
  * matrix.
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{Decomposition}]
  */
  void getTransform(SbVec3d &t, SbRotationd &r,
    SbVec3d &s, SbRotationd &so) const;


  // The following methods return matrix values and other info:

  /**
  * Returns 4x4 array of elements.
  */
  void  getValue(SbMatd &m) const;

#ifdef _WIN32
  /**
  * Returns 4x4 array of elements.
  */
  SbMatd &getValue() { SbMatd &rMat = matrix; return rMat; }
#endif
  /**
  * Returns 4x4 array of elements.
  */
  const SbMatd &getValue() const { return matrix; }

  /**
  * Returns determinant of 3x3 submatrix composed of given row and column indices
  * (0-3 for each).
  */
  double  det3(int r1, int r2, int r3, int c1, int c2, int c3) const;

  /**
  * Returns determinant of upper-left 3x3 submatrix.
  */
  double  det3() const { return det3(0, 1, 2, 0, 1, 2); }

  /**
  * Returns determinant of entire matrix.
  */
  double  det4() const;

  /**
  * Factors a matrix m into 5 pieces: m = r s r^ u t, where r^ means transpose of r,
  * and r and u are rotations, s is a scale, and t is a translation. Any projection
  * information is returned in @B proj@b.
  * [OIVJAVA-WRAPPER PACK{Factorization}]
  */
  SbBool  factor(SbMatrixd &r, SbVec3d &s, SbMatrixd &u,
    SbVec3d &t, SbMatrixd &proj) const;

  /**
  * Returns inverse of matrix. Results are undefined for singular matrices. Uses LU
  * decomposition.
  */
  SbMatrixd  inverse() const;

  /**
  * Perform in-place LU decomposition of matrix. @B index @b is index of rows in
  * matrix. @B d @b is the parity of row swaps. Returns FALSE if singular.
  */
  SbBool  LUDecomposition(int index[4], double &d);

  /**
  * Perform back-substitution on LU-decomposed matrix. Index is permutation of rows
  * from original matrix.
  */
  void  LUBackSubstitution(int index[4], double b[4]) const;

  /**
  * Returns transpose of matrix.
  */
  SbMatrixd  transpose() const;


  // The following methods provide Mx/mx and mx/vec arithmetic:

  /**
  * Multiplies matrix by given matrix on right.
  */
  SbMatrixd &multRight(const SbMatrixd &m);
  /**
  * Multiplies matrix by given matrix on left.
  */
  SbMatrixd &multLeft(const SbMatrixd &m);

  /**
  * Multiplies matrix by given column vector, giving vector result.
  */
  void  multMatrixVec(const SbVec3d &src, SbVec3d &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result. @BR
  * Use this method to transform points from object coordinates to world coordinates.
  */
  void  multVecMatrix(const SbVec3d &src, SbVec3d &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result. @B src @b
  * is assumed to
  * be a direction vector, so the translation part of matrix is ignored. Note: if you
  * wish to transform surface points and normals by a matrix, call
  * multVecMatrix() for the points and call multDirMatrix() on the
  * inverse transpose of the matrix for the normals.
  */
  void  multDirMatrix(const SbVec3d &src, SbVec3d &dst) const;

  /**
  * Multiplies the given line's origin by the matrix, and the line's direction by
  * the rotation portion of the matrix.
  */
  void  multLineMatrix(const SbLine &src, SbLine &dst) const;


  // The following methods are miscellaneous Mx functions:

  /**
  * Prints a formatted version of the matrix to the given file pointer.
  */
  void  print(FILE *fp) const;


  /**
  * Cast: returns pointer to storage of first element.
  */
  operator double *() { return &matrix[0][0]; }

  /**
  * Cast: returns reference to 4x4 array.
  */
  operator SbMatd &() { return matrix; }

  /**
  * Make it look like a usual matrix (so you can do m[3][2]).
  */
  double * operator [](int i)   { return &matrix[i][0]; }
  /**
  * Make it look like a usual matrix (so you can do m[3][2]).
  */
  const double * operator [](int i) const  { return &matrix[i][0]; }

  /**
  * Sets value from 4x4 array of elements.
  */
  SbMatrixd & operator =(const SbMatd &m);

  /**
  * Set the matrix from another SbMatrixd.
  */
  SbMatrixd & operator =(const SbMatrixd &m);

  /**
  * Set the matrix from an SbRotationd.
  */
  SbMatrixd & operator =(const SbRotationd &q)  { setRotate(q); return *this; }

  /**
  * Performs right multiplication with another matrix.
  */
  SbMatrixd & operator *=(const SbMatrixd &m)  { return multRight(m); }

  /**
  * Binary multiplication of matrices.
  */
  INVENTORBASE_API friend SbMatrixd operator *(const SbMatrixd &m1, const SbMatrixd &m2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbMatrixd &m1, const SbMatrixd &m2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbMatrixd &m1, const SbMatrixd &m2)
  { return !(m1 == m2); }

  /**
  * Equality comparison within given tolerance, for each component.
  */
  SbBool    equals(const SbMatrixd &m, double tolerance) const;

SoINTERNAL public:
  /**
   * Diagonalizes 3x3 matrix 
   */
  void  jacobi3(double evalues[3], SbVec3d evectors[3], int &rots) const;

private:
  // Storage for 4x4 matrix
  SbMatd  matrix;

  SbBool affine_inverse(const SbMatrixd &in, SbMatrixd &out) const;

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbMatrix3
//
//  3x3 matrix of floating-point elements.
//
//////////////////////////////////////////////////////////////////////////////



/**
* 3x3 matrix class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   3x3 matrix class/datatype.
* 
*   Matrices are stored in column-major order. So m[i][j] is the value in column 
*   i and row j (just like OpenGL matrices, but unlike classic C/C++ 2d arrays). 
*
*   Open Inventor considers coordinates to be row vectors.  Therefore use the
*   multVecMatrix() method to transform a position from object coordinates to 
*   world coordinates.
*
*   Correspondingly transforms are applied "left to right".  So use the multLeft()
*   method to concatenate a transform onto the cumulative modeling matrix.
*
* @SEE_ALSO
*    SbMatrix,
*    SbMatrixd,
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,9}]
*/

class INVENTORBASE_API SbMatrix3 {
public:

  /**
  * Constructor.
  */
  SbMatrix3() { }

  /**
  * Constructor.
  */
  SbMatrix3(float a11, float a12, float a13,
    float a21, float a22, float a23,
    float a31, float a32, float a33);

  /**
  * Constructor.
  */
  SbMatrix3(const SbMat3 &m);

  /**
  * Sets value from 3x3 array of elements.
  */
  void  setValue(const SbMat3 &m);
  /** [OIVJAVA-WRAPPER-NO-WRAP] */
  void    setValue(const float *pMat)
  {
    matrix[0][0] = *pMat++ ;
    matrix[0][1] = *pMat++ ;
    matrix[0][2] = *pMat++ ;

    matrix[1][0] = *pMat++ ;
    matrix[1][1] = *pMat++ ;
    matrix[1][2] = *pMat++ ;

    matrix[2][0] = *pMat++ ;
    matrix[2][1] = *pMat++ ;
    matrix[2][2] = *pMat++ ;
  } ;

  /**
  * Sets matrix to be identity.
  */
  void  makeIdentity();

  /**
  * Returns an identity matrix.
  */
  static SbMatrix3  identity();

  /**
  * Sets matrix to rotate by given rotation.
  */
  void  setRotate(const SbRotation &q);

  /**
  * Sets matrix to scale by given uniform factor.
  */
  void  setScale(float s);

  /**
  * Sets matrix to scale by given vector.
  */
  void  setScale(const SbVec3f &s);

  /**
  * Returns 3x3 array of elements.
  */
  void  getValue(SbMat3 &m) const;

  /**
  * Returns 3x3 array of elements.
  */
  const SbMat3 &getValue() const { return matrix; }

  /**
  * Multiplies matrix by given matrix on right.
  */
  SbMatrix3 &multRight(const SbMatrix3 &m);

  /**
  * Multiplies matrix by given matrix on left.
  */
  SbMatrix3 &multLeft(const SbMatrix3 &m);

  /**
  * Multiplies matrix by given column vector, giving vector result.
  */
  void  multMatrixVec(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Multiplies given row vector by matrix, giving vector result. @BR
  * Use this method to transform points from object coordinates to world coordinates.
  */
  void  multVecMatrix(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Prints a formatted version of the matrix to the given file pointer.
  */
  void  print(FILE *fp) const;

  /**
  * Cast: returns pointer to storage of first element.
  */
  operator float *() { return &matrix[0][0]; }

  /**
  * Cast: returns reference to 3x3 array.
  */
  operator SbMat3 &() { return matrix; }

  /**
  * Make it look like a usual matrix (so you can do m[2][2]).
  */
  float * operator [](int i)   { return &matrix[i][0]; }

  /**
  * Make it look like a usual matrix (so you can do m[2][2]).
  */
  const float * operator [](int i) const  { return &matrix[i][0]; }

  /**
  * Sets value from 3x3 array of elements.
  */
  SbMatrix3 & operator =(const SbMat3 &m);

  /**
  * Set the matrix from another SbMatrix3.
  */
  SbMatrix3 & operator =(const SbMatrix3 &m);

  /**
  * Set the matrix from an SbRotation.
  */
  SbMatrix3 & operator =(const SbRotation &q)  { setRotate(q); return *this; }

  /**
  * Performs right multiplication with another matrix.
  */
  SbMatrix3 & operator *=(const SbMatrix3 &m)  { return multRight(m); }

  /**
  * Binary multiplication of matrices.
  */
  INVENTORBASE_API friend SbMatrix3 operator *(const SbMatrix3 &m1, const SbMatrix3 &m2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbMatrix3 &m1, const SbMatrix3 &m2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbMatrix3 &m1, const SbMatrix3 &m2)
  { return !(m1 == m2); }

private:
  SbMat3 matrix;    // Storage for 3x3 matrix
};

inline std::ostream& operator << (std::ostream& os, const SbMatrix& mat)
{
  for ( int j = 0; j < 4; j++ )
  {
    os << "[ ";
    for ( int i = 0; i < 4; i++ )
      os << mat[j][i] << " ";
    os << "]" << std::endl;
  }
  return os;
}

#endif /* _SB_MATRIX_ */
