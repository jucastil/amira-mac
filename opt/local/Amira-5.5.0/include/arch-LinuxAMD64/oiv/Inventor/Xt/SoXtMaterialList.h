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


#ifdef _WIN32
#  include <Inventor/Win/SoWinMaterialList.h>
#else // _WIN32

#ifndef _SO_XT_MATERIAL_LIST_H_
#define _SO_XT_MATERIAL_LIST_H_

#include <X11/Intrinsic.h>
#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/nodes/SoMaterial.h>

// callback function prototypes
typedef void SoXtMaterialListCB(void *userData, const SoMaterial *mtl);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMaterialList
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component which lets you edit a material interactively.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class is used to choose an SoMaterial from palettes of predefined materials
 *   (for example, gold, silver, or bronze from the metal palette; emerald, pearl, or
 *   ruby from the stones palette). The chosen material is passed to callback
 *   functions registered with this component.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Material List !! 
 *   !!------------------------------------------------ 
 *   *IvMaterialListTitle.labelString: Material List 
 *   *IvMaterialListeIconTitle.labelString: Mat List 
 *   *IvMLMenuBar*IvPalettes.labelString: Palettes 
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoCallbackList,
 *    SoMaterial,
 *    SoXtMaterialEditor
 * 
 * 
 */ 

class INVENTORXT_API SoXtMaterialList : public SoXtComponent {
 public:
  /**
   * The constructor is passed a directory name which serves as the home directory
   * for the material palettes. You can have any number of palettes in this
   * directory. A palette is a subdirectory that contains Open Inventor data files,
   * where each file describes one material. Predefined Open Inventor materials are
   * found in $OIVHOME/data/materials.
   */
  SoXtMaterialList(
                   SoWidget parent = NULL,
                   const char *name = NULL, 
                   SbBool buildInsideParent = TRUE, 
                   const char *dir = NULL);
  /**
   * Destructor.
   */
  ~SoXtMaterialList();

  /**
   * Registers functions that will be called whenever the user chooses a new material
   * from the list. Each callback when invoked will be passed the userData pointer,
   * along with a pointer to the newly selected material.
   */
  void    addCallback(
                      SoXtMaterialListCB *f,
                      void *userData = NULL)
    { callbackList->addCallback((SoCallbackListCB *) f, userData);}

  /**
   * Removes callback.
   */
  void    removeCallback(
                         SoXtMaterialListCB *f,
                         void *userData = NULL)
    { callbackList->removeCallback((SoCallbackListCB *) f, userData); }
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtMaterialList::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMaterialList(
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
  static void         listPick(SoWidget, SoXtMaterialList *, XtPointer);

  // this is called by both constructors
  void constructorCommon(const char *dir, SbBool buildNow);

};

#endif // _SO_XT_MATERIAL_LIST_H_

#endif // _WIN32


