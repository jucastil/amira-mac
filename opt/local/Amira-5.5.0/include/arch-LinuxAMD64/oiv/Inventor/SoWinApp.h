/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if ! defined(_WIN32_APP_) && !defined(QT_DLL)
#  define _WIN32_APP_
#  ifdef _WIN32
#    define main ivMain
#    include <SoVersion.h>
#    if defined(_DEBUG)
#      define __INVULIB "InventorUD.lib"
#    else
#      define __INVULIB "InventorU.lib"
#    endif
#    ifndef Inventor_EXPORTS
#ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVULIB)
#endif
#    endif
#  endif /* _WIN32 */
#endif /* _WIN32_APP_ */
