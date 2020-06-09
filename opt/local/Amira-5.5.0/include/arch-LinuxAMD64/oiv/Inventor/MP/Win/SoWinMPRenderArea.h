/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_MP_RENDER_AREA_H_
#define _SO_WIN_MP_RENDER_AREA_H_

#if defined(_WIN32)
#  include <Inventor/Win/SoWinBeginStrict.h>
#  include <windows.h>
#  ifdef _SO_QT_
#    include <wingdi.h>
#  else
#    include <Inventor/Win/SoWinDef.h>
#  endif
#else
#  include <X11/Intrinsic.h>
#  include <X11/Xlib.h>
#endif // _WIN32

#include <Inventor/SbColor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/MP/Win/SoWinMPGLWidget.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/threads/SbThreadBarrier.h>
#include <Inventor/threads/SbThread.h>

#include <Inventor/nodes/SoCamera.h> 
#include <Inventor/components/stereo/SoStereoViewer.h>
#include <Inventor/sensors/SoTimerSensor.h>

class   SoHandleEventAction;
class   SoWinDevice;
class   SoNode;
class   SoWinMouse;
class   SoWinKeyboard;
class   SoSelection; 

// callback function prototype
typedef SbBool SoWinMPRenderAreaEventCB(void *userData, XAnyEvent *anyevent);


class SoWinMPRenderArea;
// callback function prototype for thread initialization
typedef void SoWinMPRenderAreaThreadInitCB(void * userData, SoWinMPRenderArea *ra);

// callback function prototype for pre/post thread rendering
typedef void SoWinMPRenderAreaThreadRenderCB(void * userData, SoWinMPRenderArea *ra);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMPRenderArea
//
//  Class to do Inventor rendering in a GLX Motif widget.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @SCVEXT MultiPipe component for rendering Open Inventor scene graphs.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   This is the MultiPipe version of SoWinRenderArea.
 *
 * @B NOTE: @b Since Open Inventor version 8.0 we recommend using the ScaleViz
 * extension, rather than SoWinMP classes, for multi-GPU rendering (multiple 
 * graphics boards in the same machine).  Using ScaleViz you can continue to
 * use the standard render area or view classes, and conveniently adapt to the
 * hardware configuration using a ScaleViz configuration file.
 *
 * General:
 *
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
 * Overlay rendering:
 * 
 * This class supports overlay rendering on graphics boards with hardware overlay
 * planes, for example NVIDIA Quadro boards. Open Inventor creates a 8 bit indexed overlay 
 * context when this option is enabled in the graphics hardware configuration of your system. 
 * To render a scene graph in the overlay context just call the setOverlaySceneGraph function.
 *
 * For Linux based systems you must modify the "display" section of your Xorg.conf.
 * Add the following lines and restart your X server:
 *
 * Option "UBB" "1"
 * Option "CIOverlay" "1"
 *
 * For Microsoft Windows platforms just enable overlay support in the control panel for your 
 * graphics board.
 *
 * 
 */ 

class INVENTORW_API SoWinMPRenderArea : public SoWinMPGLWidget, public SoStereoViewer {
 public:
  /**
   * Constructor to build one (default) or more subwindows. 
   * Constructor is passed arguments 
   * which tell it whether to register the
   * mouse and keyboard devices by default (SoWinMouse and SoWinKeyboard). [WIN32]
   * Note: On Windows, the constructor will not create a new top level window -- you
   * must pass a valid window handle for the @B parent @b parameter and pass TRUE
   * for @B buildInsideParent @b.
   */
  SoWinMPRenderArea(SoWidget parent = NULL,
                    const char *name = NULL, 
                    SbBool buildInsideParent = TRUE, 
                    SbBool getMouseInput = TRUE,
                    SbBool getKeyboardInput = TRUE);

  /**
   * Destructor.
   */
  ~SoWinMPRenderArea();
    
  /**
   * Sets the scene graph to be rendered in this component's window.
   */
  virtual void            setSceneGraph(SoNode *newScene);
  /**
   * Gets the scene graph to be rendered in this component's window.
   */
  virtual SoNode *        getSceneGraph();
    
  /**
   * Sets the scene graph to be rendered in the overlay plane. NOTE: This feature
   * requires a graphics board that supports an overlay plane.
   */
  void                    setOverlaySceneGraph(SoNode *newScene);
  /**
   * Gets the scene graph to be rendered in the overlay plane. NOTE: This feature
   * requires a graphics board that supports an overlay plane.
   */
  SoNode *                getOverlaySceneGraph()
    { return overlaySceneMgr->getSceneGraph();}
    
  /**
   * Registers interest in devices. When a device is registered, messages
   * from that device will be processed by the render area, and passed into the scene
   * graph. Messages from unregistered devices will be ignored.
   */
  void                    registerDevice(SoWinDevice *d);
  /**
   * Unregisters interest in devices. When a device is registered, messages
   * from that device will be processed by the render area, and passed into the scene
   * graph. Messages from unregistered devices will be ignored.
   */
  void                    unregisterDevice(SoWinDevice *d);
    
  /**
   * Sets the background color for this window. Default is black (0,0,0).
   *
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR. Specify three floats (R, G, B) in the range 0. to 1.,  
   * separated by spaces.
   */
  void                    setBackgroundColor(const SbColor &c)
    { sceneMgr->setBackgroundColor(c); }
  /**
   * Gets the background color for this window.
   */
  const SbColor &         getBackgroundColor() const
    { return sceneMgr->getBackgroundColor(); }
    
  /**
   * Sets the window background color when in color index mode. Default is black
   * (index 0)).
   */
  void                    setBackgroundIndex(int index)
    { sceneMgr->setBackgroundIndex(index); }
  /**
   * Gets the window background color when in color index mode. 
   */
  int                     getBackgroundIndex() const
    { return sceneMgr->getBackgroundIndex(); }
    
  /**
   * Sets the overlay window background color index. Default is 0 (clear
   * color).
   */
  void                    setOverlayBackgroundIndex(int index)
    { overlaySceneMgr->setBackgroundIndex(index); }
  /**
   * Gets the overlay window background color index. 
   */
  int                     getOverlayBackgroundIndex() const
    { return overlaySceneMgr->getBackgroundIndex(); }
    
  /**
   * Sets the colors to use when displaying in color index mode. This will load the
   * color map with the given colors at the starting index.
   */
  void        setColorMap(int startIndex, int num, const SbColor *colors);
    
  /**
   * Sets the colors to use for overlay bit planes. This will load the color map with
   * the given colors at the starting index.
   */
  void        setOverlayColorMap(int startIndex, int num, const SbColor *colors);
    
  // methods to reach the subWidgets viewport regions
  /**
   * Sets viewport region of the specified subwindow.
   */
  void    setViewportRegion(const SbViewportRegion &newRegion, int id) 
    { sceneMgr->getGLRenderAction(id)->setViewportRegion(newRegion); }
  /**
   * Gets current viewport region of the specified subwindow.
   */
  const SbViewportRegion &getViewportRegion(int id) const
    { return sceneMgr->getGLRenderAction(id)->getViewportRegion(); }
  /**
   * Sets viewport region to use for rendering.
   */
  void    setViewportRegion(const SbViewportRegion &newRegion);
  /**
   * Gets current viewport region to use for rendering.
   */
  const SbViewportRegion &getViewportRegion() const
    { return sceneMgr->getGLRenderAction(0)->getLogicalViewportRegion(); }
    
  /**
   * Sets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  void        setTransparencyType(SoGLRenderAction::TransparencyType type);
  /**
   * Gets the quality level for rendering transparent objects. See
   * SoGLRenderAction for possible transparency types.
   */
  SoGLRenderAction::TransparencyType  getTransparencyType() const
    { return sceneMgr->getGLRenderAction()->getTransparencyType(); }

    
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
  void            setAntialiasing(SbBool smoothing, int numPasses);
  /**
   * Gets the antialiasing for rendering. See setAntialiasing() for details.
   */
  void            getAntialiasing(SbBool &smoothing, int &numPasses) const
    { sceneMgr->getAntialiasing(smoothing, numPasses); }
    
  /**
   * Enables/prevents window clearing from happening before a rendering starts (default
   * is clear TRUE). This can be useful to limit flickering when doing single
   * buffering and geometry covers the entire window (used in the material editor).
   * Also controls whether the depth buffer (sometimes called the Z buffer) is
   * cleared before rendering.
   */
  void                    setClearBeforeRender(SbBool trueOrFalse,
                                               SbBool zbTrueOrFalse = TRUE)
    { clearFirst = trueOrFalse; 
    clearZBufferFirst = zbTrueOrFalse; }
  /**
   * Queries whether the window will be cleared before rendering starts.
   */
  SbBool                  isClearBeforeRender() const
    { return clearFirst; }
  /**
   * Queries whether the depth buffer (sometimes called the Z buffer) will be 
   * cleared before rendering starts.
   */
  SbBool                  isClearZBufferBeforeRender() const
    { return clearZBufferFirst; }
  /**
   * Enables/prevents overlay window clearing from happening before a rendering starts
   * (default is clear TRUE).
   */
  void                    setClearBeforeOverlayRender(SbBool trueOrFalse)
    { clearOverlayFirst = trueOrFalse; }
  /**
   * Queries whether the overlay window will be cleared before rendering starts.
   */
  SbBool                  isClearBeforeOverlayRender() const
    { return clearOverlayFirst; }
    
  /**
   * The render area will automatically redraw whenever something in the scene graph
   * changes. Passing FALSE will disable this feature.
   * NOTE: the render area will always
   * redraw in response to window system events (e.g. resize, exposure)
   * regardless of the setting of the auto redraw flag.
   */
  void                    setAutoRedraw(SbBool trueOrFalse);
  /**
   * Queries whether the render area will automatically redraw whenever something
   * in the scene graph changes. 
   */
  SbBool                  isAutoRedraw() const { return autoRedraw; }
    
  /**
   * Sets the priority of the redraw sensor.
   */
  void                setRedrawPriority(unsigned long priority)
    { sceneMgr->setRedrawPriority(priority);
    overlaySceneMgr->setRedrawPriority(priority); }
  /**
   * Gets the priority of the redraw sensor.
   */
  unsigned long       getRedrawPriority() const
    { return sceneMgr->getRedrawPriority(); }
  /**
   * Gets the default priority number of the redraw sensor.
   */
  static unsigned long getDefaultRedrawPriority()
    { return SoSceneManager::getDefaultRedrawPriority(); }

  /**
   * Calling this forces the render area to be redrawn now. It is not necessary to
   * call this method if auto redraw is enabled (which is the default).
   */
  void                    render()            { redraw(); }
  /**
   * Calling this forces the render area overlay planes to be redrawn now. It is not necessary to
   * call this method if auto redraw is enabled (which is the default).
   */
  void                    renderOverlay()     { redrawOverlay(); }
    
  /**
   * Schedules a redraw to happen sometime soon (as opposed to immediately). This can
   * be used to compress multiple redraws.
   */
  void                    scheduleRedraw();
  /**
   * Schedules a redraw of the overlay planes to happen sometime soon (as opposed to immediately). This can
   * be used to compress multiple redraws.
   */
  void                    scheduleOverlayRedraw();
    
  /**
   * Call this convenience method to have this render area redraw whenever the
   * selection list changes in the passed node. This is useful if using a highlight
   * render action like the SoBoxHighlightRenderAction to correctly render whenever
   * the selection changes. Pass NULL to turn this off.
   */
  void                    redrawOnSelectionChange(SoSelection *s);
  /**
   * Call this convenience method to have this render area overlay planes redraw whenever the
   * selection list changes in the passed node. This is useful if using a highlight
   * render action like the SoBoxHighlightRenderAction to correctly render whenever
   * the selection changes. Pass NULL to turn this off.
   */
  void                    redrawOverlayOnSelectionChange(SoSelection *s);
    
  /**
   * Windows messages which occur in the render area window are either directly
   * handled by the viewer (when this is really a viewer) or automatically translated
   * to SoEvents, then passed into the scene graph (via the SoHandleEventAction) so
   * that live scene graph objects can handle the message (when viewers are not in
   * viewing mode). This method allows the application to register a callback for
   * handling messages that occur in the window, instead of sending them to the
   * viewers or down the graph. The callback is passed the Windows message, and
   * should return TRUE if it handled the message. If the callback returns FALSE,
   * then the message will be handled by the render area.
   */
  void            setEventCallback(
                                   SoWinMPRenderAreaEventCB *fcn, 
                                   void *userData = NULL)
    { appEventHandler = fcn; appEventHandlerData = userData; }
    
  /**
   * Sets the normal scene manager.
   * 
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  void                setSceneManager(SoSceneManager *sm);
  /**
   * Gets the normal scene manager.
   * 
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  SoSceneManager *    getSceneManager() const { return sceneMgr; }
  /**
   * Sets the overlay plane scene manager.
   * 
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  void                setOverlaySceneManager(SoSceneManager *sm) { overlaySceneMgr = sm; }
  /**
   * Gets the overlay plane scene manager.
   * 
   * Note: For convenience most of the SoSceneManager methods have already been added
   * to this class.
   */
  SoSceneManager *    getOverlaySceneManager() const { return overlaySceneMgr; }
    
  /**
   * Sets the GL render action to use. This is used to set selection
   * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
   * classes.
   */
  void                setGLRenderAction(SoGLRenderAction *ra) 
    { 
      sizeChanged(SbVec2s(166,363));
      sceneMgr->setGLRenderAction(ra); 
    }
  /**
   * Gets the GL render action to use. This is used to set selection
   * highlighting with the SoBoxHighlightRenderAction and SoLineHighlightRenderAction
   * classes.
   */
  SoGLRenderAction    *getGLRenderAction() const
    { return sceneMgr->getGLRenderAction(); }
  /**
   * Sets the GL render action to use for the specified subwindow. This is used
   * to set selection highlighting with the SoBoxHighlightRenderAction and
   * SoLineHighlightRenderAction classes.
   */
  void            setGLRenderAction(SoGLRenderAction *ra, int i)
    {       sceneMgr->setGLRenderAction(ra, i); }
  /**
   * Gets the GL render action to use for the specified subwindow. 
   */
  SoGLRenderAction    *getGLRenderAction(int i) const
    { return sceneMgr->getGLRenderAction(i); }

  /**
   * Sets the GL render action for the overlay window.
   */
  void                setOverlayGLRenderAction(SoGLRenderAction *ra) 
    { overlaySceneMgr->setGLRenderAction(ra); }
  /**
   * Gets the GL render action for the overlay window.
   */
  SoGLRenderAction    *getOverlayGLRenderAction() const
    { return overlaySceneMgr->getGLRenderAction(); }


  /**
   * gets the timer sensor that reads the tracking data
   */
  SoTimerSensor * getTrackerSensor()
    { return trackerSensor; }
          
  /**
   * sets the inter-eye-distance. This parameter is used for stereo
   * when the headtracking is enabled
   */
  void setInterEyeDistance(float value)
    { interEyeDistance = value;}

  /**
   * gets the inter-eye-distance
   */
  float getInterEyeDistance(void)
    { return interEyeDistance;}

  // Flag to switch on/off the z-buffer
  int changeZbuffer;

  /**
   * Sets the stereo offset. See setStereoViewing() for additional info.
   */
  void            setStereoOffset(float dist) { stereoOffset = dist; scheduleRedraw() ;}
  /**
   * Returns the stereo offset. See setStereoViewing() for additional info.
   */
  float           getStereoOffset()   { return stereoOffset; }

 protected:
  
  //
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinMPRenderArea::buildWidget()
  // when they are ready for it to be built.

  SoWinMPRenderArea(SoWidget parent,
                    const char *name, 
                    SbBool buildInsideParent, 
                    SbBool getMouseInput,
                    SbBool getKeyboardInput, 
                    SbBool buildNow);
        
  //
  // redraw() calls actualRedraw(), followed by swapbuffers if necessary.
  // actualRedraw will have the scene manager render the scene. Rendering
  // is broken up into two routines like this so that subclasses can
  // redefine or simply add to rendering (in actualRedraw) without having
  // to worry about being visible, seting up the window or 
  // single/double buffer swapping.
  //
  void partialRedraw(int id);
  void partialRedrawOverlay(int id);

  void swapBuffers(int); 

  // drawing functions for the normal layer
  virtual void    redraw();
  virtual void        prepareRedraw();
  virtual void        actualRedraw();
  virtual void        endRedraw();
  // drawing functions for the overlay layer
  virtual void        redrawOverlay();
  virtual void        prepareOverlayRedraw();
  virtual void        actualOverlayRedraw();
  virtual void        endOverlayRedraw();

  //
  // Redefine these to do Inventor-specific things
  //
  virtual void        processEvent(XAnyEvent *anyevent);
  virtual void        initGraphic();
  virtual void        initOverlayGraphic();
  virtual void        sizeChanged(const SbVec2s &newSize);
  virtual void        widgetChanged(SoWidget);
        
  virtual void    initViewportRegion(int);


  SoWidget              buildWidget(SoWidget parent);
    
  // redefine these
  virtual SbString   getDefaultWidgetName() const;
  virtual SbString   getDefaultTitle() const;
  virtual SbString   getDefaultIconTitle() const;
    
  // subclasses have access to the device list for event processing
  SbPList             *deviceList;    // list of devices
    
  // application event callback variables
  SoWinMPRenderAreaEventCB *appEventHandler;
  void                   *appEventHandlerData;
  // invoke the application event callback - returns what the app cb returns
  SbBool              invokeAppCB(XAnyEvent *anyevent);
  
  // hidden lines draw style 
  void setDepthRange(float,float);
  float zNear;
  float zFar;
  void changeDepthRange(void);
  SbBool drawHiddenLineMode;
  void setHiddenLineSwap(SbBool);
  SbBool hiddenLineSwap;

  // stereo adjustment (previously in SoXtMPViewer)
  SbBool  stereoAbsoluteAdjustments;
  float   stereoOffset;
  float   stereoBalance;
  SbBool   stereoNearFrac;
  SoCamera::StereoMode stereoMode;
  float interEyeDistance; // MP immersive only

 SoINTERNAL public:
  void setDoSwapBuffers(SbBool);
  SbBool doSwapBuffers(void);
  void setLeftView(SbBool);
  void setRightView(SbBool);
  SbBool isLeftViewRendering(void);
  SbBool isRightViewRendering(void);
    
  void setStereoMode(SoCamera::StereoMode stMode);

 private:

  void setModifyViewVolumeElementWall(int id,SoSceneManager * sceneManager);
  void setStereoElement(int);

  // stereo MP
  SbBool doSwap;
  SbBool doLeftViewRendering;
  SbBool doRightViewRendering;

  SbThreadBarrier *swapBarrier;
        
  SbThreadBarrier *synchroStartBarrier;
  SbThreadBarrier *synchroEndBarrier;

  SbThreadBarrier *synchroOverlayStartBarrier;
  SbThreadBarrier *synchroOverlayEndBarrier;

  typedef struct {
    SoWinMPRenderArea *p;
    int id ;
  } ThreadFuncStruct ;
  ThreadFuncStruct *threadStruct;

  // Normal
  static unsigned int WINAPI threadRoutRedraw(LPVOID _userData);
  SbThread        **threadHandle;
  // Overlay
  static unsigned int WINAPI threadRoutRedrawOverlay(LPVOID _userData);
  SbThread        **threadHandleOverlay;

  // flag indicating whether a render traversal is in
  // progress.
  SbBool          isRedrawing;
    
  // these make rendering/redrawing happen
  SoSceneManager      *sceneMgr;      // this manages rendering and events
  SoSceneManager      *overlaySceneMgr; // manages the overlay scene graph

  SbBool      clearFirst, clearOverlayFirst;  // call clear() before rendering
  SbBool      clearZBufferFirst;  // clear ZBuffer before rendering
  SbBool      autoRedraw;     // if TRUE, then we automatically redraw
  XColor      *mapColors, *overlayMapColors; // saved colors
  int         mapColorNum, overlayMapColorNum; // number of saved colors

  SoWinMouse          *mouseDevice;
  SoWinKeyboard       *keybdDevice;
  void                reinstallDevices(SoWidget newWidget);
    
  static void         selectionChangeCB(void *userData, SoSelection *s);
  static void         overlaySelectionChangeCB(void *userData, SoSelection *s);
  SoSelection         *selection, *overlaySelection;
  SoWidget              deviceWidget;


  // static callbacks
  SbBool              firstEvent; // used to init the action SoWindowElement
 protected:
  static void         windowEventCB(SoWidget, SoWinMPRenderArea *, XAnyEvent *, Boolean *);
 private:
  static void         renderCB(void *, SoSceneManager *);
  static void         renderOverlayCB(void *, SoSceneManager *);
    
  static void visibilityChangeCB(void *pt, SbBool visible);
  void        activate();             // connects the sensor
  void        deactivate();           // disconnects the sensor
    
  // this is called by both constructors
  void constructorCommon(
                         SbBool getMouseInput,
                         SbBool getKeyboardInput, 
                         SbBool buildNow);
  int inRedraw;
  int inOverlayRedraw;

  void setModifyViewVolume(int, SoSceneManager *);

  static SoCallbackList * threadInitCBList;
  static SoCallbackList * threadPreRenderCBList;
  static SoCallbackList * threadPostRenderCBList;

  SbBool stereoActive;
  SoTimerSensor * trackerSensor;

 public:
    
  static void addThreadInitCB(SoWinMPRenderAreaThreadInitCB * fcn, void *userData);
  static void removeThreadInitCB(SoWinMPRenderAreaThreadInitCB * fcn, void *userData);
        
  static void addThreadPreRenderCB(SoWinMPRenderAreaThreadRenderCB * fcn, void *userData);
  static void removeThreadPreRenderCB(SoWinMPRenderAreaThreadRenderCB * fcn, void *userData);
        
  static void addThreadPostRenderCB(SoWinMPRenderAreaThreadRenderCB * fcn, void *userData);
  static void removeThreadPostRenderCB(SoWinMPRenderAreaThreadRenderCB * fcn, void *userData);

  /*fkw stereo for MT/MP*/
  // Implementing methods from the pure virtual class from SoStereoViewer
  virtual SbBool isViewerDoubleBuffer();
  virtual void setStereoViewing(SbBool onOrOff);
  virtual SbBool isStereoViewing();
  virtual SoCamera * getViewerCamera();
  virtual void adjustClippingPlanes();
  virtual const SbVec2s& getSize();
  virtual const SbVec2s& getTopLeft() ;
  virtual const SbVec2s& getBottomRight() ;
  void setStereoViewType(SoBaseStereo * stereo);
  SoBaseStereo * getStereoViewType();
  void reverseStereoView(SbBool reverse);
  SbBool isStereoViewReversed();
  virtual void setStereoAbsoluteAdjustments(SbBool absolute);
  virtual SbBool isStereoAbsoluteAdjustments() const {return stereoAbsoluteAdjustments;}
  virtual void setStereoBalance(float balance, SbBool nearFrac = false);
  virtual float getStereoBalance();
  virtual SbBool isStereoBalanceNearFrac();
  virtual void setStereoActive(SbBool activate) ;
  virtual SbBool isStereoActive() ;
  void setViewport(short left, short bottom, short width, short height) ;
  void getViewport(short &left, short &bottom, short &width, short &height) ;
  void * getViewer(void);
  virtual void actualRendering() {} // temporary, do nothing.
  HDC getCurrentDC() {return NULL;} // temporary, do nothing.

 protected:
  SoBaseStereo * stereoViewType;

};

#if defined(_WIN32)
#include <Inventor/Win/SoWinEndStrict.h>
#endif // _WIN32

#endif /* _SO_WIN_RENDER_AREA_H_ */


