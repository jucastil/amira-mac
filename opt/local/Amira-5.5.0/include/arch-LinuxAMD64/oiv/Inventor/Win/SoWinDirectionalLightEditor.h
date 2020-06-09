/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_DIRECTIONAL_LIGHT_EDITOR_
#define _SO_WIN_DIRECTIONAL_LIGHT_EDITOR_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/sys/port.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Win/SoWinComponent.h>


class SoBase;
class SoCamera;
class SoDirectionalLight;
class SoDirectionalLightManip;
class SoDragger;
class SoGroup;
class SoNodeSensor;
class SoPath;
class SoPathList;
class SoPerspectiveCamera;
class SoSensor;
class SoSeparator;
class SoWinClipboard;
class SoWinColorEditor;
class SoWinColorSlider;
class SoWinRenderArea;


// callback function prototypes
/** 
 * [OIV-WRAPPER NAME{EditorCB}] 
 */
typedef void SoWinDirectionalLightEditorCB(void *userData, const SoDirectionalLight *light);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinDirectionalLightEditor
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Component for editing directional lights.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   This class is used to edit an SoDirectionalLight node (color, intensity, and
 *   direction are changed). In addition to directly editing directional light nodes,
 *   the editor can also be used with callbacks which will be called whenever the
 *   light is changed. The component consists of a render area and a value slider in
 *   the main window, with controls to display a color picker. In the render area
 *   there appears a sphere representing the world, and a directional light
 *   manipulator representing the direction of the light. Picking on the manipulator
 *   and moving the mouse provides direct manipulation of the light direction. The
 *   color picker is used to edit the color, and the value slider edits the
 *   intensity.
 *   
 *   The editor can currently be attached to only one light at a time. Attaching to
 *   two different lights will automatically detach the first one before attaching
 *   the second.
 * 
 * @SEE_ALSO
 *    SoWinComponent,
 *    SoDirectionalLight
 * 
 * 
 */ 

class INVENTORW_API SoWinDirectionalLightEditor : public SoWinComponent {
 public:
  /**
   * Constructor.
   */
  SoWinDirectionalLightEditor(
                              SoWidget parent = NULL,
                              const char *name = NULL, 
                              SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoWinDirectionalLightEditor();

  /**
   * Attaches the editor to a directional light. When attached, changes
   * made in the editor directly affect the attached light.
   */
  void                attach(SoPath *pathToLight);
  /**
   * Detaches the editor from a directional light.
   */
  void                detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool              isAttached()    { return (dirLight != NULL); }
    
  /**
   * Sets new light values.
   */
  void                setLight(const SoDirectionalLight &newLight);
  /**
   * Gets the current light values.
   */
  const SoDirectionalLight &getLight() const { return *dirLight; }
    
  /**
   * Adds lightChanged callback. This is an
   * additional way of using the directional light editor, by registering a callback
   * and setting the light.
   * [OIV-WRAPPER EVENT_NAME{LightChanged}]
   */
  inline void         addLightChangedCallback(
                                              SoWinDirectionalLightEditorCB *f, 
                                              void *userData = NULL);
  /**
   * Removes the lightChanged callback.
   * [OIV-WRAPPER EVENT_NAME{LightChanged}]
   */
  inline void         removeLightChangedCallback(
                                                 SoWinDirectionalLightEditorCB *f, 
                                                 void *userData = NULL);

  // Redefined here since there are two windows to deal with -
  // the color editor and the light manipulator
  virtual void        show();
  virtual void        hide();

  SbBool alwaysOnTop;
 protected:

  SoWidget              mgrWidget;      // topmost widget

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinDirectionalLightEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinDirectionalLightEditor(
                                SoWidget parent,
                                const char *name, 
                                SbBool buildInsideParent, 
                                SbBool buildNow);

  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  SoDirectionalLight  *dirLight;          // light we are editing
  SoSeparator         *root;              // root of local scene graph
  SoSeparator         *litStuff;          // what's on display under thelight

  SoPerspectiveCamera *myCamera;
  SoCamera            *cameraToWatch;
    
  // components, manips, sensors
  SoWinColorEditor    *colorEditor;
  SoWinColorSlider    *intensitySlider;
  SoWinRenderArea      *renderArea;    
  SoNodeSensor        *lightSensor;
  SoNodeSensor        *cameraSensor;
  SoDirectionalLightManip     *dirLightManip;
  static char             *geomBuffer;
  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SoCallbackList      *callbackList;
    
  // Copy/paste support
  SoWinClipboard      *clipboard;
    
  // copy the src light values to the dst light values
  void                copyLight(SoDirectionalLight *dst, 
                                const SoDirectionalLight *src);
                            
  void                updateLocalComponents();

 private:

  HMENU menubar ;

  static WBOOL CALLBACK mgrDlgProc( Hwnd hdlg, UINT message,
                                    WPARAM wParam, LPARAM lParam );
  static void onCommand(
                        Hwnd hdlg,
                        int id,
                        Hwnd hCtrl,
                        UINT codeNotify ) ;

  void handleEdit(
                  int nSlider,
                  Hwnd hEdit,
                  UINT codeNotify) ;

  void handleMenu(Hwnd hdlg,
                  SoWinDirectionalLightEditor *p,
                  int id ) ;

  void initPlacement() ;

  static void colorEditorCloseCB(void *userData, SoWinComponent *comp) ;

  // Callback routines from components and manipulators
  static void         colorEditorCB(void *, const SbColor *);
  static void         intensitySliderCB(void *, float);
  static void         pasteDoneCB(void *, SoPathList *);
  static void         dirLightManipCB(void *, SoDragger *);

  // Callback routines from Xt/Motif
  static void         menuPick(SoWidget, int, XmAnyCallbackStruct *);
    
  // Sensor callbacks
  static void         cameraSensorCB(SoWinDirectionalLightEditor *, SoSensor *);
  static void         lightSensorCB(SoWinDirectionalLightEditor *, SoSensor *);

  // Build routines
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              buildPulldownMenu(SoWidget parent);

  static void visibilityChangeCB(void *pt, SbBool visible);
  void        activate();             // connects the sensor
  void        deactivate();           // disconnects the sensor
    
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
  SoNode *geom;

};

// Inline functions
INVENTORW_API void
SoWinDirectionalLightEditor::addLightChangedCallback(
                                                     SoWinDirectionalLightEditorCB *f, 
                                                     void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

INVENTORW_API void
SoWinDirectionalLightEditor::removeLightChangedCallback(
                                                        SoWinDirectionalLightEditorCB *f, 
                                                        void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_DIRECTIONAL_LIGHT_EDITOR_

