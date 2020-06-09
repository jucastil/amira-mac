/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef SOQT
#  include <Inventor/Qt/SoQtDirectionalLightEditor.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinDirectionalLightEditor.h>
#else // _WIN32

#ifndef _SO_XT_DIRECTIONAL_LIGHT_EDITOR_
#define _SO_XT_DIRECTIONAL_LIGHT_EDITOR_

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>


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
class SoXtClipboard;
class SoXtColorEditor;
class SoXtColorSlider;
class SoXtRenderArea;


// callback function prototypes
typedef void SoXtDirectionalLightEditorCB(void *userData, const SoDirectionalLight *light);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtDirectionalLightEditor
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component for editing directional lights.
 *
 * @ingroup Xt
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
 * @RESOURCES
 * <PRE>
 *   !!------------------------------------------------
 *   !! Drectional Light Editor !!
 *   !!------------------------------------------------
 *   *IvDirectLightTitle.labelString: Dir Light Editor
 *   *IvDirectLightIconTitle.labelString: Dir Light Ed
 *   *IvDirectLightInten.labelString: Inten
 *   *IvDirectLightColorEditor.labelString: Directional Light Color
 *   *IvDLMenuBar.IvEdit.labelString: Edit
 *   *IvDLMenuBar*IvControlPullDown*IvColorEditor.labelString: Color Editor
 *   *IvDLMenuBar*IvControlPullDown*IvCopy.labelString: Copy
 *   *IvDLMenuBar*IvControlPullDown*IvPaste.labelString: Paste
 *   *IvDLMenuBar*IvControlPullDown*IvHelp.labelString: Help
 * </PRE>
 *
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoDirectionalLight
 *
 *
 */

class INVENTORXT_API SoXtDirectionalLightEditor : public SoXtComponent {
 public:
  /**
   * Constructor.
   */
  SoXtDirectionalLightEditor(
                             SoWidget parent = NULL,
                             const char *name = NULL,
                             SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoXtDirectionalLightEditor();

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
   */
  inline void         addLightChangedCallback(
                                              SoXtDirectionalLightEditorCB *f,
                                              void *userData = NULL);
  /**
   * Removes the lightChanged callback.
   */
  inline void         removeLightChangedCallback(
                                                 SoXtDirectionalLightEditorCB *f,
                                                 void *userData = NULL);

  // Redefined here since there are two windows to deal with -
  // the color editor and the light manipulator
  virtual void        show();
  virtual void        hide();

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtDirectionalLightEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtDirectionalLightEditor(
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
  SoXtColorEditor     *colorEditor;
  SoXtColorSlider     *intensitySlider;
  SoXtRenderArea      *renderArea;
  SoNodeSensor        *lightSensor;
  SoNodeSensor        *cameraSensor;
  SoDirectionalLightManip     *dirLightManip;
  static char         *geomBuffer;
  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SoCallbackList      *callbackList;

  // Copy/paste support
  SoXtClipboard       *clipboard;

  // copy the src light values to the dst light values
  void                copyLight(SoDirectionalLight *dst,
                                const SoDirectionalLight *src);

  void                updateLocalComponents();

 private:
  // Callback routines from components and manipulators
  static void         colorEditorCB(void *, const SbColor *);
  static void         intensitySliderCB(void *, float);
  static void         pasteDoneCB(void *, SoPathList *);
  static void         dirLightManipCB(void *, SoDragger *);

  // Callback routines from Xt/Motif
  static void         menuPick(SoWidget, int, XmAnyCallbackStruct *);

  // Sensor callbacks
  static void         cameraSensorCB(SoXtDirectionalLightEditor *, SoSensor *);
  static void         lightSensorCB(SoXtDirectionalLightEditor *, SoSensor *);

  // Build routines
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              buildPulldownMenu(SoWidget parent);

  static void visibilityChangeCB(void *pt, SbBool visible);
  void        activate();             // connects the sensor
  void        deactivate();           // disconnects the sensor

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

// Inline functions
void
SoXtDirectionalLightEditor::addLightChangedCallback(
                                                    SoXtDirectionalLightEditorCB *f,
                                                    void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoXtDirectionalLightEditor::removeLightChangedCallback(
                                                       SoXtDirectionalLightEditorCB *f,
                                                       void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#endif // _SO_XT_DIRECTIONAL_LIGHT_EDITOR_

#endif // _WIN32


