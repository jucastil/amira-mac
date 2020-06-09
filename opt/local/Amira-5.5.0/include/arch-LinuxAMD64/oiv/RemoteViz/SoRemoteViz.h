/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (July 2010)
**=======================================================================*/


#ifndef SO_REMOTEVIZ_H
#define SO_REMOTEVIZ_H

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __REMOTEVIZLIB  "RemoteVizD.lib"
#    define __REMOTEVIZDLL  "RemoteVizD.dll"
#  else
#    define __REMOTEVIZLIB  "RemoteViz.lib"
#    define __REMOTEVIZDLL  "RemoteViz.dll"
#  endif
#  ifndef RemoteViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__REMOTEVIZLIB)
#    endif
#  endif
#else
#  define __REMOTEVIZDLL  "libRemoteViz"
#endif

class SoScaleVizConfig;
class SoGuiBase;

#include <Inventor/SoModule.h>
SO_MODULE_HEADER( SoRemoteViz, __REMOTEVIZDLL )

#include <Inventor/SbColor.h>

/**
 * @SCVEXT RemoteViz initialization
 * 
 * @ingroup RemoteViz
 * 
 * @DESCRIPTION
 *
 * This class performs RemoteViz initialization.
 */ 

class REMOTEVIZ_API SoRemoteViz
{

public:

  /**
   * Initializes RemoteViz.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /** 
   * Shuts down the RemoteViz module, which includes freeing any
   * internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls: 
   * @code
   *    SoRemoteViz::finish(); 
   *    SoXt::finish(); 
   *    ... 
   * @endcode
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if SoRemoteViz::init has been called.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /** Returns TRUE if at least one client is connected to this application remotely. */
  static bool isClientConnected();

  /** Make required GL call to reset server viewer color mask. */
  static void applyVncColorMask( SbColor& );

SoINTERNAL public:

  static bool mustDraw();

private:
  static int s_initRefCount;
};

#endif // SO_REMOTEVIZ_H

/**/
