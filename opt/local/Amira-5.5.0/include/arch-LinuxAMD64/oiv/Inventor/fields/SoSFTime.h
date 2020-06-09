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


#ifndef  _SO_SF_TIME_
#define  _SO_SF_TIME_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbTime.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFTime subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an SbTime.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-valued field that contains a time value.
 *   
 *   SoSFTimes are written to file as a double-precision floating point value
 *   representing the length of time in seconds. Absolute times are measured relative
 *   to 00:00:00 GMT, January 1, 1970.
 * 
 * @SEE_ALSO
 *    SbTime,
 *    SoField,
 *    SoSField,
 *    SoMFTime
 * 
 * 
 */ 

class INVENTOR_API SoSFTime : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFTime, SbTime, const SbTime &);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_TIME_ */

