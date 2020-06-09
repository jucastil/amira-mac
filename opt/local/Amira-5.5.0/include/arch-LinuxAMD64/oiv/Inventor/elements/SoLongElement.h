/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LONG_ELEMENT
#define  _SO_LONG_ELEMENT

#ifndef IV_STRICT
#include <Inventor/elements/SoInt32Element.h>
typedef SoInt32Element SoLongElement;

#else
 
Error: SoLongElement invalid with -DIV_STRICT, see <Inventor/elements/SoLongElement.h>
------
Inventor now provides SoInt32Element types in place of SoLongElement types to 
simplify porting to other architectures and operating systems.  

You should use SoInt32Element in place of SoLongElement and also change longs 
in your code to the appropriate sized typedef from <inttypes.h>.   The perl 
script  /usr/sbin/longToInt32  can assist you making this transition.  Note 
that not all longs should be changed as some are determined by other system 
include files.
_____________________________________________________________________________

#endif /* IV_STRICT */

#endif /* _SO_LONG_ELEMENT */
