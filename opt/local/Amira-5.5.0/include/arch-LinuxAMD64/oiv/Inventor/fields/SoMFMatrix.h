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


#ifndef  _SO_MF_MATRIX_
#define  _SO_MF_MATRIX_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFMatrix subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of 4x4 matrices.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of 4x4 matrices.
 *   
 *   SoMFMatrix are written to file as sets of 16 floating point numbers
 *   separated by whitespace. When more than one value is present, all of the values
 *   are enclosed in square brackets and separated by commas; for example, two
 *   identity matrices might be written as:
 *   
 *   <PRE>
 *    [ 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1,
 *    1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 ]
 *   </PRE>
 *    
 * 
 * 
 */ 

class INVENTOR_API SoMFMatrix : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFMatrix, SbMatrix, const SbMatrix &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbMatrix);

    public:
  /**
   * Makes this field contain one and only one value, which is the matrix given by
   * the 16 values.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(float a11, float a12, float a13, float a14,
                float a21, float a22, float a23, float a24,
                float a31, float a32, float a33, float a34,
                float a41, float a42, float a43, float a44);

  /**
   * Sets the @B index @b'th value in the array to @B newValue @b, a double
   * precision matrix. The array will be automatically expanded, if necessary. Note
   * that Open Inventor fields still store only single precision values, not double
   * precision values. The specified value is converted to single precision, then
   * stored.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbMatrixd &md);

  /**
   * Sets the first value in the array to @B newValue @b, a double precision matrix,
   * and deletes the second and subsequent values. Note that Open Inventor fields
   * still store only single precision values, not double precision values. The
   * specified value is converted to single precision, then stored.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbMatrixd &md);

  /**
   * Sets @B num @b values starting at index @B start @b to the values in
   * @B newValues @b, an array of double precision values. The array will
   * automatically be made larger to accommodate the new values, if necessary. Note
   * that Open Inventor fields still store only single precision values, not double
   * precision values. The specified values are converted to single precision, then
   * stored.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{md->Length},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, md->Length)}]
   */
  void setValues(int start, int num, const SbMatrixd *md);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_MF_MATRIX_ */

