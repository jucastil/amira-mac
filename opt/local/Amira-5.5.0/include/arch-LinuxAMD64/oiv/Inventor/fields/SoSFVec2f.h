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


#ifndef  _SO_SF_VEC2F_
#define  _SO_SF_VEC2F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec2f subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a two-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoSFVec2fs are written to file as a pair of floating point values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec2f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec2f : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec2f, SbVec2f, const SbVec2f &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void                setValue(float x, float y);

  /**
   * Sets the field to the given value.
   */
  void                setValue(const float xy[2]);

  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. Note that Open Inventor fields still store only single
   * precision values, not double precision values. The specified value is converted
   * to single precision, then stored.
   */
  void            setValue(const SbVec2d &vec2d);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC2F_ */

