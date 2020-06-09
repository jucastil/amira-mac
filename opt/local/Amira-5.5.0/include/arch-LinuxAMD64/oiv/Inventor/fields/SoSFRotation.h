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


#ifndef  _SO_SF_ROTATION_
#define  _SO_SF_ROTATION_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFRotation subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a rotation.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a single SbRotation (an arbitrary rotation).
 *   
 *   SoSFRotations are written to file as four floating point values separated by
 *   whitespace. The 4 values represent an axis of rotation followed by the amount of
 *   right-handed rotation about that axis, in radians. For example, a 180 degree
 *   rotation about the Y axis is:
 *   
 *   <PRE>
 *    0 1 0 3.14159265
 *    </PRE>
 * NOTE: When you specify an SoSFRotation value using setValue with
 * 4 floating point values,
 * those values will be interpreted as a quaternion (x, y, z, w) rather than
 * an axis and a rotation. To specify an SoSFRotation value using an
 * axis and a rotation, you must use 
 * the following method: setValue(const SbVec3f &axis, float angle).  
 * 
 * @SEE_ALSO
 *    SbRotation,
 *    SoField,
 *    SoSField,
 *    SoMFRotation
 * 
 * 
 */ 

class INVENTOR_API SoSFRotation : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFRotation, SbRotation, const SbRotation &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Gets the value of the field as an axis/angle.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void        getValue(SbVec3f &axis, float &angle) const
    { evaluate(); value.getValue(axis, angle); }

  /**
   * Sets the field to the given quaternion (x, y, z, w).
   */
  void        setValue(float q0, float q1, float q2, float q3);
    
  /**
   * Sets the field to the given quaternion (x, y, z, w).
   */
  void        setValue(const float q[4]);

  /**
   * Sets the field to the rotation given by axis/angle.
   */
  void        setValue(const SbVec3f &axis, float angle);

  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. Note that Open Inventor fields still store only single
   * precision values, not double precision values. The specified value is converted
   * to single precision, then stored.
   */
  void    setValue(const SbRotationd &rotd);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_ROTATION_ */

