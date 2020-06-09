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


#ifndef  _SO_MF_TIME_
#define  _SO_MF_TIME_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbTime.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFTime subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of SbTime values.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of SbTime values.
 *   
 *   SoMFTimes are written to file as one or more double-precision floating point
 *   values representing the length of time in seconds. Absolute times are measured
 *   relative to 00:00:00 GMT, January 1, 1970.
 *   
 *   When more than one value is present, all of the values are enclosed in square
 *   brackets and separated by commas; for example:
 *   
 *   <PRE>
 *    [ 1.0, 1345600.1200055, 99.8 ]
 *    </PRE>
 *    
 * 
 * @SEE_ALSO
 *    SbTime
 * 
 * 
 */ 

class INVENTOR_API SoMFTime : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFTime, SbTime, const SbTime &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbTime);

 SoINTERNAL public:
    static void initClass();
  static void exitClass();

};

#endif /* _SO_MF_TIME_ */

