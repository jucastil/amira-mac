/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/

#ifndef _SODYNAMICLIBMANAGER_
#define _SODYNAMICLIBMANAGER_

#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>


/**
 *
 * @VSGEXT Class for managing dynamic libraries.
 *
 * @ingroup General
 * This class is used to dynamically load/unload dynamic libraries and can be used
 * to inquire if a specified function is available within a specified library.
 *
 *
 * [OIV-WRAPPER-NO-WRAP]
 */



class INVENTORBASE_API SoDynamicLibManager {

public:
  /**
   * Loads a dynamic library using the specified @I libName@i.
   * @I libName @i can include an absolute or relative path.
   * If no path is supplied, the library will be searched for in the
   * following paths: @BR
   * - Windows: The directory where Inventor.dll is, the application directory, the current directory,
   * the system directory, the Windows directory, \%PATH%, and \%OIV_LD_LIBRARY_PATH% (single path). @BR
   *
   * - UNIX: $LD_LIBRARY_PATH, $OIV_LD_LIBRARY_PATH (single path).
   *
   * - MacOS: $DYLD_LIBRARY_PATH, $OIV_LD_LIBRARY_PATH (single path).
   */
  static SbBool loadLibrary(const SbString& libName, const bool reportError=true);


  /**
   * Unloads a dynamic library previously loaded by the above method.
   */
  static SbBool unloadLibrary(const SbString& libName);

  /**
   * Unloads all dynamic libraries previously loaded by the class.
   */
  static void unloadAllLibraries();


  /**
   * Inquires if the given library is already loaded by this class.
   */
  static SbBool isLibraryLoaded(const SbString& libName);


#ifdef OIV_NET_DOC
  /**
  * Inquires if the specified function is available in the specified library.
  * Returns a reference to this function, or NULL if not found.
  * Open Inventor will load the specified library if it is not already loaded.
  */

#else
  /**
  * Inquires if the specified function is available in the specified library.
  * Returns a pointer to this function, or NULL if not found.
  * Open Inventor will load the specified library if it is not already loaded.
  */

#endif //OIV_NET_DOC
  static void* lookUpFunction(const SbString& libName, const SbString& funcName);


  /**
   * Allocates an array and fills it with the names of the libraries
   * loaded by this class.
   * Returns the number of elements in the array.
   */
  static int getLoadedLibraryList(SbString*& libList);


  /**
   * Returns the dynamic library suffix used on the current operating
   * system.
   */
  static SbString getLibrarySuffix();


  /**
   * Returns the full path of the library that contains the given symbol.
   * This function is not available on all platforms and
   * will return an empty string on some Unix systems.
   */
  static SbString getLibraryFromSymbol(void* symbol);

SoINTERNAL public:
  /**
   * Returns TRUE if the defined library is loaded by current process.
   * ONLY apply on Windows plateform; returns true on UNIX systems.
   */
  static bool isLoaded(const SbString&);
 
  /**
  * Returns a pointer to a given function, 
  * given a loaded library handle.
    returns NULL if function is not found
  */
  static void* libLookUpFunction(const SbHandle libHandle, const SbString& funcName);

  static void exit();

  struct INVENTORBASE_API SafeLibraryHandle
  {
  private:
    SbString  m_libName;
    bool      m_hasDispose;

  public:
    SafeLibraryHandle();
    SafeLibraryHandle(const SbString &libName);
    ~SafeLibraryHandle();

    SbHandle getHandle() const;
    void release();
  };

  static SbHandle getLibraryHandle(const SbString& libName);

private:
  static SbString extractLibName(const SbString& s);


  static void* m_libMap;
};

#endif
