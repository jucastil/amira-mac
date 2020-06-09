/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MF_PLANE_
#define  _SO_MF_PLANE_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbPlane.h>
//////////////////////////////////////////////////////////////////////////////
//
//  SoMFPlane subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing several plane equations.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing one or more plane equations.
 *   
 *   SoMFPlanes are written to file as groups of four floating point values separated
 *   by whitespace. In each set of four values, the first three are the normal
 *   direction of the plane, the fourth is the distance of the plane from the origin
 *   (in the direction of the normal).
 *   
 *   When more than one value is present, all of the values are enclosed in square
 *   brackets and separated by commas; for example:
 *   
 *   <PRE>
 *    [ 1 0 0 0, .707 .707 0 100, ]
 *    </PRE>
 *    
 * 
 * 
 */ 

class INVENTOR_API SoMFPlane : public SoMField {
  
  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFPlane, SbPlane, SbPlane);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbPlane);
    
 SoINTERNAL public:
    static void initClass();
    static void exitClass();

 private:
  // Returns number of ASCII values to write per output line
  virtual int getNumValuesPerLine() const;
  
};

#endif /* _SO_MF_PLANE_ */

