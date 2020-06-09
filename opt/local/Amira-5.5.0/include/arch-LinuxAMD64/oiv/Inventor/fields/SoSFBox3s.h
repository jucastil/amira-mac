/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/

#ifndef  _SO_SF_BOX3S_
#define  _SO_SF_BOX3S_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

#include <Inventor/SbBox.h> // To Suppress in the VERSION

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBox3s subclass of SoSField.
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
 *   SoSFBox3s fields are written to file as 6 integers separated by whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField
 * 
 * 
 */ 

class INVENTOR_API SoSFBox3s : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFBox3s, SbBox3s, const SbBox3s &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the box dimensions.
   */
  void                setValue(short xmin, short ymin, short zmin,
                               short xmax, short ymax, short zmax);

  /**
   * Sets the box dimensions.
   */
  void                setValue(const SbVec3s &_min, const SbVec3s &_max);


 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_BOX3S_ */

