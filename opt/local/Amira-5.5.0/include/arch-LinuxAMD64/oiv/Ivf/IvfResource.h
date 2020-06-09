/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __IVFRESOURCE_H__
#define __IVFRESOURCE_H__

#include <Inventor/SbBasic.h>

#include <Ivf/IvfRes.h>
#include <tchar.h>

class SbDict;

/**
 * Used for internationalization to access strings in resource file.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   
 * 
 */ 
class IVF_API IvfResource
{
 public:

  static void     initialize();

  static LPCTSTR  getString(int nId);

  static void     freeStrings();

  static HGLOBAL  getStringCopy(int nId);

  static HMENU    getMenu(int nId);

  static HMODULE  m_hResDll;

 private:
    
  static LPCTSTR  loadStringResource(int nId);

  static SbDict * m_pStringDict;

};


#endif 
