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
/**
 * Synonym for SoSFInt32.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This class is obsolete, and is provided for backwards compatibility only. You
 *   should use the new SoSFInt32 class instead. If you compile your code
 *   -DIV_STRICT, including the SoSFLong.h header file will cause a compile-time
 *   error.
 * 
 * 
 */ 



#ifndef  _SO_SF_LONG_
#define  _SO_SF_LONG_

#ifndef IV_STRICT
#include <Inventor/fields/SoSFInt32.h>
typedef SoSFInt32 SoSFLong;

#else
 
Error.  SoSFLong invalid with -DIV_STRICT.   See <Inventor/fields/SoSFLong.h>
------
Inventor now provides So*Int32 types in place of So*Long types to simplify
porting to other architectures and operating systems.  

You should use SoSFInt32 in place of SoSFLong and also change longs in your
code to the appropriate sized typedef from <inttypes.h>.   The perl script  
/usr/sbin/longToInt32  can assist you making this transition.  Note that not 
all longs should be changed as some are determined by other system include 
files.
_____________________________________________________________________________

#endif /* IV_STRICT */

#endif /* _SO_SF_LONG_ */

