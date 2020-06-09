/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_MATRIX_
#define  _SO_SF_MATRIX_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFMatrix subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a 4x4 matrix.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a transformation matrix (an SbMatrix).
 *   
 *   SoSFMatrixs are written to file as 16 floating point numbers separated by
 *   whitespace. For example, an identity matrix is written as:
 *   
 *   <PRE>
 *    1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
 *    </PRE>
 *    
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFMatrix,
 *    SbMatrix
 * 
 * 
 */ 

class INVENTOR_API SoSFMatrix : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFMatrix, SbMatrix, const SbMatrix &);

 public:
  /**
   * Sets this field to contain the matrix given by the 16 values. For a translation
   * matrix, the x, y and z translations should be in the @B a41@b, @B a42@b, and
   * @B a43@b arguments.
   */
  void                setValue(float a11, float a12, float a13, float a14,
                               float a21, float a22, float a23, float a24,
                               float a31, float a32, float a33, float a34,
                               float a41, float a42, float a43, float a44);

  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. Note that Open Inventor fields still store only single
   * precision values, not double precision values. The specified value is converted
   * to single precision, then stored.
   */
  void            setValue(const SbMatrixd &md);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_MATRIX_ */

