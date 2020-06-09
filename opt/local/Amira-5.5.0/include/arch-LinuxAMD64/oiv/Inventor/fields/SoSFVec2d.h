/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_VEC2D_
#define  _SO_SF_VEC2D_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec2d subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a two-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoSFVec2ds are written to file as a pair of doubleing point values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec2f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec2d : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec2d, SbVec2d, const SbVec2d &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void                setValue(double x, double y);

  /**
   * Sets the field to the given value.
   */
  void                setValue(const double xy[2]);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC2D_ */

