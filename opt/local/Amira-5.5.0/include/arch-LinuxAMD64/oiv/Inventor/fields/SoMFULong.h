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
 * Synonym for SoMFUInt32.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This class is obsolete, and is provided for backwards compatibility only. You
 *   should use the new SoMFUInt32 class instead. If you compile your code
 *   -DIV_STRICT, including the SoMFULong.h header file will cause a compile-time
 *   error.
 * 
 * 
 */ 



#ifndef  _SO_MF_ULONG_
#define  _SO_MF_ULONG_

#ifndef IV_STRICT
#include <Inventor/fields/SoMFUInt32.h>

typedef SoMFUInt32 SoMFULong;

#else
 
Error. SoMFULong invalid with -DIV_STRICT.  See <Inventor/fields/SoMFULong.h>
------
Inventor now provides So*Int32 types in place of So*Long types to simplify
porting to other architectures and operating systems.  

You should use SoMFUInt32 in place of SoMFULong and also change longs in your
code to the appropriate sized typedef from <inttypes.h>.   The perl script  
/usr/sbin/longToInt32  can assist you making this transition.  Note that not 
all longs should be changed as some are determined by other system include 
files.
_____________________________________________________________________________

#endif /* IV_STRICT */

#endif /* _SO_MF_ULONG_ */

