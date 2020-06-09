/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Olivier Fedkiw (MMM yyyy)
**=======================================================================*/
#ifndef _SB_CONFIG_H
#define _SB_CONFIG_H

#include <Inventor/MP/Xt/SbPipe.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SbBox.h>

#include <Inventor/MP/SoTrackdAPI.h>

#if !defined(_WIN32)
#  include <X11/Xlib.h>
#endif

#ifndef HIDDEN_FROM_DOC
// structure used to get information from configuration file
// It is used as a chained list. Each time a pipe specification
// is found, a new structure pipe is added to the list.
// Once finished, this structure is used to initialize SbPipe **.
  
typedef struct pipe_tmp {
  int id;
  char * display_name;
  char * view;
  char * size;
  char * position;
  char * viewport;
  float edgeBlending_R;
  float edgeBlending_L;
  float edgeBlending_T;
  float edgeBlending_B;
  struct pipe_tmp * next;       
} pipe_t;

typedef struct {
  int nbPipe;
  pipe_t * first;
} cfg_t;

#endif // HIDDEN_FROM_DOC

//@tbr
/**
 * @SCVEXT Stores the configuration of the display system and the MultiPipe extension. 
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 * 
 *   Each MPGLWidget creates an SbConfig. 
 *   SbConfig reads the MultiPipe configuration file and stores all the
 *   information about the physical configuration of the display system: window
 *   information, tracking information, and behavioral
 *   information.
 *
 * MultiPipe 2.0 uses a new configuration file format based on the
 * Open Inventor file format. The nodes used in MultiPipe configuration
 * file are: SoFlatScreen, SoScreen, SoTracker, and SoMPConfig.
 *
 * Here is a sample configuration file that defines left and right "screens"
 * with a small amount of overlap. 
 * @code
 *   #Inventor V2.1 ascii
 *       
 *       Separator {
 *       
 *       SoFlatScreen {
 *          name "LEFT"
 *          display "0.1"
 *          view LEFT
 *          rightOverlap 0.01
 *       }
 *       SoFlatScreen {
 *          name "RIGHT"
 *          display "0.0"
 *          view RIGHT
 *          leftOverlap -0.01
 *       }
 *       }
 * @endcode
 *
 * @SEE_ALSO
 *    SoFlatScreen,
 *    SoMPConfig,
 *    SoScreen,
 *    SoTracker
 * 
 * 
 */ 

class INVENTORXT_API SbConfig {
  
  public :
    /**
     * Constructor.
     */
    SbConfig();
 
  /**
   * Destructor.
   */
  ~SbConfig();
  
  /** 
   * Returns the name of the MultiPipe configuration file.      
   */
  char * getConfigFile(void);

  /** 
   * Sets the name of the MultiPipe configuration file.
   */
  void setConfigFile(char * fileName);
  
  /** 
   * Reads the configuration file. 
   */
  int readConfigFile(void);
  
  /**
   * Gets the scene graph describing the MultiPipe configuration.
   */
  SoSeparator * getConfigTree(void);
  
  /** 
   * Gets the number of pipes (i.e., MultiPipe windows) used in the current configuration.
   */
  int getNbPipes(void);
  
  /** 
   * Gets the pipe object of specified index.
   */
  SbPipe * getPipe(int pipeID);

  /** 
   * Gets the pipe object of specified view.
   */
  SbPipe * getPipe(SbPipe::mpView view);
  
#if defined(_WIN32)
  /** 
   *
   */
  SbPipe * getPipe(HWND);
#else
  /** 
   * Gets the pipe object of specified window.
   */
  SbPipe * getPipe(Window win);

  /** 
   * Gets the pipe object of specified widget.
   */
  SbPipe * getPipe(SoWidget glw);

  /** 
   * Returns the first pipe in display.
   */
  SbPipe * getPipe(Display * dpy);
#endif

  /** 
   * Gets the index of a pipe
   */
  int getIndex(SbPipe * pipe);

  /** 
   * Prints the configuration.
   */
  void printInfo(void);

  /** 
   * It's necessary to have the application name in order 
   * to open several displays with Xt.
   */
  void setAppName(char * appName);

  /** 
   * Realize each MultiPipe window's Xt hierarchy
   */
  void xtRealize(void);

  /** 
   * Computes the size of the virtual display.
   */
  void computeVirtualSize(void);

  /** 
   * Gets the size of the virtual display.
   */
  SbVec2s getVirtualSize(void);

  /** 
   * Gets coordinates within the virtual display.
   */
  SbVec2s getVirtualCoordinates(SbVec2s mouseCoord, SbPipe * pipe);

  /** 
   * SbConfig is told where the XEvent happened (in which MultiPipe
   * window) with setEventPipe. This used to compute mouse coordinates in
   * Flat Screen Mode.
   */
  void setEventPipe(SbPipe * pipe);

  /** 
   * This function returns TRUE if the event being processed
   * occurred in a MultiPipe window.
   */
  int isEventFromPipe(void);
  
  /** 
   * Computes how to narrow the view volume.
   */
  SbBox3f computeSubViewVolume(int pipeID); 
  
#if defined(_WIN32)

  /** 
   * Returns the shared context
   */
  HGLRC getSharedContext(void);

  /** 
   * Sets the shared context
   */
  void setSharedContext(HGLRC ctx);

  /** 
   * Returns the overlay shared context
   */
  HGLRC getOverlaySharedContext(void);

  /** 
   * Sets the overlay shared context
   */
  void setOverlaySharedContext(HGLRC);

#else
  /** 
   * Returns the shared context
   */
  GLXContext getSharedContext(void);

  /** 
   * Sets the shared context
   */
  void setSharedContext(GLXContext ctx);

  /** 
   * Returns the overlay shared context
   */
  GLXContext getOverlaySharedContext(void);

  /** 
   * Sets the overlay shared context
   */
  void setOverlaySharedContext(GLXContext ctx);

  /** 
   * Sets the overlay colormap that is shared by all MultiPipe windows.
   */
  void setOverlayColormap(int startIndex,int num,XColor* xcol);
#endif

  /** 
   * Returns TRUE if PerPipeStereo mode is enabled.
   */
  SbBool isPerPipeStereo(void);

  /** 
   * Sets PerPipeStereo mode.
   */
  void setPerPipeStereo(SbBool trueOrFalse);

  /** 
   * Returns TRUE if sequential rendering mode is enabled (no threads).
   */
  SbBool isSequentialRendering(void);

  /** 
   * Sets sequential rendering mode.
   */
  void setSequentialRendering(SbBool trueOrFalse);

  /** 
   * Returns TRUE if insideOut mode is enabled.
   */
  SbBool isInsideOut(void);

  /** 
   * Sets InsideOut mode.
   */
  void setInsideOut(SbBool trueOrFalse);
  
  
  /** 
   * Returns tracker reader object specified in the configuration file.
   */
  SoTrackerReader * getTrackerReader(void);
  /** 
   * Returns controller reader object specified in the configuration file.
   */
  SoControllerReader * getControllerReader(void);
  
  /** 
   * Returns the default camera position. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */
  SbVec3f getDefaultCameraPosition(void) {return _cameraDefaultPosition;} ;
  
  /** 
   * Returns the default object position. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  SbVec3f getDefaultObjectPosition(void) {return _objectDefaultPosition;};
  
  /** 
   * Returns the radius of the sphere the model is scaled to during the
   * initialization process. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  float getObjectMaxDim(void) {return _objectMaxDimension;};
  
  /** 
   * Returns the inter-eye distance. This distance is used to offset the camera
   * during stereo rendering. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  float getInterEyeDistance(void) {return _interEyeDistance;};
  
  /** 
   * Sets the inter-eye distance. This distance is used to offset the camera
   * during stereo rendering. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  void setInterEyeDistance(float value) {_interEyeDistance = value;};

  /** 
   * Returns the identifier used to track the wand. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  int getWandTrackerId(void) {return _wandTrackerID;};
  
  /** 
   * Returns the identifier used to track the head. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  int getHeadTrackerId(void) {return _headTrackerID;};
  
  /** 
   * Sets the identifier used to track the wand. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  void setWandTrackerId(int value) {_wandTrackerID = value;};
  
  /** 
   * Sets the identifier used to track the head. This parameter is initialized in the
   * configuration file in the SoTracker node. MultiPipe immersive only. 
   */ 
  void setHeadTrackerId(int value) {_headTrackerID = value;};
 
  /** 
   * Returns TRUE if headtracking is enabled, else returns FALSE. 
   */  
  SbBool isHeadTracking(void);
  /** 
   * Sets the sensor id that tracks the head. Default value is 0.
   * If value is -1, headtracking is disabled.
   */  
  void setHeadTracking(int value);
  
  void getWandFile(SbString &str);
  void setWandFile(SbString wandiv);

 SoINTERNAL public:

  // Callback from SoXt::show
  static int mpRealize(SbConfig *config);

  private :
  
  
    // add a function to check the consistency of the configuration
    void checkConfig(void);
  
  // check the configuration file format
  int newReadConfigFile(void);
  
  void getTrackdKeys(char *,int &, int&);
    
  SbPipe ** pipe;
  int nbPipes;
  int nbFlatScreens;
  int nbWallScreens;
  char * configFilename;
  SoSeparator * cfgTree;
  
  // when an event is recieved, we need to know if it comes from one 
  // of the pipe window or from the viewer window;
  // evtPipe is used to compute virtualCoordinates.
  SbPipe * evtPipe;
  
  SbVec2s virtualSize;
  
#if !defined(_WIN32)
  GLXContext mpSharedContext;
  GLXContext mpOverlaySharedContext;
#else
  HGLRC mpSharedContext;
  HGLRC mpOverlaySharedContext;
#endif
  
  SbBool perPipeStereo;
  
  SbBool sequentialRendering;
  SbBool insideOut; 
  
  SoTrackerReader * _tracker;
  SoControllerReader * _controller;
  SbVec3f  _cameraDefaultPosition;
  SbVec3f  _objectDefaultPosition;
  float _objectMaxDimension;
  float _interEyeDistance;
  int _wandTrackerID;
  int _headTrackerID;
  SbString _wandFile;
 
};

#endif /* _SB_CONFIG_H */

