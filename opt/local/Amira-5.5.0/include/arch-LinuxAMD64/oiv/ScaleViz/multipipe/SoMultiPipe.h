/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2005)
**=======================================================================*/


#ifndef SO_MULTIPIPE_H
#define SO_MULTIPIPE_H

#include <ScaleViz/SoScaleViz.h>

class SCALEVIZ_API SoMultiPipe
{
 public:
  /**
   * Returns a character string identifying the name of the extension.
   */
  static SbString getProductName();

  /**
   * Returns a character string identifying the version of extension.
   */
  static const char* getVersion();

 SoINTERNAL public:

  static void internalInit();
};

#endif // SO_MULTIPIPE_H

/**/
