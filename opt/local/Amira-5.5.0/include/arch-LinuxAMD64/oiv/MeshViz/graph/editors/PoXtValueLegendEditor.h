/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_VALUE_LEGEND_EDITOR_H
#define _POXT_VALUE_LEGEND_EDITOR_H

#include <MeshViz/graph/editors/PoXtLegendEditor.h>

/**
 * @DTEXT  Abstract class for values legend editors. 
 * 
 * @ingroup LegendEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtValueLegendEditor
: public PoXtLegendEditor
{

 public:

  enum ValueLegendMask
  {
    NO_VALUE_MASK      = 0x00000000,

    UPPER_UNDEF_STRING = 0x00000001,
    LOWER_UNDEF_STRING = 0x00000002,
    PERIOD_VALUE       = 0x00000004,
    FIRST_VALUE        = 0x00000008,
    LAST_VALUE         = 0x00000010,

    ALL_VALUE_MASK = UPPER_UNDEF_STRING | LOWER_UNDEF_STRING 
    | PERIOD_VALUE | FIRST_VALUE | LAST_VALUE
  } ;



  /**
   * Destructor.
   */
  virtual ~PoXtValueLegendEditor();

  /**
   * Sets editing filters defining which value legend attributes will be displayed 
   * in the editor. (By default inclusionMask = ALL_VALUE_MASK and 
   * exclusionMask = NO_VALUE_MASK).
   */
  void setValueLegendFilter(unsigned long inclusionMask,
                            unsigned long exclusionMask);

  /**
   * Gets editing filters defining which value legend attributes will be displayed 
   * in the editor.
   */
  void getValueLegendFilter(unsigned long & inclusionMask,
                            unsigned long & exclusionMask) const;
 protected:
  PoXtValueLegendEditor(SoWidget parent=NULL, 
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
  
  // Attribute
  unsigned long   _incValueMask;
  unsigned long   _excValueMask;
  
 private:
  int _classMenusNb;
  SbBool _isValueSet;
  
  // Callbacks for PoXtDialog
  static void valueElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_VALUE_LEGEND_EDITOR_H

