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


#ifndef  _SO_MF_ROTATION_
#define  _SO_MF_ROTATION_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFRotation subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of SbRotations.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of SbRotations.
 *   
 *   SoMFRotations are written to file as one or more sets of four floating point
 *   values. Each set of 4 values is an axis of rotation followed by the amount of
 *   right-handed rotation about that axis, in radians.
 *   
 *   When more than one value is present, all of the values are enclosed in square
 *   brackets and separated by commas; for example:
 *   
 *   <PRE>
 *    [ 1 0 0 0, -.707 -.707 0 1.57 ]
 *    </PRE>
 *    
 * 
 * @SEE_ALSO
 *    SbRotation
 * 
 * 
 */ 

class INVENTOR_API SoMFRotation : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFRotation, SbRotation, const SbRotation &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbRotation);

    public:

  //
  // Some additional convenience functions:
  //
  /**
   * Sets values from an array of arrays of 4 floats.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, num)}]
   */
  void setValues(int start, int num, const float q[][4]);

  /**
   * Sets the @B index @b'th value to the given quaternion (x, y, z, w).
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, float q0, float q1, float q2, float q3);

  /**
   * Sets the @B index @b'th value to the given quaternion (x, y, z, w).
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const float q[4]);

  /**
   * Sets the @B index @b'th value to the given axis/angle.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbVec3f &axis, float angle);

  /**
   * Makes this field have exactly one value, given by the quaternion (x, y, z, w).
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(float q0, float q1, float q2, float q3);

  /**
   * Makes this field have exactly one value, given by the quaternion (x, y, z, w).
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const float q[4]);

  /**
   * Makes this field have exactly one value, given by @B axis @b and @B angle @b.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbVec3f &axis, float angle);

  /**
   * Sets the @B index @b'th value in the array to @B newValue @b, a double
   * precision rotation. The array will be automatically expanded, if necessary. Note
   * that Open Inventor fields still store only single precision values, not double
   * precision values. The specified value is converted to single precision, then
   * stored.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSet1Value(index)}]
   */
  void set1Value(int index, const SbRotationd &rd);

  /**
   * Sets the first value in the array to @B newValue @b, a double precision
   * rotation, and deletes the second and subsequent values. Note that Open Inventor
   * fields still store only single precision values, not double precision values.
   * The specified value is converted to single precision, then stored.
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValue()}]
   */
  void setValue(const SbRotationd &rd);

  /**
   * Sets @B num @b values starting at index @B start @b to the values in
   * @B newValues @b, an array of double precision rotations. The array will
   * automatically be made larger to accommodate the new values, if necessary. Note
   * that Open Inventor fields still store only single precision values, not double
   * precision values. The specified values are converted to single precision, then
   * stored.
   * [OIVNET-WRAPPER-ARG IN,NO_WRAP{rd->Length},ARRAY]
   * [OIVNET-WRAPPER-HELPER BEGIN{OnSetValues(start, rd->Length)}]
   */
  void setValues(int start, int num, const SbRotationd *rd);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_MF_ROTATION_ */

