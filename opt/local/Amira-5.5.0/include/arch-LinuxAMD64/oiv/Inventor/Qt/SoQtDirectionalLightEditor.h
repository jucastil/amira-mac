/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_QT_DIRECTIONAL_LIGHT_EDITOR_
#define _SO_QT_DIRECTIONAL_LIGHT_EDITOR_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/misc/SoCallbackList.h>

class SbColor;
class SoDirectionalLight;
class SoSeparator;
class SoDirectionalLightManip;
class SoDragger;
class SoQtColorEditor;
class SoQtColorSlider;
class SoQtRenderArea;
class SoNodeSensor;
class QMenu;
class QAction;
class SoSensor;
class SoCamera;
class SoPerspectiveCamera;
class SoPath;

// callback function prototypes
typedef void SoQtDirectionalLightEditorCB(void *userData, const SoDirectionalLight *light);


//////////////////////////////////////////////////////////////////////////////
//  Class: SoQtDirectionalLightEditor

/**
 * @VSGEXT Component for editing directional lights.
 * 
 * @ingroup Qt
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
 *    SoQtComponent,
 *    SoDirectionalLight
 * 
 * 
 */ 

class INVENTORQT_API SoQtDirectionalLightEditor : public SoQtComponent {

  Q_OBJECT

    public:
  /**
   * Constructor.
   */
  SoQtDirectionalLightEditor( QWidget* parent = qApp->activeWindow(),
                              const char *name = NULL, 
                              SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoQtDirectionalLightEditor();

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
  SbBool      isAttached()    { return (dirLight != NULL); }

  /**
   * Sets new light values.
   */
  void setLight(const SoDirectionalLight &newLight);
  /**
   * Gets the current light values.
   */
  const SoDirectionalLight &getLight() const { return *dirLight; }

  /**
   * Adds lightChanged callback. This is an
   * additional way of using the directional light editor, by registering a callback
   * and setting the light.
   */
  void addLightChangedCallback (SoQtDirectionalLightEditorCB *f, 
                                void *userData = NULL)
    { callbackList->addCallback((SoCallbackListCB *) f, userData); }
  /**
   * Removes the lightChanged callback.
   */
  inline void removeLightChangedCallback (SoQtDirectionalLightEditorCB *f, 
                                          void *userData = NULL)
    { callbackList->removeCallback((SoCallbackListCB *) f, userData); }

  // Redefined here since there are two windows to deal with -
  // the color editor and the light manipulator
  virtual void show();
  virtual void hide();

 protected:
  QWidget* mgrWidget;   // topmost widget

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtDirectionalLightEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoQtDirectionalLightEditor( QWidget* parent,
                                const char *name, 
                                SbBool buildInsideParent, 
                                SbBool buildNow);

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
    
  // Open Inventor parts
  SoDirectionalLight*      dirLight;              // light we are editing
  SoSeparator*             root;                  // root of local scene graph
  SoSeparator*             litStuff;            // what's on display under the light
  SoPerspectiveCamera*     myCamera;
  SoCamera*                cameraToWatch;
  SoNodeSensor*            lightSensor;
  SoNodeSensor*            cameraSensor;
  SoDirectionalLightManip* dirLightManip;
  static char*             geomBuffer;
    
  // UI parts
  SoQtColorEditor     *colorEditor;
  SoQtColorSlider* intensitySlider;
  SoQtRenderArea*  renderArea;    
  //    SoQtClipboard     *clipboard;

  // Calbacks
  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SoCallbackList* callbackList;
    
  // Copy and updates
  void copyLight(SoDirectionalLight *dst, const SoDirectionalLight *src);
  void updateLocalComponents();

 private:

  // Build routines
  void constructorCommon(SbBool buildNow);
  QWidget* buildWidget(QWidget* parent);
  void activate();            // connects the sensor
  void deactivate();  // disconnects the sensor

  // Callbacks
  static void colorEditorCloseCB(void *userData, SoQtComponent *comp) ;
  static void colorEditorCB(void *, const SbColor *);
  static void dirLightManipCB(void *, SoDragger *);
  static void intensitySliderCB(void*, float);
  static void cameraSensorCB(SoQtDirectionalLightEditor *, SoSensor *);
  static void lightSensorCB(SoQtDirectionalLightEditor *, SoSensor *);
  static void dialogCloseCB(void*, SoQtComponent*);

  //qt variables
  QMenu* edit_menu;
  QAction* IDM_LEDT_COLOR_EDITOR;

  private Q_SLOTS:
  void visibilityChangeCB(SbBool visible);   
  void launchColorEditor();
  void copy();
  void paste();
  void showHelp();
  void keepOnTop();
  void slot_help();
};

#endif // _SO_QT_DIRECTIONAL_LIGHT_EDITOR_

