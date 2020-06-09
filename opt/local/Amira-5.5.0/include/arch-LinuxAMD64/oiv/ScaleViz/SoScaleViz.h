/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2007)
**=======================================================================*/


#ifndef SO_SCALEVIZ_H
#define SO_SCALEVIZ_H

#include <Inventor/SbString.h>

typedef void* scaleviz_ptr;
typedef int32_t ScStreamSize;
typedef int32_t ScStreamType;
typedef int64_t ScMemObjStreamPtr;

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __SCALEVIZLIB  "ScaleVizD.lib"
#    define __SCALEVIZDLL  "ScaleVizD.dll"
#  else
#    define __SCALEVIZLIB  "ScaleViz.lib"
#    define __SCALEVIZDLL  "ScaleViz.dll"
#  endif
#  ifndef ScaleViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__SCALEVIZLIB)
#    endif
#  endif
#else
#  define __SCALEVIZDLL  "libScaleViz"
#endif

class SoScaleVizConfig;

#include <Inventor/SoModule.h>
SO_MODULE_HEADER( SoScaleViz, __SCALEVIZDLL )

/**
 *
 * @SCVEXT ScaleViz initialization
 * 
 * @ingroup ScaleViz
 * 
 * @DESCRIPTION
 *
 * This class performs ScaleViz initialization.
 *
 */ 

class SCALEVIZ_API SoScaleViz
{

public:

  enum CompositingType {
    NONE  = 0,
    TILE  = 1 << 0,
    DEPTH = 1 << 1
  };

public:

  /**
   * Returns a character string identifying the name of the extension.
   */
  static SbString getProductName();

  /**
   * Returns a character string identifying the version of extension 
   * ("major.minor.patch_number").
   */
  static const char *getVersion();

  /**
   * Returns a character string identifying the version of extension.
   * ("major.minor").
   */
  static const char *getCompactVersion();

  /**
   * Returns the compilation date of the current version.
   */
  static const char *getCompilationDate();

  /**
   * Initializes ScaleViz. Initialization is handled automatically
   * by Open Inventor. It is not necessary to call this method in
   * a user application.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /** 
   * Shuts down the ScaleViz module, which includes freeing any
   * internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls: 
   * <PRE>    SoScaleViz::finish(); 
   *    SoXt::finish(); 
   *    ... </PRE>
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();
  
  /**
   * Returns TRUE if SoScaleViz::init has been called.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * @deprecated DMX is no more supported.
   * Returns TRUE if using a DMX configuration.
   * @DEPRECATED_SINCE_OIV 8.0
   */  
  SoDEPRECATED static bool isUsingDMX();

  /**
   * Returns TRUE if using a Vnc configuration.
   */  
  static bool isUsingVnc();

  /**
   * Returns the compositing type currently used (if any).
   */
  static CompositingType isComposing();
  
  /**
   * Returns TRUE if using ScaleViz cluster mode.
   */
  static bool isRunningCluster();
  
  /**
   * Returns TRUE if running on part of an OIRU.
   */
  static bool isOiru();

  /**
   * Indicates which function is responsible for registering classes
   * of the given module.
   */
  typedef void InitCallback(void);

  /**
   * @deprecated Indicates which function is responsible for registering classes
   * of the given module.
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoDEPRECATED static void registerInit(SbString moduleName, InitCallback* initFunction);

  /**
   * Returns the number of render units currently running.
   */
  static int getNumRenderUnits();

  /**
   * Returns TRUE if a redraw is done on the application side.
   */
  static bool isLocalRedraw();

  /**
   * Adds a new configuration to ScaleViz. Returns false if the configuration
   * is not valid (e.g., if there are syntax errors). 
   */
  static bool addConfig( SoScaleVizConfig* config );

  /**
   * Adds a new configuration to ScaleViz. Returns false if the configuration
   * is not valid (e.g., if there are syntax errors). 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static bool addConfigFromFile( const char* filename );

  /**
   * Adds a new configuration to ScaleViz. Returns false if the configuration
   * is not valid (e.g., if there are syntax errors). 
   */
  static bool addConfigFromFile( const SbString& filename );

  /**
   * Removes configuration from ScaleViz. Returns true if the configuration
   * has been successfully removed.
   */
  static bool removeConfig( SoScaleVizConfig* config );
  
  /**
   * Remove all configurations defined using the passed filename.
   * Returns the number of removed configurations.
   */
  static int32_t removeConfigFromFile( const char* filename );

  /**
   * Specifies the ScaleViz configuration to launch at connection time.
   * Returns false if the specified configuration is not available or cannot be selected.
   */
  static bool setSelectedConfiguration( SoScaleVizConfig* config );

  /**
   * Specifies the ScaleViz configuration to launch at connection time.
   * Returns false if the specified configuration is not available or cannot be selected.
   */
  static bool setSelectedConfiguration( SbString& configName );

  /**
   * Returns the currently selected configuration.
   */
  static SoScaleVizConfig* getSelectedConfiguration();

  /**
   * Returns the i-th configuration from the list of registered configurations.
   */
  static SoScaleVizConfig* getConfiguration( const int32_t index );

  /**
   * Returns the number of registered configurations.
   */
  static int32_t getConfigurationCount();

  /**
   * Launches the connection process using the active configuration.
   */
  static void connect();

  /**
   * Disconnects from the cluster.
   */
  static void disconnect();

  /**
   * Returns true when ScaleViz is connected to the cluster.
   */
  static bool isConnected();

  /**
   * Returns true if remote rendering is enabled (see OIV_REMOTE_ENABLE)
   */
  static bool isRemoteEnabled();

SoINTERNAL public:
  static void setRunningQt(const bool b, int qtVersion = 0);
  static void setRunningWx(const bool b);

  /** Returns TRUE if current running configuration is multipipe. */
  static bool isRunningMultipipe();
  static bool isRunningART();

private:
  static int m_isInitialized;
};

inline bool
SoScaleViz::isRunningCluster()
{
  return isConnected();
}

#endif // SO_SCALEVIZ_H

/**/
