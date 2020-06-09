/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Jan 2008)
**=======================================================================*/
#ifndef SO_GUI_H
#define SO_GUI_H

#include <Inventor/sys/port.h>
#include <Inventor/SbBasic.h>

#include <SoVersion.h>
#ifndef HIDDEN_FROM_DOC

#if defined(_WIN32)
#  if defined(_DEBUG)
#    define __INVGUILIB  "InventorGuiD.lib"
#    define __INVGUIDLL  "InventorGuiD.dll"
#  else
#    define __INVGUILIB  "InventorGui.lib"
#    define __INVGUIDLL  "InventorGui.dll"
#  endif
#  ifndef InventorGui_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVGUILIB)
#    endif
#  endif
#else
#  define __INVGUIDLL  "libInventorGui"
#endif

#endif // HIDDEN_FROM_DOC

#include <Inventor/SoModule.h>
#ifndef HIDDEN_FROM_DOC
SO_MODULE_HEADER(SoInventorGui, __INVGUIDLL)
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGui
{
SoINTERNAL public:
  /**
   * Init SoGui module.
   */
  static void init();
  static void threadInit();

  /**
   * Finish SoGui module.
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   */
  static bool isInitialized();

private:
  static int s_initRefCount;
};

#endif // SO_GUI_H

