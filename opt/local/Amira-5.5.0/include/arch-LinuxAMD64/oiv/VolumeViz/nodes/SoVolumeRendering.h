/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_VOLUME_RENDERING_
#define  _SO_VOLUME_RENDERING_

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4251)
#  pragma warning(disable:4244)
#endif

// On Windows the "comment" pragma will automatically add our Volume
// Rendering library to the application's link string.
#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __IVVRDLL "VolumeVizD.dll"
#    define __IVVRLIB "VolumeVizD.lib"
#  else
#    define __IVVRDLL "VolumeViz.dll"
#    define __IVVRLIB "VolumeViz.lib"
#  endif
#  ifndef VolumeViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__IVVRLIB)
#    endif
#  endif
#else // _WIN32
#  define __IVVRDLL "libVolumeViz"
#endif // _WIN32

#include <Inventor/nodes/SoSubNode.h>
#include <LDM/SoLDMGlobalResourceParameters.h>
#include <LDM/nodes/SoHardwareQuery.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoVolumeViz, __IVVRDLL)

class SoLDMTileManager;

/**
 * @VREXT Initializes the VolumeViz module database.
 * 
 * @ingroup VolumeVizNodes
 * 
 * @DESCRIPTION
 *   This abstract class is the base class for all volume rendering modules. It is
 *   used only for initializing the VolumeViz extension and setting some global
 *   parameters.
 *
 *   The init() method must be called before creating any VolumeViz nodes.
 *   The finish() method should be called when the application is shutting down.
 * 
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoTransferFunction,
 *    SoVolumeRender,
 *    SoOrthoSlice,
 *    SoObliqueSlice,
 *    SoROI,
 *    SoVolumeReader,
 *    SoLDMGlobalResourceParameters
 * 
 */ 

class VOLUMEVIZ_API SoVolumeRendering {

 public:
  /**
   * Initializes the VolumeViz module database. This must be called before the
   * construction of any VolumeViz nodes.
   * 
   * Generally this method should be called immediately after initializing
   * Open Inventor. In other words just after SoXt::init(), SoWin::init(), etc.
   *
   * Starting with Open Inventor version 8.5, this method @B must @b called
   * before any instances of SoSceneManager are created.  When using the Open
   * Inventor viewer classes, an SoSceneManager is created automatically when
   * the viewer is created.  So this method should be called before creating
   * the viewer.
   * 
   * <PRE> 
   *    SoXt::init(); 
   *    SoVolumeRendering::init(); 
   *    ... </PRE>
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void		init();

  /** 
   * Shuts down the VolumeViz module, which includes freeing any
   * internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls: 
   * <PRE>    
   *    SoVolumeRendering::finish(); 
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

  ////////////////////////////////////////////////////////////////////////////////
  // Alternate Representation section

  /**
   * Sets the @B writeAlternateRep @b flag. @BR
   * When this flag is TRUE during an SoWriteAction traversal, some
   * VolumeViz nodes will write an @B alternateRep @b subgraph
   * containing only standard Open Inventor nodes that can be rendered
   * even without VolumeViz.  For example, SoOrthoSlice will write an
   * SoTexture2 node and an SoFaceSet node.
   * The default is FALSE.
   */
  static void   setWriteAlternateRep( SbBool flag );

  /**
   * Returns the @B writeAlternateRep @b flag.
   */
  static SbBool getWriteAlternateRep();

  /**
   * Sets the @B readAlternateRep @b flag. <br>
   * When this flag is TRUE while reading an Open Inventor file, any
   * @B alternateRep @b subgraphs attached to VolumeViz nodes are read and
   * added to the scene graph. Otherwise, @B alternateRep @b subgraphs are discarded
   * and the @B alternateRep @b field is set to NULL. The default is FALSE.
   */
  static void   setReadAlternateRep( SbBool flag );

  /**
   * Returns the @B readAlternateRep @b flag.
   */
  static SbBool getReadAlternateRep();

  ////////////////////////////////////////////////////////////////////////////////
  // Delayed Rendering section

  /**
   * Sets the @B delayedRendering @b flag. @BR
   * When this flag is TRUE (default), VolumeViz drawing nodes (e.g., SoOrthoSlice) are
   * considered "transparent" objects by Open Inventor. They may be delayed
   * (until after all opaque objects) and/or sorted according to the current
   * transparency type (see SoGLRenderAction). This may result in a more
   * correct image if there is opaque geometry intersecting the volume.
   * However delayed/sorted rendering may slightly decrease performance.
   * This flag may also be set using the IVVR_DELAY_RENDER environment variable.
   */
  static void   setDelayedRendering( SbBool flag );

  /**
   * Returns the @B delayedRendering @b flag.
   */
  static SbBool getDelayedRendering();

  ////////////////////////////////////////////////////////////////////////////////
  //------------------------------------------------------------------------------

  /**
   * Hardware Features Mode 
   */
  enum HW_Feature {
  /**
   *  The system supports OpenGL 3D texture mapping.
   * On some boards, this query may return TRUE even
   * if your board does not support accelerated
   * 3D textures. In this case performance may
   * be slow, and you may prefer to use
   * 2D textures instead. Note: The inability
   * to determine if 3D textures are accelerated 
   * is a limitation of OpenGL, not Open Inventor.
   */
    HW_3DTEXMAP = SoHardwareQuery::HW_3DTEXMAP,
  /**
   *  The system supports the OpenGL paletted
   *  texture extension and/or the texture color table
   *  extension. 
   */
    HW_TEXCOLORMAP = SoHardwareQuery::HW_TEXCOLORMAP,
  /**
   *  The system supports the OpenGL texture
   *  compression extension.
   */
    HW_TEXCOMPRESSION = SoHardwareQuery::HW_TEXCOMPRESSION
  };

  /**
   * Hardware Features support status
   */
  enum HW_SupportStatus {
    /** Not supported */
    NO = SoHardwareQuery::NO,
    /** Supported */
    YES,
    /** unknown status */
    UNKNOWN
  };

  /**
   * Returns information about hardware support for various volume rendering
   * features. This query is only valid after SoVolumeRendering::init has been
   * called. Otherwise the return value will be UNKNOWN.
   */
  static HW_SupportStatus isSupported( HW_Feature feature );

  ////////////////////////////////////////////////////////////////////////////////
  // Memory Control Parameters section

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setMaxMainMemory(int MaxMainMemory)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setMaxMainMemory( int maxMainMemory );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getMaxMainMemory()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static int  getMaxMainMemory();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setMaxTexMemory(int maxTexMemory)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setMaxTexMemory( int maxTexMemory );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getMaxTexMemory()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static int  getMaxTexMemory();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setTex3LoadRate(int loadRate)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setTex3LoadRate( int loadRate );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getTex3LoadRate()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static int getTex3LoadRate();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setNumIO()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setNumIO(unsigned int numIO);

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getNumIO()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static unsigned int getNumIO();

  ////////////////////////////////////////////////////////////////////////////////
  // VisualFeedback Parameters section

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::VisualFeedbackParam enum
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  enum VisualFeedbackParam {
  /** 
   * Draw the tiles of SoVolumeRender or SoVolumeSkin primitives. They are drawn by default.
   */
    DRAW_TILES = SoLDMGlobalResourceParameters::DRAW_TILES,
  /** 
   * Use texturing for SoOrthoSlice, SoObliqueSlice, and SoVolumeSkin primitives. They are used by default.
   */
    DRAW_SLICES_TEX  = SoLDMGlobalResourceParameters::DRAW_SLICES_TEX,
  /** 
   * Show tiles loaded in main memory. 
   * This implies showing the multiresolution topology. 
   * The tile outlines of tiles of full resolution are drawn with
   * a brighter yellow.
   * The topology is not drawn by default.
   * @IMAGE drawtopology.jpg
   */
    DRAW_TOPOLOGY  = SoLDMGlobalResourceParameters::DRAW_TOPOLOGY,
  /** 
   * Draw tile outlines for all primitives. The tile outline of tiles of full resolution
   * are drawn with a brighter gray for the volume, and a brighter green for the slices.
   * Outlines are not drawn by default.
   * @IMAGE drawtileoutline.jpg
   */
    DRAW_TILE_OUTLINE  = SoLDMGlobalResourceParameters::DRAW_TILE_OUTLINE,
  /** 
   * Show tiles visited by the Tile Visitor. They are not shown by default.
   *
   * For the default LDM implementation,
   * displays an octree representation showing traversal of the octree. Red dots are tiles
   * that have been valuated. Blue indicates the minimum and maximum resolution thresholds.
   * Yellow shows the octree itself.
   * @IMAGE showtilesvaluated.jpg
   */
    SHOW_TILES_VALUATED  = SoLDMGlobalResourceParameters::SHOW_TILES_VALUATED,
  /** 
   * Show tiles loaded (in red) and unloaded (in blue) in texture memory. They are not 
   * shown by default.
   */
    SHOW_LOAD_UNLOAD_TILES  = SoLDMGlobalResourceParameters::SHOW_LOAD_UNLOAD_TILES,
  /** 
   * Use fake data instead of the real data during loading into main memory. The fake data
   * is programmatically generated and is designed to illustrate features of Large Data Management.
   * Fake data is not used by default.
   * @IMAGE fakedata.jpg
   */
    USE_FAKE_DATA  = SoLDMGlobalResourceParameters::USE_FAKE_DATA
  };

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setVisualFeedbackParam( VisualFeedbackParam param, SbBool state )
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setVisualFeedbackParam( VisualFeedbackParam param, SbBool state );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getVisualFeedbackParam( VisualFeedbackParam param )
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED   static SbBool getVisualFeedbackParam( VisualFeedbackParam param );


  ////////////////////////////////////////////////////////////////////////////////
  // Viewing Parameters section

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setViewCulling( SbBool state )
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setViewCulling( SbBool state );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getViewCulling()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getViewCulling();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setScreenResolutionCulling(SbBool flag)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setScreenResolutionCulling( SbBool flag );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getScreenResolutionCulling()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getScreenResolutionCulling();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setIgnoreFullyTransparentTiles(SbBool state)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setIgnoreFullyTransparentTiles( SbBool state );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getIgnoreFullyTransparentTiles()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getIgnoreFullyTransparentTiles();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setViewpointRefinement(SbBool state)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setViewpointRefinement( SbBool state );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getViewpointRefinement()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getViewpointRefinement();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setSliceEqualResolution(SbBool state,SbBool forceRedraw)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setSliceEqualResolution( SbBool state, SbBool forceRedraw = TRUE );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getSliceEqualResolution()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getSliceEqualResolution();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setMoveLowResolution(SbBool state)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setMoveLowResolution( SbBool state );

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getMoveLowResolution()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static SbBool getMoveLowResolution();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setLoadNotificationRate(int rate)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setLoadNotificationRate(int);

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::getLoadNotificationRate()
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static int getLoadNotificationRate();

  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setLoadCB(...)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setLoadCB( SoLDMLoadCB *func, void *userData = NULL );
  
  /** @deprecated No longer used. Use SoLDMGlobalResourceParameters::setMonitoringCB(...)
   *  @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED static void setMonitoringCB( SoLDMMonitoringCB *func, int memAmount, void *userData = NULL );
 
 //////////////////////////////////////////////////////////////////////////////
 SoINTERNAL public:

  enum Cmd{
    SET_WRITE_ALTERNATE_REP = 0,
    SET_READ_ALTERNATE_REP,
    SET_DELAYED_RENDERING,
    SET_IGNORE_FULLY_TRANSPARENT_TILES,
    SET_MOVE_LOW_RES
  };
  
  // ------------------------------------------------------------

  static SbBool m_writeAlternateRep;  // write classic Inventor nodes
  static SbBool m_readAlternateRep;   // keep altRep when reading file
  static SbBool m_delayedRendering;   // enable delayed rendering

  // module ref counter
  static int s_initRefCount;

  SoVolumeRendering();

private:
  static const char* s_versionString;
};

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif // _SO_VOLUME_RENDERING_
