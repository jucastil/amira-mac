/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


////////////////////////////////////////////////////////////////////////
//
// Extended to support VRML 2.0 for Inventor version 3.0
//
// Mike Heck
//
// The "attach" and "setMaterial" methods are overloaded to allow passing
// in an SoVRMLMaterial node.  There is a new method "isAttachedVRML".
//
// This extension does not force any changes in existing applications.
// In order to attach to the material affecting a VRML 2.0 shape, existing
// applications will need to enhance their attach logic (see SceneViewer).
//
//////////////////////////////////////////////////////////////////////////

#ifdef SOQT
#  include <Inventor/Qt/SoQtMaterialEditor.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinMaterialEditor.h>
#else // _WIN32

#ifndef _SO_XT_MATERIAL_EDITOR_
#define _SO_XT_MATERIAL_EDITOR_

#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>

class SoBaseColor;
class SoXtClipboard;
class SoXtColorEditor;
class SoNodeSensor;
class SoSensor;
class SoDirectionalLight;
class SoMaterial;
class SoXtMaterialList;
class SoPathList;
class SoXtRenderArea;
class SoSelection;
class SoXtColorSlider;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;
class SoVRMLMaterial;
class SoNode;
class SoSFColor;

// callback function prototypes
typedef void SoXtMaterialEditorCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMaterialEditor
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component which lets you edit a material interactively.
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   This class is used to edit the material properties of an SoMaterial node. The
 *   editor can also directly be used using callbacks instead of attaching it to a
 *   node. The component consists of a render area displaying a test sphere, some
 *   sliders, a set of radio buttons, and a menu. The sphere displays the current
 *   material being edited. There is one slider for each material coefficient. Those
 *   fields are ambient, diffuse, specular, emissive (all of which are colors); and
 *   transparency and shininess (which are scalar values). A color editor can be
 *   opened to edit the color slider base color. A material list displays palettes of
 *   predefined materials from which to choose.
 *
 *   The editor can currently be attached to only one material at a time. Attaching
 *   two different materials will automatically detach the first one before attaching
 *   the second.
 *
 * @RESOURCES
 * <PRE>
 *   !!------------------------------------------------
 *   !! Material Editor !!
 *   !!------------------------------------------------
 *   *IvMaterialEditorTitle.labelString: Material Editor
 *   *IvMaterialEditorIconTitle.labelString: Mat Editor
 *   *IvMaterialAmbientTitle.labelString: Material Ambient Color
 *   *IvMaterialDiffuseTitle.labelString: Material Diffuse Color
 *   *IvMaterialSpecularTitle.labelString: Material Specular Color
 *   *IvMaterialEmissiveTitle.labelString: -Material Emissive Color
 *   *IvMaterialEditorMaterial.labelString: Material /
 *   *IvMaterialEditorAmb.labelString: Amb /
 *   *IvMaterialEditorDiff.labelString: Diff /
 *   *IvMaterialEditorSpec.labelString: Spec /
 *   *IvMaterialEditorEmis.labelString: Emis /
 *   *IvMaterialEditorColor.labelString: Color
 *   *IvMEMenuBar.IvEdit.labelString: Edit
 *   *IvMEMenuBar*IvEditPullDown.IvMaterialList.labelString: Material List
 *   *IvMEMenuBar*IvEditPullDown.IvContinuous.labelString: Continuous
 *   *IvMEMenuBar*IvEditPullDown.IvManual.labelString: Manual
 *   *IvMEMenuBar*IvEditPullDown.IvCopy.labelString: Copy
 *   *IvMEMenuBar*IvEditPullDown.IvPaste.labelString: Paste
 *   *IvMEMenuBar*IvEditPullDown.IvHelp.labelString: Help
 *   *IvControls.IvEditColor.labelString: Edit Color
 *   *IvsliderForm.IvtextForm.IvAmb.labelString: Amb:
 *   *IvsliderForm.IvtextForm.IvDiff.labelString: Diff
 *   *IvsliderForm.IvtextForm.IvSpec.labelString: Spec
 *   *IvsliderForm.IvtextForm.IvEmis.labelString: Emis
 *   *IvsliderForm.IvtextForm.IvShininess.labelString: Shininess
 *   *IvsliderForm.IvtextForm.IvTransp.labelString: Transp:
 *   *IvMETop.IvAccept.labelString: Accept
 * </PRE>
 *
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoXtMaterialList,
 *    SoXtDirectionalLightEditor,
 *    SoMaterial
 *
 *
 */

class INVENTORXT_API SoXtMaterialEditor : public SoXtComponent {
 public:
    /**
    * UpdateFrequency is how often new values should be sent
    * to the node or the callback routine. 
    */
  enum UpdateFrequency {
    /**
     *  Send updates with every mouse motion
     */
    CONTINUOUS,
    /**
     *  Only send updates after user hits accept button
     */
    AFTER_ACCEPT
  };

  /**
   * Constructor.
   */
  SoXtMaterialEditor(
                     SoWidget parent = NULL,
                     const char *name = NULL,
                     SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  ~SoXtMaterialEditor();

  /**
   * Attaches the editor to a material node and edits the material of the given
   * index.
   */
  void attach(SoMaterial *material, int index = 0);

  /**
   * Attaches the editor to a VRML material node and edits the material.
   */
  void attach(SoVRMLMaterial *material);

  /**
   * Detaches the editor from the material node.
   */
  void                detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool              isAttached()    { return (material != NULL); }

  /**
   * Additional way of using the material editor, by registering a callback which
   * will be called whenever the material changes (check the @B UpdateFrequency @b
   * to find when the callbacks will be called).
   */
  inline void         addMaterialChangedCallback(
                                                 SoXtMaterialEditorCB *f,
                                                 void *userData = NULL);
  /**
   * Removes the material changed callback.
   */
  inline void         removeMaterialChangedCallback(
                                                    SoXtMaterialEditorCB *f,
                                                    void *userData = NULL);

  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void        setUpdateFrequency(SoXtMaterialEditor::UpdateFrequency freq);
  /**
   * Gets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  SoXtMaterialEditor::UpdateFrequency getUpdateFrequency()
    { return updateFreq; }

  // Redefine these since there are multiple windows -
  // the color editor, directional light editor, and this component
  virtual void        show();
  virtual void        hide();

  /**
   * Sets a new material value.
   */
  void                setMaterial(const SoMaterial &mtl);

  /**
   * Set a new VRML material value.
   */
  void setMaterial(const SoVRMLMaterial &mtl);

  /**
   * Gets the current material value.
   */
  const SoMaterial &  getMaterial() const { return *localMaterial; }

  /**
   * Returns TRUE if attached material is a VRML material.
   */
  SbBool isAttachedVRML() { return (isVRMLMaterial); }

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtMaterialEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMaterialEditor(
                       SoWidget parent,
                       const char *name,
                       SbBool buildInsideParent,
                       SbBool buildNow);

  SoWidget                  buildWidget(SoWidget parent);

  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;

 private:
  // attach vars
  SoNode              *material;  // material we are editing
  SoMaterial          *imat;
  SoVRMLMaterial      *vmat;
  SbBool              isVRMLMaterial; // What kind of matl we are editing
  int                 index;      // material index number
  SoNodeSensor        *sensor;
  SoCallbackList      *callbackList;
  SoWidget              acceptButton, diamondButtons[4], radioButtons[4];
  SoXtMaterialEditor::UpdateFrequency updateFreq;

  // widgets to edit the material
  SoWidget              mgrWidget;      // topmost widget
  SoXtColorEditor     *colorEditor;
  SoXtColorSlider     *sliders[6];
  SbBool              changedIt[6];
  SoXtMaterialList    *materialList;
  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SbBool              openMaterialList;
  static void         colorEditorCloseCB(void *, SoXtComponent *);
  static void         materialListCloseCB(void *, SoXtComponent *);

  // copy/paste support
  SoXtClipboard       *clipboard;

  // local scene vars
  SoXtRenderArea      *renderArea;
  SoMaterial          *localMaterial;     // local copy of the material
  SoDirectionalLight  *light0;
  SoDirectionalLight  *light1;
  SoBaseColor         *tileColor;
  SoSeparator         *root;

  // keep the menu items around so we can update them before menu display
  SoWidget              *menuItemsList;

  int32_t             activeColor;        // field which color editor edits

  // update the sliders/colorEditor based on the local material
  void                updateLocalComponents();

  // update the colorEditor based on the activeColor flag
  void                updateColorEditor(SbBool updateTitle = FALSE);

  // update a color slider (amb/diff/spec/emiss) based of a material color
  // (split the base color from the intensity).
  void                updateColorSlider(SoXtColorSlider *, const float rgb[3]);

  // update a material field when a color slider changes.
  void                updateMaterialColor(
                                          SoMFColor   *editMtlColor,
                                          SoMFColor   *localMtlColor,
                                          const float *rgb,
                                          float       intensity);
  void                updateMaterialColor(
                                          SoSFColor   *editMtlColor,
                                          SoMFColor   *localMtlColor,
                                          const float *rgb,
                                          float       intensity);

  // copies mat2 onto mat1
  void                copyMaterial(SoNode *mat1, int index1,
                                   const SoNode *mat2, int index2);

  // For each of the 6 sliders (or sets of sliders) sets the ignore flag of
  // the material node being editted to FALSE if it has been changed.
  void                undoIgnoresIfChanged();

  // copy/paste support
  static void         pasteDone(void *userData, SoPathList *pathList);

  // Callback routines from components
  static void         materialListCB(void *, const SoMaterial *);
  static void         colorEditorCB(void *, const SbColor *);
  static void         ambientSliderCB(void *, float);
  static void         diffuseSliderCB(void *, float);
  static void         specularSliderCB(void *, float);
  static void         emissiveSliderCB(void *, float);
  static void         shininessSliderCB(void *, float);
  static void         transparencySliderCB(void *, float);

  // Callback routines from Xt/Motif
  static void         menuPick(SoWidget, int, XmAnyCallbackStruct *);
  static void         menuDisplay(SoWidget, SoXtMaterialEditor *, XtPointer);
  static void         radioButtonPick(SoWidget, int, XtPointer);
  static void         diamondButtonPick(SoWidget, int, XtPointer);
  static void         acceptButtonCB(SoWidget, SoXtMaterialEditor *, XtPointer);

  // Sensor callbacks
  static void         sensorCB(void *, SoSensor *);

  // Build routines
  SoWidget              buildPulldownMenu(SoWidget parent);
  SoWidget              buildControls(SoWidget parent);
  SoWidget              buildSlidersForm(SoWidget parent);

  static void visibilityChangeCB(void *pt, SbBool visible);
  void        activate();             // connects the sensor
  void        deactivate();           // disconnects the sensor

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};


// Inline functions
void
SoXtMaterialEditor::addMaterialChangedCallback(
                                               SoXtMaterialEditorCB *f,
                                               void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoXtMaterialEditor::removeMaterialChangedCallback(
                                                  SoXtMaterialEditorCB *f,
                                                  void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#endif // _SO_XT_MATERIAL_EDITOR_

#endif // _WIN32


