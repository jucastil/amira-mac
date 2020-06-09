/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
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

#ifndef _SO_WIN_MATERIAL_EDITOR_
#define _SO_WIN_MATERIAL_EDITOR_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/sys/port.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Win/SoWinComponent.h>

class SoBaseColor;
class SoWinClipboard;
class SoWinColorEditor;
class SoNodeSensor;
class SoSensor;
class SoDirectionalLight;
class SoMaterial;
#ifdef NOTYET
class SoWinMaterialList;
#endif
class SoPathList;
class SoWinRenderArea;
class SoSelection;
class SoWinColorSlider;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;
class SoWinMaterialPalette;

class SoVRMLMaterial;   //for VSG enhancements
class SoNode;           //ditto
class SoSFColor;        //ditto

// callback function prototypes
/** 
 * [OIV-WRAPPER NAME{EditorCB}] 
 */
typedef void SoWinMaterialEditorCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMaterialEditor
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Component which lets you edit a material interactively.
 * 
 * @ingroup Win
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
 * @SEE_ALSO
 *    SoWinComponent,
 *    SoWinDirectionalLightEditor,
 *    SoMaterial
 * 
 * 
 */ 

class INVENTORW_API SoWinMaterialEditor : public SoWinComponent {
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
    AFTER_ACCEPT,
  };
    
  /**
   * Constructor.
   */
  SoWinMaterialEditor(
                      SoWidget parent = NULL,
                      const char *name = NULL, 
                      SbBool buildInsideParent = TRUE);
  /**
   * Destructor.
   */
  virtual ~SoWinMaterialEditor();
    
  /**
   * Attaches the editor to a material node and edits the material of the given
   * index.
   */
  void                attach( SoMaterial *material, int index = 0 );
  /**
   * Attaches the editor to a VRML material node and edits the material.
   */
  void                attach( SoVRMLMaterial *material );
  /**
   * Detaches the editor from the material node.
   */
  void                detach();
  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool              isAttached() { return (material != NULL); }
    
  /**
   * Additional way of using the material editor, by registering a callback which
   * will be called whenever the material changes (check the @B UpdateFrequency @b
   * to find when the callbacks will be called).
   * [OIV-WRAPPER EVENT_NAME{MaterialChanged}]
   */
  inline void         addMaterialChangedCallback(
                                                 SoWinMaterialEditorCB *f, 
                                                 void *userData = NULL);
  /**
   * Removes the material changed callback.
   * [OIV-WRAPPER EVENT_NAME{MaterialChanged}]
   */
  inline void         removeMaterialChangedCallback(
                                                    SoWinMaterialEditorCB *f, 
                                                    void *userData = NULL);
    
  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void        setUpdateFrequency(SoWinMaterialEditor::UpdateFrequency freq);
  /**
   * Gets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  SoWinMaterialEditor::UpdateFrequency getUpdateFrequency()
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
   * Sets a new VRML material value.
   */
  void                setMaterial(const SoVRMLMaterial &mtl);
  /**
   * Gets the current material value.
   */
  const SoMaterial     & getMaterial()     const { return *localMaterial; }
#ifdef NOTYET
  const SoVRMLMaterial & getVRMLMaterial() const
    { copyMaterial( localVRMLMaterial,0,localMaterial,0);
    return *localVRMLMaterial; }
#endif

  /**
   * Returns TRUE if attached material is a VRML material.
   */
  SbBool isAttachedVRML() { return (isVRMLMaterial); }

  SbBool alwaysOnTop;
  SoWinMaterialPalette * m_pMaterialPalette;    
 protected:


  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinMaterialEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinMaterialEditor(
                        SoWidget parent,
                        const char *name, 
                        SbBool buildInsideParent, 
                        SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
 private:
  unsigned long nCurrEditId ;
  unsigned long diamondButtonId[4] ;
  unsigned long radioButtonId[4] ;
  HMENU menubar ;

  void layoutAccept() ;

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

  void handleButtons(SoWinMaterialEditor *p,
                     SoWidget hCtrl,
                     int id,
                     UINT codeNotify) ;
        
  void handleMenu(SoWinMaterialEditor *p,
                  int id ) ;

  void initPlacement() ;


  // attach vars
  //SoMaterial                *material;  // material we are editing
  SoNode              *material;  // material we are editing
  SoMaterial          *imat;      // ditto
  SoVRMLMaterial      *vmat;      // ditto
  int                 index;      // material index number
  SoNodeSensor        *sensor;
  SoCallbackList      *callbackList;
  SoWidget              acceptButton, diamondButtons[4], radioButtons[4];
  SoWinMaterialEditor::UpdateFrequency        updateFreq;

  SbBool              isVRMLMaterial; // What kind of matl we are editing
    
  // widgets to edit the material
  SoWidget                      mgrWidget;      // topmost widget
  SoWinColorEditor    *colorEditor;
  SoWinColorSlider    *sliders[6];
  SbBool              changedIt[6];
#ifdef NOTYET
  SoWinMaterialList   *materialList;
#endif
  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SbBool              openMaterialList;
  static void         colorEditorCloseCB(void *, SoWinComponent *);
  static void         materialListCloseCB(void *, SoWinComponent *);
    
  // copy/paste support
  SoWinClipboard              *clipboard;
    
  // local scene vars
  SoWinRenderArea     *renderArea;
  SoMaterial          *localMaterial;     // local copy of the material
  SoVRMLMaterial      *localVRMLMaterial; // need for query
  SoDirectionalLight  *light0;
  SoDirectionalLight  *light1;
  SoBaseColor         *tileColor;
  SoSeparator         *root;
    
  long                activeColor;        // field which color editor edits
    
  // update the sliders/colorEditor based on the local material
  void                updateLocalComponents();
    
  // update the colorEditor based on the activeColor flag
  void                updateColorEditor(SbBool updateTitle = FALSE);
    
  // update a color slider (amb/diff/spec/emiss) based of a material color
  // (split the base color from the intensity).
  void                updateColorSlider(SoWinColorSlider *, const float rgb[3]);
    
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
  //void              copyMaterial(SoMaterial *mat1, int index1, 
  //                         const SoMaterial *mat2, int index2);
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
  void                menuPick(SoWidget, int, XmAnyCallbackStruct *);
  void                menuDisplay(SoWidget, SoWinMaterialEditor *, XtPointer);
  void                radioButtonPick(SoWidget, int, XtPointer);
  void                diamondButtonPick(SoWidget, int, XtPointer);

  static void         acceptButtonCB(SoWidget, SoWinMaterialEditor *, XtPointer);
    
  // Sensor callbacks
  static void         sensorCB(void *, SoSensor *);

  // Build routines
  SoWidget              buildWidget(SoWidget parent);
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
INVENTORW_API void
SoWinMaterialEditor::addMaterialChangedCallback(
                                                SoWinMaterialEditorCB *f, 
                                                void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

INVENTORW_API void
SoWinMaterialEditor::removeMaterialChangedCallback(
                                                   SoWinMaterialEditorCB *f, 
                                                   void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_MATERIAL_EDITOR_

