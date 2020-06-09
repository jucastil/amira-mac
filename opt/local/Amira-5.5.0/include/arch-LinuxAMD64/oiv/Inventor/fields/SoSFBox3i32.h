/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/

#ifndef  _SO_SF_BOX3I32_
#define  _SO_SF_BOX3I32_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

#include <Inventor/SbBox.h> // To Suppress in the VERSION

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBox3i32 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////


/**
 * @VSGEXT Field containing a three-dimensional box.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This field defines a three-dimensional box.
 *   
 *   SoSFBox3i32 fields are written to file as 6 integers separated by whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField
 * 
 * 
 */ 

class INVENTOR_API SoSFBox3i32 : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFBox3i32, SbBox3i32, const SbBox3i32 &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the box dimensions.
   */
  void                setValue(int xmin, int ymin, int zmin,
                               int xmax, int ymax, int zmax);

  /**
   * Sets the box dimensions.
   */
  void                setValue(const SbVec3i32 &_min, const SbVec3i32 &_max);

  /**
   * Sets the box dimensions.
   */
  void                setValue(const SbVec3s &_min, const SbVec3s &_max);


 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_BOX3I32_ */

