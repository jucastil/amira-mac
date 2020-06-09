/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (MMM yyyy)
**=======================================================================*/

#ifndef _SO_INVENTOR_GL_
#define _SO_INVENTOR_GL_

#include <Inventor/SbBasic.h>

/**
* General basic object database.
*
* @ingroup General
*
* @DESCRIPTION
*  Allows a minimal set of GL Open Inventor functionality, specifically
*  NOT including the scene graph, to be initialized.
*
* @SEE_ALSO
*    SoDB
*
*/

SoINTERNAL class INVENTORGL_API SoInventorGL
{
public:
  /**
   * Initializes the GL Open Inventor nodes.
   * This must be called before calling any other database routines.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /**
   * Frees Open Inventor's internal static memory
   * allocations. This avoids false positives from memory
   * leak checking software. 
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if database is initialized (for error checking)
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

private:
  // library usage counter
  static int s_initRefCount;
};


#endif /* _SO_INVENTOR_GL_ */
