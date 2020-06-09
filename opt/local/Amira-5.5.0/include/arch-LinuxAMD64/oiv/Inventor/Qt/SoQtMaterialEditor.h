/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
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

#ifndef _SO_QT_MATERIAL_EDITOR_
#define _SO_QT_MATERIAL_EDITOR_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Qt/SoQtComponent.h>

#include <QtCore/QPointer>
class QMenu;
class QAction;
class SoBaseColor;
class SoQtColorEditor;
class QLabel;
class QRadioButton;
class QMenuBar;
class SoNodeSensor;
class SoSensor;
class SoDirectionalLight;
class SoMaterial;
class SoPathList;
class SoQtRenderArea;
class SoSelection;
class SoQtColorSlider;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;
class SoQtMaterialPalette;

class SoVRMLMaterial;   //for VSG enhancements
class SoNode;           //ditto
class SoSFColor;        //ditto

// callback function prototypes
typedef void SoQtMaterialEditorCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtMaterialEditor
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT Component which lets you edit a material interactively.
* 
* @ingroup Qt
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
*    SoQtComponent,
*    SoQtDirectionalLightEditor,
*    SoMaterial
* 
* 
*/ 

class INVENTORQT_API SoQtMaterialEditor : public SoQtComponent {
  
  Q_OBJECT
    
public:
  /** Update frequency.
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
  SoQtMaterialEditor( QWidget *parent = qApp->activeWindow(),
                      const char *name = NULL, 
                      SbBool buildInsideParent = TRUE );
  /**
   * Destructor.
   */
  ~SoQtMaterialEditor();
  
  /**
   * Attaches the editor to a material node and edits the material of the given
   * index.
   */
  void          attach( SoMaterial *material, int index = 0 );

  /**
   * Attaches the editor to a VRML material node and edits the material.
   */
  void                attach( SoVRMLMaterial *material );

  /**
   * Detaches the editor from the material node.
   */
  void          detach();

  /**
   * Returns TRUE if the editor is attached.
   */
  SbBool                isAttached() { return (material != NULL); }
  
  /**
   * Additional way of using the material editor, by registering a callback which
   * will be called whenever the material changes (check the @B UpdateFrequency @b
   * to find when the callbacks will be called).
   */
  inline void           addMaterialChangedCallback(
                                                   SoQtMaterialEditorCB *f, 
                                                   void *userData = NULL);
  /**
   * Removes the material changed callback.
   */
  inline void           removeMaterialChangedCallback(
                                                      SoQtMaterialEditorCB *f, 
                                                      void *userData = NULL);
  
  /**
   * Sets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  void  setUpdateFrequency(SoQtMaterialEditor::UpdateFrequency freq);

  /**
   * Gets the update frequency. See the @B UpdateFrequency @b enum declaration.
   */
  SoQtMaterialEditor::UpdateFrequency getUpdateFrequency()
    { return updateFreq; }
  
  // Redefine these since there are multiple windows -
  // the color editor, directional light editor, and this component
  virtual void          show();
  virtual void          hide();
  
  /**
   * Sets a new material value.
   */
  void                  setMaterial(const SoMaterial &mtl);

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
    return *localVRMLMaterial; } //VSG
#endif
  
  /**
   * Returns TRUE if attached material is a VRML material.
   */
  SbBool isAttachedVRML() { return (isVRMLMaterial); }
  
  /** 
   * Boolean indicating if the editor should be always on top of the other windows.
   */
  SbBool alwaysOnTop;

  /** 
   * Pointer to a material palette editor
   */
  SoQtMaterialPalette * m_pMaterialPalette;   

 protected:
  
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtMaterialEditor::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoQtMaterialEditor(
                       QWidget *parent,
                       const char *name, 
                       SbBool buildInsideParent, 
                       SbBool buildNow);
  
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;

  virtual bool eventFilter(QObject * object,QEvent *event);
  
 private:
  unsigned long nCurrEditId ;
  //unsigned long diamondButtonId[4];
  //unsigned long radioButtonId[4];
  QMenuBar *menubar ;
  
  
  // attach vars
  //SoMaterial          *material;  // material we are editing
  SoNode              *material;  // material we are editing
  SoMaterial          *imat;      // ditto
  SoVRMLMaterial      *vmat;      // ditto
  int                 index;        // material index number
  SoNodeSensor        *sensor;
  SoCallbackList      *callbackList;
  QPointer<QRadioButton>        diamondButtons[4], radioButtons[4];
  QPointer<SoQtButton>          acceptButton;
  SoQtMaterialEditor::UpdateFrequency   updateFreq;
  
  SbBool              isVRMLMaterial; // What kind of matl we are editing
  
  // widgets to edit the material
  QPointer<QWidget>    mgrWidget;     // topmost widget
  SoQtColorEditor     *colorEditor;
  SoQtColorSlider     *sliders[6];
  SbBool              changedIt[6];
#ifdef NOTYET
  SoQtMaterialList      *materialList;
#endif
  SbBool                ignoreCallback; // TRUE while callback should be ignored
  SbBool                openMaterialList;
  
  // copy/paste support
  //SoQtClipboard               *clipboard;
  
  // local scene vars
  SoQtRenderArea        *renderArea;
  SoMaterial          *localMaterial;       // local copy of the material
  SoVRMLMaterial      *localVRMLMaterial; // need for query
  SoDirectionalLight    *light0;
  SoDirectionalLight    *light1;
  SoBaseColor           *tileColor;
  SoSeparator           *root;
  
  long          activeColor;        // field which color editor edits
  
  // update the sliders/colorEditor based on the local material
  void                  updateLocalComponents();
  
  // update the colorEditor based on the activeColor flag
  void                  updateColorEditor(SbBool updateTitle = FALSE);
  
  // update a color slider (amb/diff/spec/emiss) based of a material color
  // (split the base color from the intensity).
  void                  updateColorSlider(SoQtColorSlider *, const float rgb[3]);
  
  // update a material field when a color slider changes.
  void                  updateMaterialColor(
                                            SoMFColor   *editMtlColor,
                                            SoMFColor   *localMtlColor,
                                            const float *rgb,
                                            float       intensity);
  void                  updateMaterialColor(
                                            SoSFColor   *editMtlColor,
                                            SoMFColor   *localMtlColor,
                                            const float *rgb,
                                            float       intensity);
  
  // copies mat2 onto mat1
  //void                copyMaterial(SoMaterial *mat1, int index1, 
  //                         const SoMaterial *mat2, int index2);
  void                  copyMaterial(SoNode *mat1, int index1, 
                                     const SoNode *mat2, int index2);
  
  // For each of the 6 sliders (or sets of sliders) sets the ignore flag of 
  // the material node being editted to FALSE if it has been changed.
  void          undoIgnoresIfChanged();
  
  // copy/paste support
  //static void         pasteDone(void *userData, SoPathList *pathList);
  
  // Callback routines from components
  static void materialListCB(void *, const SoMaterial *);
  static void colorEditorCB(void *, const SbColor *);
  static void ambientSliderCB(void *, float);
  static void diffuseSliderCB(void *, float);
  static void specularSliderCB(void *, float);
  static void emissiveSliderCB(void *, float);
  static void shininessSliderCB(void *, float);
  static void transparencySliderCB(void *, float);
  static void paletteEditorClosedCB(void*, SoQtComponent*);
  static void colorEditorCloseCB(void* userData, SoQtComponent*);
  static void dialogCloseCB(void* userData, SoQtComponent*);
  
  // Callback routines from Xt/Motif
  void          menuPick(int id);
  void          menuDisplay(QWidget*, SoQtMaterialEditor *, XtPointer);
  void          radioButtonPick(QWidget*, int, XtPointer);
  void          diamondButtonPick(QWidget*, int, XtPointer);
  
  // Sensor callbacks
  static void           sensorCB(void *, SoSensor *);
  
  // Build routines
  QWidget*                    buildWidget(QWidget* parent);
  QMenuBar*         buildPulldownMenu(QWidget* parent);
  QWidget*              buildControls(QWidget* parent);
  QWidget*              buildSlidersForm(QWidget* parent);
  
  void        activate();               // connects the sensor
  void        deactivate();             // disconnects the sensor
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
  
  QPointer<QMenu> edit;
  QAction* acCon, *acMan;
  
  private Q_SLOTS:
  
    void visibilityChangeCB(SbBool visible);
  
  void slot_mat_pal();
  void slot_continuous();
  void slot_manual();
  
  void slot_radioButton0();
  void slot_radioButton1();
  void slot_radioButton2();
  void slot_radioButton3();
  
  void slot_diamondButton0();
  void slot_diamondButton1();
  void slot_diamondButton2();
  void slot_diamondButton3();
  
  void acceptButtonCB();
  
  void slot_help();
  
};

// Inline functions
void
SoQtMaterialEditor::addMaterialChangedCallback(
                                               SoQtMaterialEditorCB *f, 
                                               void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoQtMaterialEditor::removeMaterialChangedCallback(
                                                  SoQtMaterialEditorCB *f, 
                                                  void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }


#endif // _SO_QT_MATERIAL_EDITOR_

