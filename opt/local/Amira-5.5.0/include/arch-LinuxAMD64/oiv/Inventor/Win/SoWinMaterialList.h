/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_MATERIAL_LIST_H_
#define _SO_WIN_MATERIAL_LIST_H_

#ifdef _WIN32
// Not yet implemented for _WIN32
#else

#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/nodes/SoMaterial.h>

// callback function prototypes
typedef void SoWinMaterialListCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMaterialList
//
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTORW_API SoWinMaterialList : public SoWinComponent {
 public:
  // pass the home directory of the material palettes as dir
  SoWinMaterialList(
                    SoWidget parent = NULL,
                    const char *name = NULL, 
                    SbBool buildInsideParent = TRUE, 
                    const char *dir = NULL);
  ~SoWinMaterialList();

  // Callbacks - register functions that will be called whenever the user
  // chooses a new material from the list.
  // (This component cannot be attached to a database - it is read only)
  void    addCallback(
                      SoWinMaterialListCB *f,
                      void *userData = NULL)
    { callbackList->addCallback((SoCallbackListCB *) f, userData);}

  void    removeCallback(
                         SoWinMaterialListCB *f,
                         void *userData = NULL)
    { callbackList->removeCallback((SoCallbackListCB *) f, userData); }
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinMaterialList::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinMaterialList(
                      SoWidget parent,
                      const char *name, 
                      SbBool buildInsideParent, 
                      const char *dir, 
                      SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  // Build routines
  SoWidget              buildWidget(SoWidget parent);
  SoWidget              buildPulldownMenu(SoWidget parent);
    
 private:
  char                *materialDir;   // the parent directory of materials
  SoCallbackList      *callbackList;  // funcs to invoke when a mtl is picked
  SbPList             menuItems;      // Widgets
  SbPList             mtlPalettes;    // list of palettes
  SbPList             palette;        // the current palette
  int                 curPalette;     // index into mtlPalettes
  SoWidget              mtlList;        // the Motif list of materials

  // Fill up the mtlList with a new palette
  void                fillInMaterialList();
  SbBool              setupPalettes();

  // Callback routines from Xt/Motif
  static void         menuPick(SoWidget, int, XtPointer);
  static void         listPick(SoWidget, SoWinMaterialList *, XtPointer);

  // this is called by both constructors
  void constructorCommon(const char *dir, SbBool buildNow);
};

#endif //_WIN32

#endif // _SO_WIN_MATERIAL_LIST_H_
