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
 * Synonym for SoSFUInt32.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This class is obsolete, and is provided for backwards compatibility only. You
 *   should use the new SoSFUInt32 class instead. If you compile your code
 *   -DIV_STRICT, including the SoSFULong.h header file will cause a compile-time
 *   error.
 * 
 * 
 */ 



#ifndef  _SO_SF_ULONG_
#define  _SO_SF_ULONG_

#ifndef IV_STRICT
#include <Inventor/fields/SoSFUInt32.h>
typedef SoSFUInt32 SoSFULong;

#else
 
Error. SoSFULong invalid with -DIV_STRICT.  See <Inventor/fields/SoSFULong.h>
------
Inventor now provides So*Int32 types in place of So*Long types to simplify
porting to other architectures and operating systems.  

You should use SoSFUInt32 in place of SoSFULong and also change longs in your
code to the appropriate sized typedef from <inttypes.h>.   The perl script  
/usr/sbin/longToInt32  can assist you making this transition.  Note that not 
all longs should be changed as some are determined by other system include 
files.
_____________________________________________________________________________

#endif /* IV_STRICT */

#endif /* _SO_SF_ULONG_ */

