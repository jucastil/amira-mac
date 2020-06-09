/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
**=======================================================================*/


#ifndef SoTVizViewer_H
#define SoTVizViewer_H




#ifdef _WIN32
class SoWinBitmapButton;
#ifdef TVIZ_USE_JOYSTICK
class SiTVizJoystick;
#endif
#endif

#include <Inventor/Xt/viewers/SoXtConstrainedViewer.h>
#include <TerrainViz/viewer/SoTVizCameraManager.h>

#ifdef _WIN32
#  include <Inventor/sys/SoDynamicLibManager.h>
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVTVIZWDLL "TerrainVizWinD.dll"
#    define __INVTVIZWLIB "TerrainVizWinD.lib"
#  else
#    define __INVTVIZWDLL "TerrainVizWin.dll"
#    define __INVTVIZWLIB "TerrainVizWin.lib"
#  endif
#  ifndef TerrainVizWin_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVTVIZWLIB)
#    endif
#  endif
#else
#  define __INVTVIZWDLL "libTerrainVizXt"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoTerrainVizWin, __INVTVIZWDLL)

class SoSwitch;
class SoSeparator;
class SoPerspectiveCamera;
class SoDirectionalLight;
class SoCallback;
class SoNode;
class SoTransform;
class SoFieldSensor;
class SoTVizControls;
class SoTVizNavigationTools;
class SoTVizNavigationToolBase;


// some default values
#define DEFAULT_SPD_MOD_COEF             1.f
#define DEFAULT_MAX_ROLL_ANGLE          30.f
#define DEFAULT_TERRAINSIZE_TO_MAXSPEED   .1f
#define FLY_SPD_FACTOR                    .3f
#define TOPLEFTWHEEL_FACTOR               .1f

/**
*
* @TVEXT Abstract base class for SoTVizViewer.
* 
* @ingroup TerrainViz
* 
* @DESCRIPTION
*   This class is a constrained viewer that has been customized for terrain viewing.
*   The environment variable TVIZ_VIEWER_DATA_PATH should specify the directory where 
*   the .iv files for navigation tools
*   are located (typically $OIVHOME/data/TerrainViz/viewer).
*
*  
*   You can add different types of nodes to this viewer:
*   - an SoTVizRender node, using setScenegraph() and then setTerrain()
*   - a separator containing an SoQuadMesh node
*   - a separator containing an SoVertexProperty and an SoQuadMesh
*   - a separator containing an SoCoordinate3 and an SoQuadMesh
*   - a shape node
*
*   @B Note:@b This viewer is not compatible with Qt.
*
* @SEE_ALSO
*    SoXtConstrainedViewer,
*    SoWinConstrainedViewer,
*    SoTVizCameraManager
* 
*/ 
class TERRAINVIZW_API SoTVizViewer : public SoXtConstrainedViewer, public SoTVizCameraManager
{
public:

  /**
   *  Constructor.
   */
  SoTVizViewer ( SoWidget parent = NULL,
                 const char *name = NULL,
                 SbBool buildwithDefaultTools = TRUE,
                 SbBool buildInsideParent = TRUE,
                 SoXtFullViewer::BuildFlag flag = BUILD_ALL,
                 SoXtViewer::Type type = BROWSER);

  /**
   *  Destructor.
   */
  ~SoTVizViewer ();

  
  /**
   *  Switches the navigation mode between walk mode (default) and flying mode.
   */
  virtual void setFlyMode (SbBool onOff);
  
  /**
   *  Returns TRUE if flying mode is active.
   */
  virtual SbBool isFlyMode () const;
  
  /**
   *  Reverses the up and down directions in flying mode.
   *  Default is FALSE.
   */
  virtual void setInvertedControlsMode (SbBool onOff);
  
  /**
   *  Returns TRUE if flying mode is reversed.
   */
  virtual SbBool isInvertedControlsMode () const;
  
  /**
   *  Sets the maximum roll angle.
   *  Turning left/right while flying will cause rolling (a.k.a. banking) up to
   *  this maximum angle.
   *  A zero value prevents rolling. The default is 30 degrees.
   */
  virtual void  setMaxRollAngle (float newAngle);
  
  /**
   *  Returns the maximum roll angle.
   */
  virtual float getMaxRollAngle () const;
  
  
  /**
   *  Sets a multiplier on speed based on distance between camera and ground.
   *  This feedback is active by default.
   */  
  virtual void setElevationRelativeSpeedMode (SbBool onOff);
  
  /**
   *  Returns TRUE if distance feedback on speed is active.
   */  
  virtual SbBool isElevationRelativeSpeedMode () const;
  
  
  enum speedUnits {
    /**
     * Speed is in Km/h.
     */
    KILOMETERS_PER_HOUR,
    /**
     * Speed is in m/s.
     */
    METERS_PER_SECOND,
    /**
     * Speed is in mph.
     */
    MILES_PER_HOUR
  };
  
  
  /**
   *  Sets the speed units. Default = KILOMETERS_PER_HOUR.
   */
  virtual void setSpeedUnit (SoTVizViewer::speedUnits newSpeedUnit = SoTVizViewer::KILOMETERS_PER_HOUR);

  /**
   *  Returns the speed units used.
   */
  virtual SoTVizViewer::speedUnits getSpeedUnit () const;
  
  /**
   * Modulates maximum speed with a coefficient as follows:<BR> 
   * If ElevationRelativeSpeed is TRUE, then <BR>
   * max_speed = relative_elevation * speed_modulation_coeff<BR>
   * Otherwise, max_speed is specified using #setMaxSpeed.
   */   
  virtual void  setSpeedModulationCoeff (float newCoeff);
        
  /**
   * Returns the speed modulation coefficient. 
   */   
  virtual float getSpeedModulationCoeff () const;
  
  /**
   * Sets the maximum speed.
   * Active only if ElevationRelativeSpeed is FALSE (set with 
   * #setElevationRelativeSpeedMode). Otherwise, maximum speed is computed
   * using the speed modulation coefficient. See #setSpeedModulationCoeff.<BR>
   * Default = m_terrainMaxSize*DEFAULT_TERRAINSIZE_TO_MAXSPEED*getToRealLength()
   * where m_terrainMaxSize is the dimension of the largest side of the terrain data, 
   * DEFAULT_TERRAINSIZE_TO_MAXSPEED is 0.1, and getToRealLength() is expressed in m/s.
   * If autoMaxSpeed is TRUE, then maximum speed will be automatically recomputed each 
   * time a new terrain is loaded.
   */

  virtual void  setMaxSpeed (float newSpeed, SbBool autoMaxSpeed = FALSE);
  
  /**
   *  Returns the maximum speed allowed.
   */
  virtual float getMaxSpeed () const;
  
  /**
   *  Prevents the camera from going outside the terrain borders.
   */
  virtual void setBorderRespect (SbBool onOff);
  
  
  /**
   * Turns constant elevation mode on/off. Default = FALSE.
   * If ConstantElevationMode is TRUE, then the camera moves at a fixed height relative
   * to the terrain. That is, the camera position (X,Y,Z) has
   *
   * Z = terrainHeight(X,Y) + offset
   * 
   * where offset is fixed at the current height when ConstantElevationMode
   * is set to TRUE. 
   */
  virtual void setConstantElevationMode (SbBool onOff, SbBool resetElevation = FALSE);
  
  /**
   * Changes camera height in constant elevation mode. The default is the current
   * camera offset. The units are the units specified using 
   * #SoTVizCameraManager::setIOLengthUnit.
   */
  virtual void setTargetRelativeElevation (double newElevation);
  
  /**
   *  Sets the minimum elevation of the camera.
   */  
  virtual void setMinimumElevation (double newMinimalElevation);

  /**
   *  To be called if the terrain node is not the scene graph root specified by setScenegraph().
   */  
  virtual void setTerrain (SoNode* t);

  /**
   * Sets the north direction. Default = (0,1,0) (Y).
   */
  void setNorth (SbVec3f& newNorth);
        
  /**
   * Returns the north direction.
   */
  SbVec3f getNorth() const;

  /**
   * Shows the viewer controls interface. You can control the visibility
   * of the controls interface using #setTerrainNavigationToolsVisibility.
   */
  virtual void openControls();

  /**
   *  Returns a pointer to the internal SoTVizNavigationTools instance.
   *  This is useful for adding or removing interface elements.
   */
  virtual SoTVizNavigationTools* getTerrainNavigationTools () const;
   
  /** 
   *  Sets the navigation tools visible or not.
   */
  virtual void setTerrainNavigationToolsVisibility (SbBool onOff);
   
  /**
   *  Returns TRUE if navigation tools are visible.
   */
  virtual SbBool getTerrainNavigationToolsVisibility () const;
   
   
  /** 
   *  Sets the navigation tools interactive or not.
   */
  virtual void setTerrainNavigationToolsInteractivity (SbBool onOff);
   
  /**
   *  Returns TRUE if navigation tools are interactive.
   */
  virtual SbBool getTerrainNavigationToolsInteractivity () const;
   
   
   
  /**
   * Sets the scene graph to render. Whenever a new scene is supplied, the first camera 
   * encountered will be by default used as the edited camera. If the scene graph
   * has no camera, a new camera will be created. See SoXtViewer for a more complete
   * description of nodes that may be added when #setSceneGraph is called.
   */
  virtual void setSceneGraph (SoNode *);
   
  /**
   * Sets the edited camera. Setting the camera is only needed if the first camera found 
   * in the scene when setting the scene graph isn't the one the programmer really wants to edit. 
   */
   
  virtual void setCamera (SoCamera *);
   
  /**
   *  Returns a pointer to the camera.
   */  
  virtual SoCamera* getCamera () const;
   
  /**
   * Turns the headlight on/off. Default = on.
   */
  virtual void setHeadlight(SbBool);
   
  /**
   * Sets the up direction of the viewer. Default = (0,0,1) (Z).
   */
  virtual void setUpDirection (SbVec3f& newUpDirection);
   
  /**
   * Returns the up direction of the viewer.
   */
  virtual SbVec3f getUpDirection() const { return getGuiConstrainedViewer()->getUpDirection(); }
   
  /**
   * Changes the camera position to view the entire scene (the camera zoom and 
   * orientation are not changed). 
   */
  virtual void viewAll();
   
  /**
   * Restores the camera values. 
   */
  virtual void resetToHomePosition();
   
   
  /**
   * Sets whether the viewer is turned on or off. When turned on, events are consumed
   * by the viewer. When viewing is off, events are processed by the viewer's render area.
   * This means events will be sent down to the scene graph for processing (i.e., picking 
   * can occur). Note that if the application has registered an event callback, it will be 
   * invoked on every message, whether viewing is turned on or not. However, the return 
   * value of this callback (which specifies whether the callback handled the event or not)
   * is ignored when viewing is on. That is, the viewer will process the event even if the 
   * callback already did. This is to ensure that the viewing paradigm is not broken (default
   * viewing is on). 
   */
  virtual void setViewing (SbBool onOff);
   
  /**
   * Sets whether the viewer is allowed to change the cursor over the renderArea window. 
   * When disabled, the cursor is undefined by the viewer and will not change as the mode 
   * of the viewer changes. When re-enabled, the viewer will reset it to the appropriate icon. 
   * Disabling the cursor enables the application to set the cursor directly on the viewer 
   * window or on any parent widget of the viewer. This can be used when setting a busy cursor
   * on the application shell. This value is inherited from SoXtViewer, default = TRUE.
   */
  virtual void setCursorEnabled(SbBool onOff);
   


protected:

  // protected constructor for delayed building
  SoTVizViewer(SoWidget parent,
               const char *name,
               SbBool buildwithDefaultTools,
               SbBool buildInsideParent,
               SoXtFullViewer::BuildFlag flag,
               SoXtViewer::Type type,
               SbBool buildNow);

  void
  SoTVizViewerCommon(SoWidget parent,
                     const char *name,
                     SbBool buildwithDefaultTools,
                     SbBool buildInsideParent,
                     SoXtFullViewer::BuildFlag flag,
                     SoXtViewer::Type type,
                     SbBool buildNow);


  // Viewer modes
  enum {
    PICK_MODE, 
    WALK_MODE,
    WALK_MODE_ACTIVE, 
    TILT_MODE, 
    TILT_MODE_ACTIVE, 
    PAN_MODE, 
    PAN_MODE_ACTIVE, 
    FLY_MODE,
    FLY_MODE_ACTIVE,
    SEEK_MODE
  };
  int m_mode;
  
  // Viewer new buttons
  enum {
    // ConstrainedViewer has allready 7 PushButtons
    FLY_PUSH = 8, 
    CT_ELEVATION_PUSH = 9
  };
  
  // Mouse location
  SbVec2s m_locator;

  void commonDelete() ;


#ifdef _WIN32
  // redefined methods for cursors management
  HCURSOR sizeCursor, moveCursor;
  // redefined methods for new popup menu
  virtual void buildPopupMenu();
  // callback for viewer buttons
  virtual void pushButtonCB (SoWidget w, int id, void *);
  // popup management
  virtual void processPopupItem(int item);
  // Methods dealing with the new top left wheel of viewer decoration
  static void topLeftWheelCB (SoTVizViewer *v, XtPointer *d);
#elif defined(__APPLE__)

#else
  SbBool createdCursors;
  Cursor walkCursor, spinCursor, panCursor, flyCursor, seekCursor;
  // redefined methods for new popup menu
  // pb : parent method is not virtual
  virtual SoWidget buildFunctionsSubmenu(SoWidget popup);
  virtual void rightWheelMotion(float newVal);
  // Methods dealing with the new top left wheel of viewer decoration
  static void topLeftWheelCB(SoWidget, SoTVizViewer *v, XtPointer *d);
#endif

  void setFlyModeCommon (SbBool onOff);
  void setConstantElevationModeCommon (SbBool onOff, SbBool resetElevation);

  virtual void defineCursors();
  virtual void updateCursor();

  // Redefined to redraw navigation tools on window size changes
  virtual void sizeChanged(const SbVec2s & newSize);

  // redefined decoration building methods
  virtual SoWidget buildLeftTrim(SoWidget parent);

  // Create custom buttons
  virtual void createViewerButtons(SoWidget parent);

  // redefined method to react to events
  virtual void processEvent (XAnyEvent *);

  // Redefined viewer methods
  virtual void setSeekMode (SbBool flag);

  // Viewer mode switch method
  void switchMode (int newMode);

  float        topLeftWheelVal;
  virtual void topLeftWheelStart();
  virtual void topLeftWheelFinish();
  virtual void topLeftWheelMotion(float newVal);

  // Redefined from TerrainCameraManager to take speed unit in account
  // and support controls interface update
  virtual void updateIOUnits();

  // Navigation tools in the render area
  SoTVizNavigationTools * m_navTools;
  SbBool m_terrainNavigationToolsVisibility;
  SbBool m_terrainNavigationToolsInteractivity;
  
  // processEvent method variables
  SbBool m_controlKey;
  SbBool m_shiftKey;
  SbBool m_leftButton;

private:

  // the real constructor method
  void constructorCommon (SbBool buildNow);

  // Controls interface
  SoTVizControls * m_controlsBox;
  SoSwitch * m_navToolsSwitch;
  
  // m_internalNorthDirection is the normalized projection of m_northVector
  // on upDirection normal plan
  SbVec3f       m_northVector;
  SbVec3f m_internalNorthDirection;
  // Called when north or up direction changes
  void    updateNorthDirection();
  
  SbBool  m_flyMode;
  SbBool  m_invertedControlsMode;
  SbBool  m_buildwithDefaultTools;
  float   m_maxRollingAngle;
  
  SoNode* m_sceneGraph;
  SoNode* m_terrain;
  
  SoTVizViewer::speedUnits m_speedUnit;
  float m_toIOSpeed;
  SbBool  m_elevationRelativeSpeedMode;
  float m_speedModulationCoeff;
  float m_maxSpeed;
  float m_previousAngleX;

  // Update the viewer camera speed
  void computeViewerSpeed ();
  
  // camera sensors and theirs callbacks
  SoFieldSensor * m_cameraPositionSensor;
  SoFieldSensor * m_cameraOrientationSensor;
  static void     cameraPositionCB (void *, SoSensor *);
  static void     cameraOrientationCB (void *, SoSensor *);
  
  // methods and variables used during animation phases
  static void   animationSensorCB (void *, SoSensor *);
  void      startAnimating ();
  void      stopAnimating ();
  void        doCameraAnimation ();
  SbRotation  m_noRolling;
  SbTime            m_prevAnimTime;
  SoFieldSensor * m_animationSensor;

  SbVec3f m_previousCameraPosition;
  SbBool  m_resetCamera;

  float  m_maxHeight;

  double m_previousTargetHeight;

  SbVec2s m_locatorOnLeftClick;

  SbBool m_autoMaxSpeed;

#ifdef _WIN32
private:
  // two viewer buttons more
  SoWinBitmapButton* fly_Button;
  SoWinBitmapButton* ct_Elevation_Button;

  // Because this is private in our parent class, we will need our own
  SoWinBitmapButton* buttonList[12];
  // Pointer to the InvTViz DLL
  SoDynamicLibManager::SafeLibraryHandle TVizWinDLL;
  // Pointer to the inventor resource DLL
  SoDynamicLibManager::SafeLibraryHandle resDLL;

#ifdef TVIZ_USE_JOYSTICK
private:
  SiTVizJoystick* m_joystick;
  SbBool m_joystickUsed;
  int m_previousMode;

 SoINTERNAL public:
  static void setJoystickCallback(void *data, SoSensor *);
  void joystickControl ();
  SbBool isJoystickActivated();
  // If joystickUsed==0 (keyboard) -> joystickUsed=1 (joystick) and vice versa
  void   switchControlInput();
  SbBool isJoystickUsed();
  SbBool isButtonPressed(unsigned char which_one);
#endif

#elif defined(__APPLE__)

#else
private:
  // two viewer buttons more
  SoXtBitmapButton* flyPushButton;
  SoXtBitmapButton* cstElevPushButton; 
  // redefined to react to popup menu events
  static void menuPick(SoWidget, int id, XmAnyCallbackStruct *);
  // callback for viewer buttons
  static void pushButtonCB (SoWidget w, int id, void *);
#endif

};

#endif // SoTVizViewer_H
