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


#ifndef  _SO_SF_PLANE_
#define  _SO_SF_PLANE_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFPlane subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a plane equation.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a plane equation (an SbPlane).
 *   
 *   SoSFPlanes are written to file as four floating point values separated by
 *   whitespace. The first three are the normal direction of the plane, the fourth is
 *   the distance of the plane from the origin (in the direction of the normal).
 * 
 * @SEE_ALSO
 *    SbPlane,
 *    SoField,
 *    SoSField,
 *    SoMFPlane
 * 
 * 
 */ 

class INVENTOR_API SoSFPlane : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFPlane, SbPlane, const SbPlane &);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_PLANE_ */

