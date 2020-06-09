/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WINRESOURCE_
#define _SO_WINRESOURCE_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/sys/port.h>
#include <Inventor/sys/SoDynamicLibManager.h>
#include <Inventor/Win/SoWinRes.h>
#include <Inventor/Win/SoWinDef.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>

class SbDict;
SoINTERNAL class INVENTORW_API SoWinResource
{
 public:
  static SoDynamicLibManager::SafeLibraryHandle& loadResourceDll(LPCTSTR lpszDllName);
  static LPCTSTR  getString(int nId);
  static void     freeStrings();
  static HGLOBAL  getStringCopy(int nId);
  static Hmenu    getMenu(int nId);
  static SoDynamicLibManager::SafeLibraryHandle m_hResDllSafeHandle;
 private:
  static LPCTSTR  loadStringResource(int nId);
  static SbDict * m_pStringDict;
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WINRESOURCE_ */
