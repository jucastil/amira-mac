/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_AUTO_VALUE_LEGEND_EDITOR_H
#define _POXT_AUTO_VALUE_LEGEND_EDITOR_H

#include <MeshViz/graph/editors/PoXtValueLegendEditor.h>

/**
 * @DTEXT  Abstract class for auto value legend editors. 
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtAutoValueLegendEditor
: public PoXtValueLegendEditor
{

 public:

  enum AutoValueLegendMask
  {
    NO_AUTO_VALUE_MASK = 0x00000000,

    START = 0x00000001,
    END   = 0x00000002,

    ALL_AUTO_VALUE_MASK = START | END
  } ;



  /**
   * Destructor.
   */
  virtual ~PoXtAutoValueLegendEditor();

  /**
   * Sets editing filters defining which auto value legend attributes will be 
   * displayed in the editor. (By default inclusionMask = ALL_AUTO_VALUE_LEGEND_MASK
   * and exclusionMask = NO_AUTO_VALUE_LEGEND_MASK).
   */
  void setAutoValueLegendFilter(unsigned long inclusionMask,
                                unsigned long exclusionMask);

  /**
   * Gets editing filters defining which auto value legend attributes will be 
   * displayed in the editor. 
   */
  void getAutoValueLegendFilter(unsigned long & inclusionMask,
                                unsigned long & exclusionMask) const;
 protected:
  PoXtAutoValueLegendEditor(SoWidget parent=NULL, 
                            const char * name=NULL,
                            SbBool buildInsideParent=TRUE);
  
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
  
  // Attributes
  unsigned long   _incAutoValueMask;
  unsigned long   _excAutoValueMask;
  
 private:
  int _classMenusNb;
  SbBool _isAutoValueSet;
  
  // Callbacks for PoXtDialog
  static void autoValueElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif

