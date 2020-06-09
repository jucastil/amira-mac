/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Gambale (MMM yyyy)
**=======================================================================*/


#ifndef _SO_QT_MATERIAL_PALETTE_
#define _SO_QT_MATERIAL_PALETTE_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Qt/SoQtComponent.h>

#include <Inventor/STL/map>

#include <QtCore/QPointer>
class QScrollBar;
class QMenuBar;
class QLabel;
class QMenu;
class QAction;
class QLineEdit;

class SoBaseColor;
class SoQtColorEditor;
class SoNodeSensor;
class SoSensor;
class SoDirectionalLight;
class SoMaterial;
class SoPathList;
class SoQtPlaneViewer;
class SoSelection;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;
class SoOrthographicCamera;
class SoNode;
class SoSelection;
class SoPath;
class SoEventCallback;
class SoQtMaterialEditor;
class SoQtColorEditor;
class SoBoxHighlightRenderAction;

// callback function prototypes
typedef void SoQtMaterialPaletteCB(void *userData, const SoMaterial *mtl);

#ifndef _WIN32
#  include <sys/param.h>
#  if defined MAXPATHLEN
#    define MAX_PATH MAXPATHLEN
#  else
#    define MAX_PATH 256
#  endif
#endif 

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtMaterialPalette
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORQT_API SoQtMaterialPalette : public SoQtComponent {
  
  Q_OBJECT
    
    public:
  
  SoQtMaterialPalette(
                      QWidget *parent = NULL,
                      const char *name = NULL, 
                      SbBool buildInsideParent = TRUE);
  ~SoQtMaterialPalette();
  
  // attach the editor to the given node and edits the material
  // of the given index (default is the first material)
  void          attach(SoMaterial *material, int index = 0);
  void          detach();
  SbBool                isAttached()    { return (material != NULL); }
  
  //
  // Additional way of using the material editor, by registering a callback
  // and setting the material. At the time dictated by setUpdateFrequency
  // the callbacks will be called with the new material.
  //
  inline void           addMaterialChangedCallback(SoQtMaterialPaletteCB *f, 
                                                   void *userData = NULL);
  inline void           removeMaterialChangedCallback(SoQtMaterialPaletteCB *f, 
                                                      void *userData = NULL);
  
  // Redefine these since there are multiple windows -
  // the color editor, directional light editor, and this component
  virtual void          show();
  virtual void          hide();
  
  // Set new values for the material editor, or get current values
  void                  setMaterial(const SoMaterial &mtl);
  const SoMaterial &    getMaterial() const { return (*material); }
 public:
  void windowsPalette();
  
  SbBool alwaysOnTop;
  static void staticLocation2EventCB(void *userData,
                                     SoEventCallback *node);
  void location2Event(SoEventCallback *node);

  // @UNICODE_WARNING
  SoNONUNICODE void setPaletteBaseDir(const char * newBaseDir);

  void setPaletteBaseDir( const SbString newBaseDir );

  long getMaxDirCount() { return m_nMaxPathId; };
 protected: 
  void makePaletteMenuList(QMenuBar* menuBar);
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtMaterialPalette::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoQtMaterialPalette(
                        QWidget *parent,
                        const char *name, 
                        SbBool buildInsideParent, 
                        SbBool buildNow);
  
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
 private:
#ifndef _WIN32
  SbString     materialDir;
#endif

  unsigned long nCurrEditId ;
  QMenuBar* menubar;
  
  // attach vars
  SoMaterial            *material;  // material we are editing
  int                   index;      // material index number
  SoCallbackList        *callbackList;
  
  // widgets to edit the material
  QPointer<QWidget>                   mgrWidget;
  
  
  SbBool                ignoreCallback; // TRUE while callback should be ignored
  SbBool                openMaterialList;
  
  //local palette vars
  SoQtPlaneViewer       *paletteRenderArea;
  SoSelection                   *paletteRoot;
  SoOrthographicCamera * m_pCamera;
  static void staticSelectionCB(void *userData, SoPath *path);
  void                          selectionCB(SoPath * path);
  
  SoSelection                   *makePalette();
  void                              resetPalette();  
  SoSeparator                   *makeRow(SoNode * aShape,long * nodeCnt,SbBool reset = FALSE);
  char            currentMaterialPath[MAX_PATH];
  SbString        getMaterialDir();
  void            setMaterialDir(const SbString& dirPath);
  SbBool          saveMaterial(const SbString& fName);  
  void            changeMaterialPath( QAction* id );

  QPointer<QScrollBar>     m_hScrollBar;
  QPointer<QLabel>         m_hStatusText;
  QPointer<QLabel>         m_hPaletteName;
  int             m_nMaxPathId;
  void            adjustVScrollInfo(long rows);
  
  SoBoxHighlightRenderAction * m_pHighlightAction;
  
  
  SoQtMaterialEditor            *m_pMaterialEditor;
  SoQtColorEditor                   *m_pColorEditor;
  // keep the menu items around so we can update them before menu display
  QWidget*                *menuItemsList;
  
  long          activeColor;        // field which color editor edits
  
  // copies mat2 onto mat1
  void    copyMaterial(SoMaterial *mat1, int index1, 
                       const   SoMaterial *mat2, int index2);
  
  // copy/paste support
  //static void         pasteDone(void *userData, SoPathList *pathList);
  
  // Callback routines from components
  static void           materialListCB(void *, const SoMaterial *);
  static void           dialogCloseCB(void*, SoQtComponent*);
  static void           colorEditorCloseCB(void*, SoQtComponent*);
  // Callback routines from Xt/Motif
  void          menuPick(QWidget*, int, void *);
  void          menuDisplay(QWidget*, SoQtMaterialPalette *, XtPointer);
  
  // Build routines
  QWidget*              buildWidget(QWidget *parent);
  QMenuBar*   buildPulldownMenu(QWidget *parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

  //special qt stuffs
  QPointer<QMenu> palette;
  QAction* acPal;
  std::map<int, QAction*> m_paletteMenuIdsMap;
  QDialog * materialPath;
  QLineEdit *line;

  private Q_SLOTS:
  
    void slot_color();
  void slot_mat();
  void slot_palette( QAction* id );
  void slot_scroll_view(int);
  void browsePalletteBaseDir();
  void slot_ok();
  void slot_browse();
  void slot_help();
  void slot_copy();

};

// Inline functions
void
SoQtMaterialPalette::addMaterialChangedCallback(SoQtMaterialPaletteCB *f, 
                                                void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoQtMaterialPalette::removeMaterialChangedCallback(SoQtMaterialPaletteCB *f, 
                                                   void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#endif // _SO_QT_MATERIAL_PALETTE_


