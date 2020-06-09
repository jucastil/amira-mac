/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_RENDER_AREA_H_
#define _SO_WIN_RENDER_AREA_H_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <windows.h>
#include <Inventor/Win/SoWinDef.h>

#include <Inventor/SbColor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/Win/SoWinGLWidget.h>
#include <Inventor/actions/SoGLRenderAction.h>

#include <Inventor/nodes/SoCamera.h> // stereo settings
#include <Inventor/elements/SoStereoElement.h>
#include <Inventor/nodes/SoFullSceneAntialiasing.h>
#include <Inventor/SbElapsedTime.h>

#include <Inventor/Gui/SoGuiRenderArea.h>

class SoHandleEventAction;
class SoWinDevice;
class SoNode;
class SoWinMouse;
class SoWinKeyboard;
class SoSelection;
class SoWinRenderArea;
class SoGuiAlgoViewers;

/**
 * [OIV-WRAPPER NAME{EventCallback}]
 */
typedef SbBool SoWinRenderAreaEventCB( void* userData, XAnyEvent* anyevent );

/**
 * [OIV-WRAPPER NAME{RenderCallback}]
 */
typedef SbBool SoWinRenderAreaRenderCB( void* userData, SoWinRenderArea* rendArea );

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinRenderArea
//
//  Class to do Inventor rendering in a GLX Motif widget.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Component for rendering Open Inventor scene graphs.
 *
 * @ingroup Win
 *
 * @DESCRIPTION
 *   This class provides Open Inventor rendering and message handling inside a
 *   Windows window. There is a routine to specify the scene to render. The scene is
 *   automatically rendered whenever anything under it changes (a data sensor is
 *   attached to the root of the scene), unless explicitly told not to do so (manual
 *   redraws). Users can also set Open Inventor rendering attributes such as the
 *   transparency type, antialiasing on or off, etc. This class employs an
 *   SoSceneManager to manage rendering and message handling.
 *
 *   Windows messages that occur in the render area can be handled by the application,
 *   by the viewer (if this is really a viewer), or by the nodes in the scene graph.
 *   When a message occurs, it is first passed to the application message \oivnetdoc delegate \else callback \endoivnetdoc
 *   function registered with the setEventCallback() method on
 *   SoWinRenderArea. If this function does not exist or returns FALSE, the message
 *   is either used directly by the viewer or translated to an SoEvent for further
 *   scene graph processing. If the viewer does not handle the message, and an
 *   overlay scene graph exists, the SoEvent is sent to that scene graph by way of an
 *   SoHandleEventAction. If no node in the overlay scene graph handles the message
 *   (i.e., calls setHandled() on the SoHandleEventAction), the SoEvent is
 *   passed to the normal scene graph in the same manner.
 *
 * @NOTES
 * 
 * Overlay rendering:
 * 
 * This class supports overlay rendering on graphics boards with hardware overlay
 * planes, for example NVIDIA Quadro boards. Open Inventor creates a 8 bit indexed overlay 
 * context when this option is enabled in the graphics hardware configuration of your system. 
 * To render a scene graph in the overlay context just call the setOverlaySceneGraph function.
 *
 * For Linux based systems you must modify the section display of your Xorg.conf.
 * Add the following lines and restart your X server:
 *
 * Option "UBB" "1"
 * Option "CIOverlay" "1"
 *
 * For Microsoft Windows platforms just enable overlay support in the control panel for your 
 * graphics board.
 *
 * @SEE_ALSO
 *    SoWinGLWidget,
 *    SoWinComponent,
 *    SoWinViewer,
 *    SoSceneManager,
 *    SoBoxHighlightRenderAction,
 *    SoLineHighlightRenderAction
 *
 *
 */

class INVENTORW_API SoWinRenderArea : public SoWinGLWidget
{
 public:

  /**
   * Constructor which is passed arguments which tell it whether to register the
   * mouse and keyboard devices by default (SoWinMouse and SoWinKeyboard). [_WIN32]
   * Note: On Windows, the constructor will not create a new top level window -- you
   * must pass a valid window handle for the @B parent @b parameter and pass TRUE
   * for @B buildInsideParent @b.
   */
  SoWinRenderArea( SoWidget parent = NULL,
                   const char* name = NULL,
                   SbBool buildInsideParent = TRUE,
                   SbBool getMouseInput = TRUE,
                   SbBool getKeyboardInput = TRUE );
  /**
   * Destructor.
   */
  ~SoWinRenderArea();

  /**
   * Sets the scene graph to be rendered in this component's window.
   * [OIVJAVA-WRAPPER CUSTOM_CODE]
   * [OIVNET-WRAPPER-ARG ALLOC_REF{Normal}]
   */
  virtual void setSceneGraph( SoNode *newScene );

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
  SoNode* getOverlaySceneGraph() { return m_guiRenderArea->getOverlaySceneGraph(); }

  /**
   * Registers interest in devices. When a device is registered, messages
   * from that device will be processed by the render area, and passed into the scene
   * graph. Messages from unregistered devices will be ignored.
   */
  void registerDevice( SoWinDevice* d );
  /**
   * Unregisters interest in devices. When a device is registered, messages
   * from that device will be processed by the render area, and passed into the scene
   * graph. Messages from unregistered devices will be ignored.
   */
  void unregisterDevice( SoWinDevice* d );

  /**
   * Sets the background color for this window. Default is black (0,0,0). @BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR (3 floats representing RGB values of the colors separated by space).
   */
  void setBackgroundColor( const SbColor& c );

  /**
   * Gets the background color for this window.
   */
  const SbColor& getBackgroundColor() const { return m_guiRenderArea->getBackgroundColor(); }

  /**
   * Sets the window background color when in color index mode. Default is black
   * (index 0)).
   */
  void setBackgroundIndex( int index ) { m_guiRenderArea->setBackgroundIndex( index ); }

  /**
   * Gets the window background color when in color index mode.
   */
  int getBackgroundIndex() const { return m_guiRenderArea->getBackgroundIndex(); }

  /**
   * Sets the overlay window background color index. Default is 0 (clear
   * color).
   */
  void setOverlayBackgroundIndex( int index ) { m_guiRenderArea->setOverlayBackgroundIndex( index ); }

  /**
   * Gets the overlay window background color index.
   */
  int getOverlayBackgroundIndex() const { return m_guiRenderArea->getOverlayBackgroundIndex(); }

  /**
   * Sets the colors to use when displaying in color index mode. This will load the
   * color map with the given colors at the starting index.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY]
   */
  void setColorMap( int startIndex, int num, const SbColor* colors );

  /**
   * Sets the colors to use for overlay bit planes. This will load the color map with
   * the given colors at the starting index.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY]
   */
  void setOverlayColorMap( int startIndex, int num, const SbColor* colors );

  /**
   * Sets viewport region to use for rendering.
   */
  void setViewportRegion( const SbViewportRegion& newRegion )
  { m_guiRenderArea->setViewportRegion( newRegion ); }

  /**
   * Gets current viewport region to use for rendering.
   */
  const SbViewportRegion &getViewportRegion() const
    { return m_guiRenderArea->getViewportRegion(); }

  /**
   * Sets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  void setTransparencyType( SoGLRenderAction::TransparencyType type );

  /**
   * Gets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  SoGLRenderAction::TransparencyType  getTransparencyType() const
    { return m_guiRenderArea->getTransparencyType(); }

  /**
   * Sets fast editing save policy to use when rendering. The default is DISABLE.
   * Valid values are DISABLE, EACH_FRAME, and WHEN_NEEDED. See SoSeparator.
   * 
   * If fastEditDelayedObjects is set to TRUE, delayed objects won't be redrawn
   * when editing the scene graph. It means that composition between delayed transparent objects
   * and fast edit scene graph won't be correct but redrawing may be much faster. Default is FALSE.
   */
  void setFastEditSavePolicy( SoGLRenderAction::FastEditSavePolicy policy,
                              SbBool fastEditDelayedObjects = FALSE);

  /**
   * Returns fast editing save policy used when rendering.
   */
  SoGLRenderAction::FastEditSavePolicy  getFastEditSavePolicy() const
    { return m_guiRenderArea->getFastEditSavePolicy(); }

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
   *
   * Caution: Multipass antialiasing is quite slow. We recommend using
   * full-scene antialiasing, which is hardware accelerated on modern graphics hardware.
   * See SoWinGLWidget::setFullSceneAntialiasing().
   */
  void setAntialiasing( SbBool smoothing, int numPasses );

  /**
   * Gets the antialiasing for rendering. See setAntialiasing() for details.
   */
  void getAntialiasing( SbBool& smoothing, int& numPasses) const
    { m_guiRenderArea->getAntialiasing( smoothing, numPasses ); }

  /**
   * Enables/prevents window clearing from happening before a rendering starts (default
   * is clear TRUE). This can be useful to limit flickering when doing single
   * buffering and geometry covers the entire window (used in the material editor).
   * Also controls whether the depth buffer (sometimes called the Z buffer) is
   * cleared before rendering.
   */
  void setClearBeforeRender( SbBool trueOrFalse, SbBool zbTrueOrFalse = TRUE )
  { m_guiRenderArea->setClearBeforeRender( trueOrFalse, zbTrueOrFalse ); }

  /**
   * Queries whether the window will be cleared before rendering starts.
   */
  SbBool isClearBeforeRender() const { return m_guiRenderArea->isClearBeforeRender(); }

  /**
   * Queries whether the depth buffer (sometimes called the Z buffer) will be
   * cleared before rendering starts.
   */
  SbBool isClearZBufferBeforeRender() const { return m_guiRenderArea->isClearZBufferBeforeRender(); }

  /**
   * Enables/prevents overlay window clearing from happening before a rendering starts
   * (default is clear TRUE).
   */
  void setClearBeforeOverlayRender( SbBool trueOrFalse )
  { m_guiRenderArea->setClearBeforeOverlayRender( trueOrFalse ); }

  /**
   * Queries whether the overlay window will be cleared before rendering starts.
   */
  SbBool isClearBeforeOverlayRender() const { return m_guiRenderArea->isClearBeforeOverlayRender(); }

  /**
   * The render area will automatically redraw whenever something in the scene graph
   * changes. Passing FALSE will disable this feature.
   * NOTE: the render area will always
   * redraw in response to window system events (e.g. resize, exposure)
   * regardless of the setting of the auto redraw flag.
   */
  void setAutoRedraw( SbBool trueOrFalse );

  /**
   * Queries whether the render area will automatically redraw whenever something
   * in the scene graph changes.
   */
  SbBool isAutoRedraw() const { return m_guiRenderArea->isAutoRedraw(); }

  /**
   * Sets the priority of the redraw sensor.
   */
  void setRedrawPriority( unsigned long priority ) { m_guiRenderArea->setRedrawPriority(priority); }

  /**
   * Gets the priority of the redraw sensor.
   */
  unsigned long getRedrawPriority() const { return m_guiRenderArea->getRedrawPriority(); }

  /**
   * Gets the default priority number of the redraw sensor.
   */
  static unsigned long getDefaultRedrawPriority() { return SoSceneManager::getDefaultRedrawPriority(); }

  /**
   * Calling this forces the render area to be redrawn now. It is not necessary to
   * call this method if auto redraw is enabled (which is the default).
   */
  void render() { redraw(); }

  /**
   * Calling this forces the render area overlay planes to be redrawn now. It is not necessary to
   * call this method if auto redraw is enabled (which is the default).
   */
  void renderOverlay() { redrawOverlay(); }

  /**
   * Schedules a redraw to happen sometime soon (as opposed to immediately). This can
   * be used to compress multiple redraws.
   */
  void scheduleRedraw();

  /**
   * Schedules a redraw of the overlay planes to happen sometime soon (as opposed to immediately). This can
   * be used to compress multiple redraws.
   */
  void scheduleOverlayRedraw();

  /**
   * Call this convenience method to have this render area redraw whenever the
   * selection list changes in the passed node. This is useful if using a highlight
   * render action like the SoBoxHighlightRenderAction to correctly render whenever
   * the selection changes. Pass NULL to turn this off.
   *
   * This call increases the ref counter of the given SoSelection node, it will be
   * automatically decreased when the selection node is replaced by another one, or if
   * it is turned off.
   */
  void redrawOnSelectionChange( SoSelection* s );

  /**
   * Call this convenience method to have this render area overlay planes redraw whenever the
   * selection list changes in the passed node. This is useful if using a highlight
   * render action like the SoBoxHighlightRenderAction to correctly render whenever
   * the selection changes. Pass NULL to turn this off.
   *
   * This call increases the ref counter of the given SoSelection node, it will be
   * automatically decreased when the selection node is replaced by another one, or if
   * it is turned off.
   */
  void redrawOverlayOnSelectionChange( SoSelection* s );

  /**
   * Windows messages which occur in the render area window are either directly
   * handled by the viewer (when this is really a viewer) or automatically translated
   * to SoEvents, then passed into the scene graph (via the SoHandleEventAction) so
   * that live scene graph objects can handle the message (when viewers are not in
   * viewing mode). This method allows the application to register a \oivnetdoc delegate \else callback \endoivnetdoc for
   * handling messages that occur in the window, instead of sending them to the
   * viewers or down the graph. The \oivnetdoc delegate \else callback \endoivnetdoc is passed the Windows message, and
   * should return TRUE if it handled the message. If the \oivnetdoc delegate \else callback \endoivnetdoc returns FALSE,
   * then the message will be handled by the render area.
   *
   * The following Windows events are sent to setEventCallback:
   * - WM_LBUTTONDOWN@BR
   * - WM_MBUTTONDOWN@BR
   * - WM_RBUTTONDOWN@BR
   * - WM_LBUTTONUP@BR
   * - WM_MBUTTONUP@BR
   * - WM_RBUTTONUP@BR
   * - WM_MOUSEMOVE@BR
   * - WM_MOUSEWHEEL@BR
   * - WM_LBUTTONDBLCLK@BR
   * - WM_MBUTTONDBLCLK@BR
   * - WM_RBUTTONDBLCLK@BR
   * - WM_SETFOCUS@BR
   * - WM_KILLFOCUS@BR
   * - WM_COMMAND@BR
   * - WM_KEYDOWN@BR
   * - WM_SYSKEYDOWN@BR
   * - WM_KEYUP@BR
   * - WM_SYSKEYUP@BR
   * - WM_SIZE@BR
   * - WM_PAINT@BR
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setEventCallback( SoWinRenderAreaEventCB* fcn, void* userData = NULL )
    { appEventHandler = fcn; appEventHandlerData = userData; }

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
  SoSceneManager* getSceneManager() const { return m_guiRenderArea->getSceneManager(); }

  /**
   * Sets the overlay plane scene manager.
   *
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  void setOverlaySceneManager( SoSceneManager* sm ) { m_guiRenderArea->setOverlaySceneManager( sm ); }

  /**
   * Gets the overlay plane scene manager.
   *
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  SoSceneManager* getOverlaySceneManager() const { return m_guiRenderArea->getOverlaySceneManager(); }

  /**
   * Sets the GL render action to use. This is used for example to set selection
   * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
   * classes.
   * Note: Properties of the previous render action, for example transparency type,
   * are not automatically copied to the new render action.  The application must
   * explicitly set the desired properties of the new render action.
   */
  void setGLRenderAction( SoGLRenderAction* ra );

  /**
   * Gets the GL render action to use. This is used to set selection
   * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
   * classes.
   */
  SoGLRenderAction* getGLRenderAction() const { return m_guiRenderArea->getGLRenderAction(); }

  /**
   * Sets the GL render action for the overlay window.
   */
  void setOverlayGLRenderAction( SoGLRenderAction* ra )
  { m_guiRenderArea->setOverlayGLRenderAction( ra ); }

  /**
   * Gets the GL render action for the overlay window.
   */
  SoGLRenderAction* getOverlayGLRenderAction() const
  { return m_guiRenderArea->getOverlayGLRenderAction(); }


  /**
   * Returns the information needed to make OpenGL render contexts
   * share OpenGL objects, for example, display lists and texture objects.
   * Open Inventor automatically shares between on-screen contexts. This
   * method is useful to share objects with an off-screen context.
   * See SoOffscreenRenderer.
   */
  const SbGLShareContext getShareContext();

  /**
   * Specifies a function to be called after the Open Inventor render
   * traversal and immediately before the OpenGL buffer swap.
   *
   * Generally the application should not modify Open Inventor state in these
   * callbacks, but they can be useful for special effects using OpenGL calls.
   *
   * When the \oivnetdoc delegate \else callback \endoivnetdoc function is called, Open Inventor has completed normal
   * rendering (including delayed transparent objects, multi-pass, etc),
   * but no "end of frame" calls (glFlush, glFinish, SwapBuffers...) have
   * been made.  The function should return TRUE if "end of frame" handling
   * has been done by the application (Open Inventor will do nothing in this
   * case).  If FALSE is returned, Open Inventor will do its normal end of
   * frame calls (normally calling SwapBuffers).
   */
  void setPostRenderCallback( SoWinRenderAreaRenderCB* fcn, void* userData = NULL )
    { appPostRenderCB = fcn; appPostRenderData = userData; }

  /**
   * Gets the post-render callback function and data.
   * Returns NULL if no callback has been specified by the application.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoWinRenderAreaRenderCB* getPostRenderCallback( const void* &userData ) const
    { userData = appPostRenderData; return appPostRenderCB; }

  /**
   * Enables/disables floating point rendering using 16- or 32-bit components.
   * If TRUE, Open Inventor will automatically render to an offscreen floating point buffer,
   * and copy the resulting image to the screen.
   *
   * To determine if floating point rendering was successfully enabled,
   * use #getFloatingColorBuffer, below.
   *
   * Using floating point rendering can improve image quality, particularly when
   * many objects are being blended, for example, in volume rendering.
   * This is a convenience method as you could accomplish the same results
   * setting up a graphic template.
   */
  void setFloatingColorBuffer( SbBool enable,
                               FloatColorBufferSize size = FLOAT_16_COLOR_BUFFER );

  /**
   * Returns TRUE if floating point rendering is used and its precision.
   */
  void getFloatingColorBuffer( SbBool& enable, FloatColorBufferSize& size );

  /**
   * Returns TRUE if floating point rendering is available.
   */
  static SbBool isFloatingColorBufferSupported();

  /** 
   * Sends the event to be processed by the renderArea.
   */
  void sendEvent( XAnyEvent* anEvent );

  /** 
   * Sets the recorder used for MPEG encoding. Default is none.
   *
   * @param recorder the recorder to be used.
   */
  virtual void setMPEGRecorder( SoMPEGRenderer* recorder )
  { m_guiRenderArea->setMPEGRecorder( recorder ); }

  /** 
   * Returns the recorder used for MPEG encoding.
   */
  virtual SoMPEGRenderer* getMPEGRecorder() const
  { return m_guiRenderArea->getMPEGRecorder(); }

  SoEXTENDER public:
  SoWinRenderArea( SoWidget parent,
                   const char* name, 
                   SbBool buildInsideParent, 
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SoGuiAlgoViewers* guiAlgos );

  //Equivalent to the SoExtender constructor
  SoWinRenderArea( SoWidget parent,
                   const char* name, 
                   SbBool buildInsideParent, 
                   SbBool getMouseInput,
                   SbBool getKeyboardInput, 
                   SbBool buildNow,
                   SbBool sync,
                   SoGuiAlgoViewers* guiAlgos );

  //Equivalent to the protected constructor
  SoWinRenderArea( SoWidget parent,
                   const char* name, 
                   SbBool buildInsideParent, 
                   SbBool getMouseInput,
                   SbBool getKeyboardInput, 
                   SbBool buildNow,
                   SoGuiAlgoViewers* guiAlgos );

 SoINTERNAL public:

  SoGuiRenderArea* getGuiRenderArea() const;

  void setStereoMode( SoCamera::StereoMode stMode );
  void setStereoElement();

  virtual void setDoubleBuffer( SbBool db );

  virtual SbBool isInteractive() const;

  SoWinRenderArea( SoWidget parent,
                   const char* name,
                   SbBool buildInsideParent,
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SbBool buildNow,
                   SbBool sync );

  // Retro compatibility only.
  // These members shouldn't be used directly, instead call their accessors
  float stereoBalance, stereoOffset;
  SbBool stereoAbsoluteAdjustments;
  SoCamera::StereoMode stereoMode;
  SbBool stereoReversed;

 protected:

  //
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinRenderArea::buildWidget()
  // when they are ready for it to be built.

  SoWinRenderArea( SoWidget parent,
                   const char* name,
                   SbBool buildInsideParent,
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SbBool buildNow );

  //Constructors provided to avoid multiple instance of implementation objects
  //Equivalent to the public constructor
  SoWinRenderArea( SoWidget parent,
                   const char* name,
                   SbBool buildInsideParent,
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SoGuiRenderArea* guiRenderArea );

  //Equivalent to the SoExtender constructor
  SoWinRenderArea( SoWidget parent,
                   const char* name,
                   SbBool buildInsideParent,
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SbBool buildNow,
                   SbBool sync,
                   SoGuiRenderArea* guiRenderArea );

  //Equivalent to the protected constructor
  SoWinRenderArea( SoWidget parent,
                   const char* name,
                   SbBool buildInsideParent,
                   SbBool getMouseInput,
                   SbBool getKeyboardInput,
                   SbBool buildNow,
                   SoGuiRenderArea* guiRenderArea );

  // redraw() calls actualRedraw(), followed by swapbuffers if necessary.
  // actualRedraw will have the scene manager render the scene. Rendering
  // is broken up into two routines like this so that subclasses can
  // redefine or simply add to rendering (in actualRedraw) without having
  // to worry about being visible, seting up the window or
  // single/double buffer swapping.
  //
  virtual void redraw();
  virtual void actualRedraw();
  virtual void redrawOverlay();
  virtual void actualOverlayRedraw();

  //
  // Redefine these to do Inventor-specific things
  //
  virtual void processEvent( XAnyEvent* anyevent );
  virtual void initGraphic();
  virtual void initOverlayGraphic();
  virtual void sizeChanged( const SbVec2s& );
  virtual void posChanged( const SbVec2i32&, const SbVec2i32& );
  virtual void widgetChanged( SoWidget );

  SoWidget buildWidget( SoWidget parent );

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // subclasses have access to the device list for event processing
  SbPList* m_deviceList;    // list of devices

  // application event callback variables
  SoWinRenderAreaEventCB *appEventHandler;
  void                   *appEventHandlerData;
  // invoke the application event callback - returns what the app cb returns
  SbBool invokeAppCB( XAnyEvent* anyevent );
  void processInventorEvent( XAnyEvent* anyevent );

  // application pre/post render callback variables
  SoWinRenderAreaRenderCB *appPostRenderCB;
  void                    *appPostRenderData;

 private:
  // Floating point rendering
  SbBool m_isFloatingPointRendering;
  FloatColorBufferSize m_floatingPointRenderingPrecision;

#if defined(sun) || defined(__linux__)
  XColor* m_mapColors, *m_overlayMapColors; // saved colors
  int m_mapColorNum, m_overlayMapColorNum; // number of saved colors
#endif

  SoWinMouse* m_mouseDevice;
  SoWinKeyboard* m_keybdDevice;
  void reinstallDevices( SoWidget newWidget );

  static void selectionChangeCB( void* userData, SoSelection* s );
  static void overlaySelectionChangeCB( void* userData, SoSelection* s );
  SoWidget m_deviceWidget;

  // static callbacks
  SbBool m_firstEvent;

 protected:
  SbBool m_runOnce;
  static void windowEventCB( SoWidget w, SoWinRenderArea* wra, XAnyEvent* e, Boolean* b );
 private:
  static void renderCB( void* v, SoSceneManager* sm );
  static void renderOverlayCB( void* v, SoSceneManager* sm );

  static void visibilityChangeCB( void* pt, SbBool visible );

  // this is called by constructors
  void constructorCommon( SbBool getMouseInput,
                          SbBool getKeyboardInput,
                          SbBool buildNow );

  // this is called by constructorCommon
  void constructorCommon2( SbBool getMouseInput,
                          SbBool getKeyboardInput,
                          SbBool buildNow );

  void activate();
  void deactivate();

  int inRedraw;
  int inOverlayRedraw;

  SoGuiRenderArea* m_guiRenderArea; // Implementation class for SoXxRendeArea

  bool m_firstStdRedraw;
  bool m_firstConnectedRedraw;
  SoTimerSensor* m_viewerUpdaterSensor;
  static void viewerUpdaterCB( void*, SoSensor* );
  void updateFirstFrame();

};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WIN_RENDER_AREA_H_ */


