/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_ITEM_LEGEND_EDITOR_H
#define _POXT_ITEM_LEGEND_EDITOR_H

#include <MeshViz/graph/editors/PoXtLegendEditor.h>

/**
 * @DTEXT  Class for items legend editors.
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtItemLegendEditor
: public PoXtLegendEditor
{

 public:

  enum ItemLegendMask
  {
    NO_ITEM_MASK     = 0x00000000,

    START            = 0x00000001,
    END              = 0x00000002,
    BOX_VISIBILITY   = 0x00000004,
    LINE_VISIBILITY  = 0x00000008,
    MARK_VISIBILITY  = 0x00000010,

    ALL_ITEM_MASK = START | END | BOX_VISIBILITY 
    | LINE_VISIBILITY | MARK_VISIBILITY
  } ;



  /**
   * Constructor.
   */
  PoXtItemLegendEditor(SoWidget parent=NULL, 
                       const char * name=NULL,
                       SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  virtual ~PoXtItemLegendEditor();

  /**
   * Sets editing filters defining which item legend attributes will be displayed 
   * in the editor. (By default inclusionMask = ALL_ITEM_MASK and 
   * exclusionMask = NO_ITEM_MASK). 
   */
  void setItemLegendFilter(unsigned long inclusionMask,
                           unsigned long exclusionMask);

  /**
   * Gets editing filters defining which item legend attributes will be displayed 
   * in the editor.
   */
  void getItemLegendFilter(unsigned long & inclusionMask,
                           unsigned long & exclusionMask) const;
 protected:
  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setFilter();
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  virtual void copyLegendFields(PoLegend * dest, PoLegend * source);
  virtual void updateLegendFromXtElements ();
  
  virtual int getMenuItems();
  
  // Attribute
  unsigned long   _incItemMask;
  unsigned long   _excItemMask;
  
 private:
  int _classMenusNb;
  SbBool _isItemSet;
  
  // Callbacks for PoXtDialog
  static void itemElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_ITEM_LEGEND_EDITOR_H

