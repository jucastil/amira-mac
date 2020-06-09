/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_LINEAR_VALUE_LEGEND_EDITOR_H
#define _POXT_LINEAR_VALUE_LEGEND_EDITOR_H

#include <MeshViz/graph/editors/PoXtAutoValueLegendEditor.h>

/**
 * @DTEXT  Class for linear auto value legend editors. 
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtLinearValueLegendEditor
: public PoXtAutoValueLegendEditor
{

 public:

  enum LinearValueLegendMask
  {
    NO_LINEAR_VALUE_MASK  = 0x00000000,
    
    VALUE_DISTRIBUTION    = 0x00000001,

    ALL_LINEAR_VALUE_MASK = VALUE_DISTRIBUTION
  } ;



  /**
   * Constructor.
   */
  PoXtLinearValueLegendEditor(SoWidget parent=NULL, 
                              const char * name=NULL,
                              SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  virtual ~PoXtLinearValueLegendEditor();

  /**
   * Sets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. (By default inclusionMask = 
   * ALL_LINEAR_VALUE_MASK and exclusionMask = 
   * NO_LINEAR_VALUE_MASK).
   */
  void setLinearValueLegendFilter(unsigned long inclusionMask,
                                  unsigned long exclusionMask);

  /**
   * Gets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. 
   */
  void getLinearValueLegendFilter(unsigned long & inclusionMask,
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
  
  // Attributes
  unsigned long   _incLinearValueMask;
  unsigned long   _excLinearValueMask;
  
 private:
  int _classMenusNb;
  SbBool _isLinearValueSet;
  
  // Callbacks for PoXtDialog
  static void linearValueElementsCallback (void *, 
                                           const PoXtDialog::PoXtDialogDataCB *);
};


#endif

