/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef SO_GUI_EXAMINER_VIEWER
#define SO_GUI_EXAMINER_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiViewer
//
// SoXXExaminerViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiAlgoViewers.h>

// classes used
class SbSphereSheetProjector;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SbTime;

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiExaminerViewer : public SoGuiAlgoViewers 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiExaminerViewer );
#endif

SoINTERNAL public:

  //Macros
#define KEY_PRESS_CHECK_VALID_MACRO \
  if ( m_mode != IDLE_MODE && m_mode != SPIN_MODE && \
  m_mode != TRANS_MODE && m_mode != DOLLY_MODE ) \
  break;

// size of the rotation buffer, which is used to animate the spinning ball.
#define ROT_BUFF_SIZE 3

  /**
   * Viewing mode.
   */
  enum ViewingMode 
  {
    /**
     * Rotate the camera around the point of interest.
     */
    VIEWING_MODE_SPIN,

    /**
     * Same as VIEWING_MODE_SPIN but add also constrained camera rotation.
     * It modifies the viewer usage described previously as follow:
     *  - @B Ctrl + Left Mouse @BR: Rotation around the Z axis
     *  - @B Shift + Left Mouse or @BR: Rotation around the X or the Y axis.
     *    If the mouse movement is globally from the left to the right (resp. 
     *    from up to down) the Y axis (resp. X axis) is chosen.
     */
    VIEWING_MODE_SPIN_CONSTRAINED,

    /**
     * Translate the camera in the viewer plane.
     */
    VIEWING_MODE_PAN,

    /**
     * Dolly/Zoom (move forward and backward) to
     *   get closer to or further away from the point of interest.
     */
    VIEWING_MODE_ZOOM
  };

  enum ViewerModes 
  {
    PICK_MODE,          // Alt key can take us out of viewing mode
    VIEW_MODE,          // Equivalent to old IDLE_MODE
    SPIN_MODE = VIEW_MODE,
    SPIN_MODE_ACTIVE,   // Equivalent to old SPIN_MODE
    SPINX_MODE_ACTIVE,	    	// Rotation on X axis.
    SPINY_MODE_ACTIVE,	    	// Rotation on Y axis.
    SPINZ_MODE_ACTIVE,	    	// Rotation on Z axis.
    PAN_MODE,           // Just Ctrl key pressed (similar to old ROLL_MODE)
    PAN_MODE_ACTIVE,    // Equivalent to old TRANS_MODE
    DOLLY_MODE,          // 
    DOLLY_MODE_ACTIVE,  // Equivalent to old DOLLY_MODE
    SEEK_MODE,
    SPINX_VIEWER_MODE_ACTIVE,	// Rotation on X viewer axis.
    SPINY_VIEWER_MODE_ACTIVE,	// Rotation on Y viewer axis.
    SPINZ_VIEWER_MODE_ACTIVE,	// Rotation on Z viewer axis.
    REVERSE_DOLLY_MODE_ACTIVE, // A reversed DOLLY MODE
    ROLL_MODE,
    ROLL_MODE_ACTIVE, // Rotation centered around an anchor.
    EMPTY_MODE = -1
  };

  // list of custom push buttons
  enum 
  {
    CAM_PUSH = 0,
    PUSH_NUM
  };

  // Defines the spining type
  enum ViewingSpinType 
  {
    VIEWING_SPIN_FREE,
    VIEWING_SPIN_X_OR_Y, // Means that the spin is either on the X or on the Y axis
    VIEWING_SPIN_X,
    VIEWING_SPIN_Y,
    VIEWING_SPIN_Z
  };

  /**
   * Constructor.
   */
  SoGuiExaminerViewer();

  /**
   * Sets the viewing mode.
   * This methods specifies what is the viewing behavior when the left mouse is 
   * pressed. 
   */
  void setViewingMode( ViewingMode viewingMode );

  /**
   * Gets the current viewing mode.
   */
  ViewingMode getViewingMode() const;

  /**
   * Shows/hides the point of rotation feedback, which only appears while in viewing
   * mode (default is off).
   */
  void setFeedbackVisibility( SbBool insertFlag );

  void setFeedbackFlag( SbBool flag );

  /**
   * Returns the rotation feedback flag.
   */
  SbBool isFeedbackVisible() const;

  /**
   * Sets the point of rotation feedback size in pixels (default 20 pix).
   */
  void setFeedbackSize( int newSize );

  /**
   * Returns the point of rotation feedback size in pixels.
   */
  int getFeedbackSize() const;

  /**
   * Enables/disables the spin animation feature of the viewer (enabled by
   * default).@BR
   * @BR
   * The default value can be set using the environment variable
   * OIV_VIEWER_ANIMATION (0 = OFF, 1 = ON).
   */
  void setAnimationEnabled( SbBool flag );

  /**
   * Returns whether spin animation is enabled.
   */
  SbBool isAnimationEnabled();

  void setAnimatingFlag( SbBool flag );

  /**
   * Queries if the viewer is currently animating.
   */
  SbBool isAnimating();

  //Accessor for the member m_feedbackSwitch
  SoSwitch* getFeedbackSwitch() const;

  // ----------------------- Extension usage -----------------------------------

  // redefine those routines to do viewer specific stuff
  virtual void actualRedraw();

  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );

protected:

  /**
   * Destructor.
   */
  virtual ~SoGuiExaminerViewer();

// ----------------------- Private usage -------------------------------------
private:

  void createFeedbackNodes();

  // Viewer state variables
  ViewingMode m_viewingMode;
  int m_viewerMode;

  // point of rotation feedback vars
  SbBool m_feedbackFlag;
  SoSeparator* m_feedbackRoot;
  SoSwitch* m_feedbackSwitch;
  SoTranslation* m_feedbackTransNode;
  SoScale* m_feedbackScaleNode;
  float m_feedbackSize;
  static char* m_geometryBuffer;

  // variables used for spinning animation
  SbBool m_animationEnabled, m_animatingFlag;
  SbBool m_computeAverage;
  SbRotation m_averageRotation;
  SbRotation* m_rotBuffer;
};

#endif // SO_GUI_EXAMINER_VIEWER
