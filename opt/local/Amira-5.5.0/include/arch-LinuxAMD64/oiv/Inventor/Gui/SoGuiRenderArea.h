/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef SO_GUI_RENDER_AREA_H
#define SO_GUI_RENDER_AREA_H

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiRenderArea
//
// SoXXRenderArea implementation class
//
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/SoGuiGLWidget.h>
#include <Inventor/nodes/SoCamera.h> // stereo settings
#include <Inventor/nodes/SoFullSceneAntialiasing.h>
#include <Inventor/SbElapsedTime.h>

class SoNode;
class SoFrameGrabber;
class SbThreadSemaphore;
class ScTracking;
class SoSelection;
class SoMPEGRenderer;
class SoIdleSensor;

#ifndef HIDDEN_FROM_DOC
typedef void (*soSelectionChangeCB)(void *, SoSelection* data);
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiRenderArea : public SoGuiGLWidget
{
#ifndef HIDDEN_FROM_DOC
 SO_FIELDCONTAINER_HEADER( SoGuiRenderArea );
#endif

SoINTERNAL public:
 SoSFVec2i32 position;
 SoSFVec2i32 globalPosition;
 SoSFFieldContainer sceneManager;
 SoSFBool stereoAbsoluteAdjustments;
 SoSFFloat stereoOffset;
 SoSFFloat stereoBalance;
 SoSFBool stereoNearFrac;
 SoSFBool stereoReversed;

 SoSFFieldContainer cameraBase;

 /**
  * Constructor.
  */
 SoGuiRenderArea();
 SoGuiRenderArea( bool sync );

 /**
  * Sets the scene graph to be rendered in this component's window.
  */
 virtual void setSceneGraph( SoNode* newScene );

 /**
  * Gets the scene graph to be rendered in this component's window.
  */
 virtual SoNode* getSceneGraph();

 /**
  * Sets the scene graph to be rendered in the overlay plane. NOTE: This feature
  * requires a graphics board that supports an overlay plane.
  */
 void setOverlaySceneGraph( SoNode* newScene );

 /**
  * Gets the scene graph to be rendered in the overlay plane. NOTE: This feature
  * requires a graphics board that supports an overlay plane.
  */
 SoNode* getOverlaySceneGraph();

 /**
  * Sets the background color for this window. Default is black (0,0,0). @BR
  *  @BR
  * The default value can be set using the environment variable
  * OIV_BACKGROUND_COLOR (3 floats representing RGB values of the colors separated by space).
  */
 void setBackgroundColor( const SbColor& c );

 /**
  * Gets the background color for this window.
  */
 const SbColor& getBackgroundColor() const;

 /**
  * Sets the window background color when in color index mode. Default is black
  * (index 0)).
  */
 void setBackgroundIndex( int index );

 /**
  * Gets the window background color when in color index mode.
  */
 int getBackgroundIndex() const;

 /**
  * Sets the overlay window background color index. Default is 0 (clear
  * color)).
  */
 void setOverlayBackgroundIndex( int index );

 /**
  * Gets the overlay window background color index.
  */
 int getOverlayBackgroundIndex() const;

 /**
  * Sets viewport region to use for rendering.
  */
 void setViewportRegion( const SbViewportRegion& newRegion );

 /**
  * Gets current viewport region to use for rendering.
  */
 const SbViewportRegion& getViewportRegion() const;

 /**
  * Sets the quality level for rendering transparent objects. See
  * SoGLRenderAction for possible transparency types.
  */
 void setTransparencyType( SoGLRenderAction::TransparencyType type );

 /**
  * Gets the quality level for rendering transparent objects. See
  * SoGLRenderAction for possible transparency types.
  */
 SoGLRenderAction::TransparencyType getTransparencyType() const;

 /**
  * Sets fast editing save policy to use when rendering. The default is DISABLE.
  * Valid values are DISABLE, EACH_FRAME, and WHEN_NEEDED. See SoSeparator.
  * @BR
  * @BR
  * If fastEditDelayedObjects is set to TRUE, delayed objects won't be redrawn
  * when editing the scene graph. This may provide better performance, but
  * composition between delayed transparent objects
  * and fast edit scene graph won't be correct.
  */
 void setFastEditSavePolicy( SoGLRenderAction::FastEditSavePolicy policy,
                             SbBool fastEditDelayedObjects = FALSE);

 /**
  * Returns fast editing save policy used when rendering.
  */
 SoGLRenderAction::FastEditSavePolicy getFastEditSavePolicy() const;

 /**
  * This method specifies the angle between each sorting axis when using the
  * transparency type SORTED_TRIANGLES_XXX or SORTED_OBJECT_TRIANGLES_XXX.
  * @BR
  * Transparent triangles are sorted based on the nearest axis.
  * (in terms of the dot (inner) product). If the triangles have
  * already been sorted on this axis (or the opposite), and the sort result is cached,
  * the triangles are rendered using the cached information.
  *
  * The default value for sort frequency is 90, meaning that a sorting is made every 90 degrees.
  * If the value is 0, sorting is always done
  * and the camera orientation vector is the axis used for sorting. In this case, no
  * cache is made.
  *
  * See SoGLRenderAction for additional details and figures.
  */
 void setSortedTrianglesSortFrequency( int angle );

 /**
  * Returns the sort frequency used for the SORTED_TRIANGLES_XXX and
  * SORTED_OBJECT_TRIANGLES_XXX transparency types.
  */
 int getSortedTrianglesSortFrequency();

 /**
  * Sets the number of caches to use when the transparency type is
  * SORTED_TRIANGLES_XXX or SORTED_OBJECT_TRIANGLES_XXX. This specifies the number
  * of lists of sorted triangles to keep in memory in order to render
  * transparent triangles more quickly.
  *
  * When computing a new list of sorted triangles, if an empty cache is available,
  * it is used.
  * Else, the farthest axis
  * from the camera orientation axis is replaced in the cache.
  * The default number of caches is 3.
  */
 void setSortedTrianglesNumCaches( int numCaches );

 /**
  * Returns the maximum number of caches allowed for the sorted triangles transparency types.
  */
 int getSortedTrianglesNumCaches();

 /**
  * Enables or disables the invalidation of render caches.
  * - When set to ALWAYS, the caches are invalidated for each SoSeparator node before
  *   its children are traversed. No new caches will be built. This value forces
  *   all nodes to be visited during each render traversal.
  *
  * - When set to ONCE, the caches are invalidated for each SoSeparator node before
  *   its children are traversed. The
  *   invalidate cache mode is automatically changed to OFF at the end of the traversal.
  *
  * - When set to OFF (default), caches are managed by their respective render caching
  *   nodes in the usual way.
  *
  * This method is useful to force all nodes to be visited during render traversal.
  */
 void setInvalidateCacheMode( SoGLRenderAction::InvalidateCacheMode icm );

 /**
  * Returns the current cache invalidation mode.
  */
 SoGLRenderAction::InvalidateCacheMode getInvalidateCacheMode();

 /**
  * Sets the antialiasing for rendering. There are two kinds of antialiasing
  * available: smoothing and multipass antialiasing. If smoothing is set to TRUE,
  * smoothing is enabled. Smoothing uses OpenGL's line- and point-smoothing features
  * to provide cheap antialiasing of lines and points. The value of @B numPasses @b
  * controls multipass antialiasing. Each time a render action is applied, Open
  * Inventor renders the scene @B numPasses @b times from slightly different camera
  * positions, averaging the results. @B numPasses @b can be from one to 255,
  * inclusive. Setting @B numPasses @b to one disables multipass antialiasing. You
  * can use either, both, or neither of these antialiasing techniques. By default,
  * both smoothing and multipass antialiasing are disabled.
  */
 void setAntialiasing( SbBool smoothing, int numPasses );

 /**
  * Gets the antialiasing for rendering. See setAntialiasing() for details.
  */
 void getAntialiasing( SbBool& smoothing, int& numPasses ) const;

 /**
  * Enables/prevents window clearing from happening before a rendering starts (default
  * is clear TRUE). This can be useful to limit flickering when doing single
  * buffering and geometry covers the entire window (used in the material editor).
  * Also controls whether the depth buffer (sometimes called the Z buffer) is
  * cleared before rendering.
  */
 void setClearBeforeRender( SbBool trueOrFalse, SbBool zbTrueOrFalse = TRUE );

 /**
  * Queries whether the window will be cleared before rendering starts.
  */
 SbBool isClearBeforeRender() const;

 /**
  * Queries whether the depth buffer (sometimes called the Z buffer) will be
  * cleared before rendering starts.
  */
 SbBool isClearZBufferBeforeRender() const;

 /**
  * Enables/prevents overlay window clearing from happening before a rendering starts
  * (default is clear TRUE).
  */
 void setClearBeforeOverlayRender( SbBool trueOrFalse );

 /**
  * Queries whether the overlay window will be cleared before rendering starts.
  */
 SbBool isClearBeforeOverlayRender() const;

 /**
  * The render area will automatically redraw whenever something in the scene graph
  * changes. Passing FALSE will disable this feature.
  */
 void setAutoRedraw( SbBool trueOrFalse );

 /**
  * Queries whether the render area will automatically redraw whenever something
  * in the scene graph changes.
  */
 SbBool isAutoRedraw() const;

 /**
  * Sets the priority of the redraw sensor.
  */
 void setRedrawPriority( uint32_t priority );

 /**
  * Gets the priority of the redraw sensor.
  */
 uint32_t getRedrawPriority() const;

 /**
  * Gets the default priority number of the redraw sensor.
  */
 static uint32_t getDefaultRedrawPriority();


 /**
  * Sets the normal scene manager.
  *
  * Note: For convenience most of the SoSceneManager methods have already been added
  * to this class.
  */
  void setSceneManager( SoSceneManager* sm );

 /**
  * Gets the normal scene manager.
  *
  * Note: For convenience most of the SoSceneManager methods have already been added
  * to this class.
  */
 SoSceneManager* getSceneManager() const;

 /**
  * Sets the overlay plane scene manager.
  *
  * Note: For convenience most of the SoSceneManager methods have already been added
  * to this class.
  */
 void setOverlaySceneManager( SoSceneManager* sm );

 /**
  * Gets the overlay plane scene manager.
  *
  * Note: For convenience most of the SoSceneManager methods have already been added
  * to this class.
  */
 SoSceneManager* getOverlaySceneManager() const;

 /**
  * Sets the GL render action to use. This is used to set selection
  * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
  * classes.
  */
 void setGLRenderAction( SoGLRenderAction* ra );

 /**
  * Gets the GL render action to use. This is used to set selection
  * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
  * classes.
  */
 SoGLRenderAction* getGLRenderAction() const;

 /**
  * Sets the GL render action for the overlay window.
  */
 void setOverlayGLRenderAction( SoGLRenderAction* ra );

 /**
  * Gets the GL render action for the overlay window.
  */
 SoGLRenderAction* getOverlayGLRenderAction() const;

  /**
  * Gets the default render area size.
  */
 static SbVec2s getDefaultSize();

  /**
   * Invoke the app callback and return what the callback returns.
   */
  SbBool invokeAppCB( const SoEvent* anyevent );

  /**
   * Notify redraw action.
   */
  virtual void notifyRedraw();
  virtual void signalRedraw();
  virtual void cleanRedraw();

  /**
   * Propagate notification.
   */
  virtual void notify( SoNotList* );

  /**
  * Hide or show DirectViz control dialog
  */
  virtual void showDirectVizDialog( SbBool show );

  /**
  * Load DirectViz Gui library if needed. Returns true if library is loaded
  */
  SbBool checkDirectVizGuiLoaded();

#ifdef DIRECTVIZ_SUPPORT
#ifndef NO_PASSWORD
  // DirectViz password check
  static SbBool DirectVizLicenceCheck;
#endif
#endif

  /**
  * Check for a DirectViz license in order to manage entry in viewer popup menu
  */
  void checkDirectVizLicense();

  /** 
   * Sets the recorder used for MPEG encoding.
   *
   * @param recorder the recorder to be used.
   */
  virtual void setMPEGRecorder( SoMPEGRenderer* recorder );

  /** 
   * Returns the recorder used for MPEG encoding.
   */
  virtual SoMPEGRenderer* getMPEGRecorder() const;

  // ----------------------- Extension usage -----------------------------------

 void setStereoMode( SoCamera::StereoMode stMode );
 void setStereoElement();

 void setRedrawing( SbBool redrawing );
 SbBool isRedrawing() const;

 SbBool isInteractive() const;

 void setStereoOffset( float offset );
 float getStereoOffset() const;

 void setStereoReversed( SbBool reverse );
 SbBool getStereoReversed() const;

 void setStereoAbsoluteAdjustments( SbBool absolute );
 SbBool getStereoAbsoluteAdjustments() const;

 void setStereoBalance( float balance, SbBool nearFrac = false );
 float getStereoBalance() const;
 SbBool isStereoBalanceNearFrac() const;

 virtual void setDoubleBufferRA(SbBool db);

 virtual void actualRedraw();
 virtual void actualOverlayRedraw();

 virtual void initGraphic();
 void redrawCleanUp();

 void activate();             // connects the sensor
 void deactivate();           // disconnects the sensor

 void posChanged( const SbVec2i32& newPos, const SbVec2i32& newGPos );

 void setFrameGrabber( SoFrameGrabber* grabber );
 SoFrameGrabber* getFrameGrabber() const;

  /**
   * Sensor callback used to render remote/composed frame asynchronously.
   */
  //static void asyncPaintSensorCB( void *data, SoSensor * );

  /**
   * Sensor responsible to schedule the asyncPaintSensor
   */
  //SoOneShotSensor *m_asyncPaintSensor;

  // called at the begining of redraw call
  void preRedraw();

  // called at the end of redraw call
  virtual void postRedraw();

  // call when selection changed
  void redrawOnSelectionChange( SoSelection* s );

  // call when overlay selection changed
  void redrawOverlayOnSelectionChange( SoSelection* s );


  // setup system dependent renderArea handles.
  void setRenderAreaHandle(const void *renderAreaHandle, soSelectionChangeCB _selectionChangedCB, soSelectionChangeCB _overlaySelectionChangedCB);
  void *m_renderAreaHandle;
  soSelectionChangeCB selectionChangeCB;
  soSelectionChangeCB overlaySelectionChangeCB;

  inline SoFrameGrabber* getGrabber() const;

  /** Gets fps count since last reset. */
  unsigned int getFPSCount();

protected:

  /**
   * Destructor.
   */
  virtual ~SoGuiRenderArea();

  int m_interactiveCount;
  unsigned int m_fpsCount;
  SbElapsedTime m_fpsTimer;
  double m_previousfpsTime;
  bool m_usefpsCallback;

  // MPEG recording
  SoMPEGRenderer* m_mpegRenderer;

// ----------------------- Private usage -------------------------------------
private:
  void commonConstructor();

  // these make rendering/redrawing happen
  SoSceneManager* m_sceneMgr;      // this manages rendering and events
  SoSceneManager* m_overlaySceneMgr; // manages the overlay scene graph
  SbBool m_autoRedraw;     // if TRUE, then we automatically redraw
  SbBool m_clearFirst, m_clearOverlayFirst;  // call clear() before rendering
  SbBool m_clearZBufferFirst;      // clear ZBuffer before rendering
  SbBool m_isRedrawing;
  SoFrameGrabber* m_grabber;
  ScTracking* m_tracking;
  SoCamera* m_cameraBase;

  SoSelection* selection, *overlaySelection;

  // Floating point rendering
  SbBool m_isFloatingPointRendering;
  FloatColorBufferSize m_floatingPointRenderingPrecision;

  // stereo adjustment
  SoCamera::StereoMode m_stereoMode;

  SbThreadSemaphore* m_redrawSem;
  
  SoIdleSensor *m_IvTuneRefreshSensor; 
};

SoFrameGrabber* SoGuiRenderArea::getGrabber() const
{
  return m_grabber;
}

inline unsigned int
SoGuiRenderArea::getFPSCount()
{
  return m_fpsCount;
}

#endif // SO_GUI_RENDER_AREA_H

