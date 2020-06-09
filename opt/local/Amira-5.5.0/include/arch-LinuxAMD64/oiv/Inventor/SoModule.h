/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Apr 2009)
**=======================================================================*/


#ifndef SO_MODULE
#define SO_MODULE

#include <Inventor/sys/port.h>
#include <SoVersion.h>

/**
 * Class used to check and report library and application consistency.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * Contains static methods to query information about how the library was built.
 */
class INVENTORBASE_API SoModuleCheck
{
public:
  /** Constructor */
  SoModuleCheck( const bool is_secure_scl);

  /** Returns a string describing the compiler used to build the library. @BR
    * For example "Microsoft Visual Studio 2008". 
    */
  static const char* getCompilerString();

  /** Returns a string describing the platform used to build the library. @BR
   * For example "Win32".
   */
  static const char* getPlatformString();

  /** Returns as a string the internal VSG build number. */
  static const char* getInternalBuildString();

  /** Returns TRUE if the library was built in debug mode. */
  static bool isDebug();

  /** Returns TRUE if the library was built with _SECURE_SCL=1 compiler flag. */
  static bool isSCLFlag();

  /** Returns the Open Inventor version of the library. @BR
   *  For example 8500 for version 8.5.0
   */
  static int getProductVersion();
};

#ifndef HIDDEN_FROM_DOC

#ifdef LIBRARYBUILD

class INVENTORBASE_API SoModule
{
protected:
  SoModule( const char* libName,
    const char* version,
    const char* compiler,
    const char* plateform,
    const bool debug,
    const bool is_secure_scl );
private:
  SoModule() {};
};

#include <SoVersion.h>
#include <SoCompilerResourcePreproc.i>
#if defined(_DEBUG)
#define IS_DEBUG 1
#else
#define IS_DEBUG 0
#endif

#if !defined(_SECURE_SCL) || (_SECURE_SCL==1)
#define IS_SECURE_SCL 1
#else
#define IS_SECURE_SCL 0
#endif

#define SO_MODULE_HEADER( className, libName) \
class className##Module : public SoModule \
{ \
 public: \
  className##Module() \
  : SoModule( libName, SO_PRODUCT_VERSION, COMPILER_STRING, SO_PRODUCT_STRING_PLATFORM, IS_DEBUG , IS_SECURE_SCL) {} \
};

#define SO_MODULE_SOURCE( className ) \
className##Module g_##className##Module

#else
#define SO_MODULE_HEADER( className, libName)
#define SO_MODULE_SOURCE( className ) ;

#endif // LIBRARY_BUILD

#endif // HIDDEN_FROM_DOC

#endif // SO_MODULE
