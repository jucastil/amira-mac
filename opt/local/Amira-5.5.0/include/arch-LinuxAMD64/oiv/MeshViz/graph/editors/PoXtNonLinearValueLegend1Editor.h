/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_NON_LINEAR_VALUE_LEGEND1_EDITOR_H
#define _POXT_NON_LINEAR_VALUE_LEGEND1_EDITOR_H

#include <MeshViz/graph/editors/PoXtAutoValueLegendEditor.h>

/**
 * @DTEXT  Class for non linear auto value legend (first representation) editors. 
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtNonLinearValueLegend1Editor
: public PoXtAutoValueLegendEditor
{

 public:

  enum NonLinearValueLegend1Mask
  {
    NO_NON_LINEAR_VALUE_MASK  = 0x00000000,

    LESS_LEVEL_STRING         = 0x00000001,
    GREATER_LEVEL_STRING      = 0x00000002,
    VALUE_SEPARATOR_STRING    = 0x00000004,

    ALL_NON_LINEAR_VALUE_MASK = LESS_LEVEL_STRING
    | GREATER_LEVEL_STRING | VALUE_SEPARATOR_STRING
  } ;



  /**
   * Constructor.
   */
  PoXtNonLinearValueLegend1Editor(SoWidget parent=NULL, 
                                  const char * name=NULL,
                                  SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  virtual ~PoXtNonLinearValueLegend1Editor();

  /**
   * Sets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. (By default inclusionMask = 
   * ALL_NON_LINEAR_VALUE_MASK and exclusionMask = 
   * NO_NON_LINEAR_VALUE_MASK).
   */
  void setNonLinearValueLegend1Filter(unsigned long inclusionMask,
                                      unsigned long exclusionMask);

  /**
   * Gets editing filters defining which non linear auto value legend attributes 
   * will be displayed in the editor. 
   */
  void getNonLinearValueLegend1Filter(unsigned long & inclusionMask,
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

