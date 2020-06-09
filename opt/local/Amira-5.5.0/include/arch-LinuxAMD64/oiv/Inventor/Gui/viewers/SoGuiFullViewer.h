/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_FULL_VIEWER
#define  SO_GUI_FULL_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiFullViewer
//
// SoXXFullViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiViewer.h>

// classes used
class SoFieldSensor;
class SoStereoDialog;

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiFullViewer : public SoGuiViewer 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiFullViewer );
#endif

SoINTERNAL public:
  // This specifies what should be build by default in the constructor
  enum BuildFlag 
  {
    /**
     *  Doesn't build anything extra 
     */
    BUILD_NONE          = 0x00, 
    /**
     *  Build the decoration only 
     */
    BUILD_DECORATION    = 0x01, 
    /**
     *  Build the popup menu only 
     */
    BUILD_POPUP         = 0x02, 
    /**
     *  Build everything by default 
     */
    BUILD_ALL           = 0xff 
  };

  /*
   * Defines
   */
  // list of the different popup choices
  enum popupChoices 
  {
    VIEW_ALL = 20,  // enables the same menu routine to be used
    SET_HOME,    // as the draw style entrie (can't overlap
    HOME,         // with SoWinViewerDrawStyle values)
    HEADLIGHT, 
    SEEK, 
    PREF, 
    VIEWING, 
    OPENRT, 
    DECORATION, 
    FULLSCREEN,
    COPY_VIEW, 
    PASTE_VIEW,
    HELP,
    DIRECTVIZ
  };

  enum drawChoices 
  {
    AS_IS,
    HIDDEN_LINE, 
    NO_TXT, 
    LOW_RES, 
    LINE, 
    POINT,
    BBOX, 
    
    MOVE_SAME_AS, 
    MOVE_NO_TXT, 
    MOVE_LOW_RES, 
    MOVE_LINE, 
    MOVE_LOW_LINE, 
    MOVE_POINT, 
    MOVE_LOW_POINT, 
    MOVE_BBOX, 
    
    DRAW_STYLE_NUM // specify the length
  };

  // list of the toggle buttons in the popumenu
  enum popupToggles 
  {
    HEADLIGHT_WIDGET = 0,    // very convenient to start at 0
    VIEWING_WIDGET,
    OPENRT_WIDGET,
    DECORATION_WIDGET,
    FULLSCREEN_WIDGET,
    DIRECTVIZ_WIDGET,
    POPUP_TOGGLE_NUM   // specify the length
  };

  // list of custom push buttons
  enum ViewerPushButtons 
  {
    PICK_PUSH, 
    VIEW_PUSH, 
    HELP_PUSH, 
    HOME_PUSH,
    SET_HOME_PUSH,
    VIEW_ALL_PUSH,
    SEEK_PUSH,
    PUSH_NUM
  };

  /**
   * Constructor.
   */
  SoGuiFullViewer();

  /**
   * Shows/hides the viewer component trim (default on). See the viewer constructor to
   * prevent the decoration from being built.
   *
   * The default value can be set using the environment variable
   * OIV_VIEWER_DECORATION (0 = OFF, 1 = ON).
   */
  void setDecoration( SbBool onOrOff );

  /**
   * Returns whether the viewer component trim is on or off.
   */
  SbBool isDecoration();
    
  /**
   * Enables/disables the viewer popup menu (default enabled). See the viewer
   * constructor to prevent the popup menu from being built.
   *
   * The default value can be set using the environment variable
   * OIV_VIEWER_POPUP_MENU (0 = OFF, 1 = ON).
   *
   * Description or equivalent function for each submenu of this popup menu:
   * - Functions: Manage the position of the camera:
   *   -> Home see resetToHomePosition()
   *   -> Set home see saveHomePosition()
   *   -> View all see viewAll()
   *   -> Seek see seekToPoint(const SbVec2s& mouseLocation)
   * - DrawStyle: Manage the draw style and buffering style:
   *   -> see setDrawStyle(DrawType type, DrawStyle style)
   *   -> see setBufferingType(BufferType type)
   * - Viewing: see setViewing()
   * - Decorations: see setDecoration()
   * - FullScreen: see setFullScreen()
   * - HeadLight: see setHeadlight()
   * - Preferences:
   *   -> Seek to point: Enables/disables seek mode (like the 'S' key)
   *   -> Auto clip planes: Enables/disables automatic clipping
   *   -> Stereo: Opens the stereo dialog
   *   -> Full scene antialiasing: see setFullSceneAntialiasing()
   *   -> Record: Opens the recording dialog
   *   -> DirectViz: Opens the DirectViz ray tracing dialog
   *   -> Rotation axes: Shows/hides the rotation axes
   */
  void setPopupMenuEnabled( SbBool trueOrFalse );

  /**
   * Returns whether the viewer popup menu is enabled or disabled.
   */
  SbBool isPopupMenuEnabled();

  // Accessors and mutators for xxWheelVals
  void setRightWheelVal( float newVal );
  float getRightWheelVal() const;

  void setBottomWheelVal( float newVal );
  float getBottomWheelVal() const;

  void setLeftWheelVal( float newVal );
  float getLeftWheelVal() const;

  void initVars( BuildFlag buildFlag ); // Initialize m_popupEnabled & m_decorationFlag

  // ----------------------- Extension usage -----------------------------------
    
  // Subclasses can redefine these to add viewer functionality. They
  // by default call start and finish interactive viewing methods.
  // (defined in the base class).
  virtual void rightWheelStart();
  virtual void bottomWheelStart();
  virtual void leftWheelStart();
  virtual void rightWheelFinish();
  virtual void bottomWheelFinish();
  virtual void leftWheelFinish();

  int SO_WHEEL_DELTA;

  protected:
   /**
    * Destructor.
    */
   virtual ~SoGuiFullViewer();

  // ----------------------- Private usage -------------------------------------
  private:

  SbBool m_decorationFlag;
  SbBool m_popupEnabled;
  float  m_rightWheelVal, m_bottomWheelVal, m_leftWheelVal;
};

#endif  // SO_GUI_FULL_VIEWER
