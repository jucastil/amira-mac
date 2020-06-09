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


#ifndef  _SO_SF_VEC4F_
#define  _SO_SF_VEC4F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec4f subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a homogeneous three-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   Field containing a homogeneous three-dimensional vector.
 *   
 *   SoSFVec4fs are written to file as four floating point values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec4f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec4f : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec4f, SbVec4f, const SbVec4f &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void        setValue(float x, float y, float z, float w);

  /**
   * Sets the field to the given value.
   */
  void        setValue(const float xyzw[4]);

  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. Note that Open Inventor fields still store only single
   * precision values, not double precision values. The specified value is converted
   * to single precision, then stored.
   */
  void            setValue(const SbVec4d &vec4d);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC4F_ */

