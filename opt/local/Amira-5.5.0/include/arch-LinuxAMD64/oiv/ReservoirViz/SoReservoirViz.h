/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (May 2006)
**=======================================================================*/

#ifndef _SO_RESERVOIR_VIZ_
#define _SO_RESERVOIR_VIZ_

#include <LDM/SoLDMLargeDataManagement.h>



// On Windows the "comment" pragma will automatically add the ReservoirViz
// Rendering library to the application's link string.
#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __RESVIZDLL "ReservoirVizD.dll"
#    define __RESVIZLIB "ReservoirVizD.lib"
#  else
#    define __RESVIZDLL "ReservoirViz.dll"
#    define __RESVIZLIB "ReservoirViz.lib"
#  endif
#  ifndef ReservoirViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__RESVIZLIB)
#    endif
#  endif
#else
#    define __RESVIZDLL "libReservoirViz"
#endif // _WIN32

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoReservoirViz, __RESVIZDLL)

#if defined(_WIN32)
typedef          __int64  int64_t;
typedef unsigned __int64 uint64_t;
#else // UNIX
# include <inttypes.h>
#endif // _WIN32/UNIX


/**
 * @RVEXT Initialization of the ReservoirViz extension.
 * 
 * @ingroup ReservoirViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the ReservoirViz module. The module
 *   must be initialized before using any other classes of the module.
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 
class RESERVOIRVIZ_API SoReservoirViz
{

 public:
  /**
   * Initializes the ReservoirViz module database. This must be called before the
   * construction of any ReservoirViz nodes.
   * 
   * Typically, this method must be called just after SoXt::init() or SoWin::init():
   * 
   * <PRE>
   *    SoXt::init(); 
   *    SoReservoirViz::init(); 
   *    ... </PRE>
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void		init();

  /**
   * Shuts down the ReservoirViz module, which includes freeing 
   * any internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls:
   * <PRE>
   *    SoReservoirViz::finish(); 
   *    SoXt::finish(); 
   *    ... </PRE>
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  static int s_initRefCount;
  SoReservoirViz();


};

#endif //_SO_RESERVOIR_VIZ_
