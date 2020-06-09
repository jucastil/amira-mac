/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_NON_LINEAR_VALUE_LEGEND2_EDITOR_H
#define _POXT_NON_LINEAR_VALUE_LEGEND2_EDITOR_H

#include <MeshViz/graph/editors/PoXtAutoValueLegendEditor.h>

/**
 * @DTEXT  Class for non linear auto value legend (second representation) editors.
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtNonLinearValueLegend2Editor
: public PoXtAutoValueLegendEditor
{

 public:

  enum NonLinearValueLegend2Mask
  {
    NO_NON_LINEAR_VALUE_MASK  = 0x00000000,

    ALL_NON_LINEAR_VALUE_MASK = NO_NON_LINEAR_VALUE_MASK
  } ;



  /**
   * Constructor.
   */
  PoXtNonLinearValueLegend2Editor(SoWidget parent=NULL, 
                                  const char * name=NULL,
                                  SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  virtual ~PoXtNonLinearValueLegend2Editor();

  /**
   * Sets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. (By default inclusionMask = 
   * ALL_NON_LINEAR_VALUE_MASK and exclusionMask = 
   * NO_NON_LINEAR_VALUE_MASK).
   */
  void setNonLinearValueLegend2Filter(unsigned long inclusionMask,
                                      unsigned long exclusionMask);

  /**
   * Gets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. 
   */
  void getNonLinearValueLegend2Filter(unsigned long & inclusionMask,
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
  unsigned long   _incNonLinearValueMask;
  unsigned long   _excNonLinearValueMask;
  
 private:
  int _classMenusNb;
  SbBool _isNonLinearValueSet;
  
  // Callbacks for PoXtDialog
  static void nonLinearValueElementsCallback (void *, 
                                              const PoXtDialog::PoXtDialogDataCB *);
};


#endif

