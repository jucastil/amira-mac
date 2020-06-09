/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __SOLOCKMGR_H__
#define __SOLOCKMGR_H__

#include <Inventor/SbBase.h>

class SoLockMgrPrivate;
/**
 * @VSGEXT Sets the unlock string.
 * 
 * @ingroup lock
 * 
 * @DESCRIPTION
 * This class is used for setting the unlock string (also called "license string" or
 * "password") programmatically. Master passwords and encrypted passwords must
 * be specified via this mechanism.
 *
 * If your application uses any of the Open Inventor
 * extensions (e.g., MeshViz, VolumeViz, etc.), you will need to
 * specify the necessary license strings using a colon-separated list or a
 * newline-separated list. For encrypted passwords, you must use a
 * newline-separated list. (Since SoLockManager stores only a single 
 * string, it would not work to make multiple calls, each
 * specifying a single license string; each call would
 * overwrite the previously specified value.)
 * 
 * You must set the unlock string before your call to SoXt::init, 
 * SoWin::init (Windows platforms only), SoDB::init, or IVF_INIT_INSTANCE 
 * (Windows MFC- and IVF-based applications). This means the password string
 * should typically be specified in your application's main, WinMain
 * or CMyApp::InitInstance (for an MFC- and IVF-based application).
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 
class INVENTORBASE_API SoLockManager
{
 public:
#ifdef OIV_NET_DOC
	 /**
	 * Sets the unlock string. @BR
	 * SoLockManager makes a copy of the specified string, so it is
	 * not necessary to declare a static string.@BR
	 */

#else
	 /**
	 * Sets the unlock string. @BR
	 * SoLockManager makes a copy of the specified string, so it is
	 * not necessary to declare a static string.@BR
	 * To reclaim the memory allocated by SoLockManager (for example
	 * at program exit), simply call setUnlockString with NULL.
	 */

#endif //OIV_NET_DOC
	 static void SetUnlockString(char *pUnlockString);
  /**
   * Returns the unlock string.
   */
  static char *GetUnlockString();

	SoINTERNAL public:
	static void exitClass();

 private:
  static SoLockMgrPrivate *pData;
};

#endif
