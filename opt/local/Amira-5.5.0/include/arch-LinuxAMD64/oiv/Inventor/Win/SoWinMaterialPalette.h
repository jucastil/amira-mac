/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_MATERIAL_PALETTE_
#define _SO_WIN_MATERIAL_PALETTE_

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
class SoPathList;
class SoWinRenderArea;
class SoSelection;
class SoWinColorSlider;
class SoMFColor;
class SbColor;
class SoBase;
class SoSeparator;
class SoWinPlaneViewer;
class SoOrthographicCamera;
class SoNode;
class SoSelection;
class SoPath;
class SoEventCallback;
class SoWinMaterialEditor;
class SoWinColorEditor;
class SoBoxHighlightRenderAction;
#include <winbase.h>

// callback function prototypes
typedef void SoWinMaterialPaletteCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMaterialPalette
//
//  This editor lets you interactively edit a material
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinMaterialPalette : public SoWinComponent {
 public:
    
  SoWinMaterialPalette(
                       SoWidget parent = NULL,
                       const char *name = NULL, 
                       SbBool buildInsideParent = TRUE);
  ~SoWinMaterialPalette();
    
  // attach the editor to the given node and edits the material
  // of the given index (default is the first material)
  void                attach(SoMaterial *material, int index = 0);
  void                detach();
  SbBool              isAttached()    { return (material != NULL); }
    
  //
  // Additional way of using the material editor, by registering a callback
  // and setting the material. At the time dictated by setUpdateFrequency
  // the callbacks will be called with the new material.
  //
  inline void         addMaterialChangedCallback(
                                                 SoWinMaterialPaletteCB *f, 
                                                 void *userData = NULL);
  inline void         removeMaterialChangedCallback(
                                                    SoWinMaterialPaletteCB *f, 
                                                    void *userData = NULL);
    
  // Redefine these since there are multiple windows -
  // the color editor, directional light editor, and this component
  virtual void        show();
  virtual void        hide();
    
  // Set new values for the material editor, or get current values
  void                setMaterial(const SoMaterial &mtl);
  const SoMaterial &  getMaterial() const { return (*material); }
 public:
  void windowsPalette();

  SbBool alwaysOnTop;
  static void staticLocation2EventCB(void *userData,
                                     SoEventCallback *node);
  void location2Event(SoEventCallback *node);

  void browsePalletteBaseDir();
  void setPaletteBaseDir(LPCTSTR newBaseDir);
  long getMaxDirCount() { return m_nMaxPathId; };
 protected:
  HWND m_fileBrowser;

  static HKEY tgsRegKey;

  void makePaletteMenuList(HMENU menuBar);

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinMaterialPalette::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinMaterialPalette(
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
  HMENU menubar ;


  static WBOOL CALLBACK mgrDlgProc( Hwnd hdlg, UINT message,
                                    WPARAM wParam, LPARAM lParam );
  static void onCommand(
                        Hwnd hdlg,
                        int id,
                        Hwnd hCtrl,
                        UINT codeNotify ) ;
        
  void handleMenu(SoWinMaterialPalette *p,
                  int id ) ;

  void initPlacement() ;
  // attach vars
  SoMaterial          *material;  // material we are editing
  int                 index;      // material index number
  SoCallbackList      *callbackList;
    
  // widgets to edit the material
  SoWidget              mgrWidget;      // topmost widget


  SbBool              ignoreCallback; // TRUE while callback should be ignored
  SbBool              openMaterialList;
    
  // copy/paste support
  SoWinClipboard              *clipboard;
    
  //local palette vars
  SoWinPlaneViewer        *paletteRenderArea;
  SoSelection                     *paletteRoot;
  SoOrthographicCamera * m_pCamera;
  static void staticSelectionCB(void *userData, SoPath *path);
  void                            selectionCB(SoPath * path);

  SoSelection                     *makePalette();
  void                            resetPalette();
  SoSeparator                     *makeRow(SoNode * aShape,long * nodeCnt,SbBool reset = FALSE);
  LPCTSTR                         getMaterialDir();
  void                            setMaterialDir(LPCTSTR dirPath);
  SbBool                          saveMaterial(LPCTSTR fName);
  char                currentMaterialPath[MAX_PATH];
  char*                m_materialPath;
  void                changeMaterialPath(UINT id);
  SoWidget              m_hScrollBar;
  SoWidget                          m_hStatusText;
  SoWidget                          m_hPaletteName;
  int                 m_nMaxPathId;
  void                adjustVScrollInfo(long rows);
  void                scrollCamera(int nScrollCode, short int nPos);

  SoBoxHighlightRenderAction * m_pHighlightAction;

    
  SoWinMaterialEditor             *m_pMaterialEditor;
  SoWinColorEditor                *m_pColorEditor;
  // keep the menu items around so we can update them before menu display
  SoWidget              *menuItemsList;
    
  long                activeColor;        // field which color editor edits
    
  // copies mat2 onto mat1
  void                copyMaterial(SoMaterial *mat1, int index1, 
                                   const SoMaterial *mat2, int index2);

  // copy/paste support
  static void         pasteDone(void *userData, SoPathList *pathList);

  // Callback routines from components
  static void         materialListCB(void *, const SoMaterial *);
  // Callback routines from Xt/Motif
  void                menuPick(SoWidget, int, XmAnyCallbackStruct *);
  void                menuDisplay(SoWidget, SoWinMaterialPalette *, XtPointer);

  // Build routines
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              buildPulldownMenu(SoWidget parent);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

// Inline functions
void
SoWinMaterialPalette::addMaterialChangedCallback(
                                                 SoWinMaterialPaletteCB *f, 
                                                 void *userData)
{ callbackList->addCallback((SoCallbackListCB *) f, userData); }

void
SoWinMaterialPalette::removeMaterialChangedCallback(
                                                    SoWinMaterialPaletteCB *f, 
                                                    void *userData)
{ callbackList->removeCallback((SoCallbackListCB *) f, userData); }

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_MATERIAL_PALETTE_


