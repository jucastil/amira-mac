/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_CARTESIAN_AXIS_EDITOR_H
#define _POXT_CARTESIAN_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtAxisEditor.h>

/**
 * @DTEXT  Abstract class for cartesian axis editors.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtCartesianAxisEditor
: public PoXtAxisEditor
{

 public:

  enum CartesianAxisMask
  {
    NO_CARTESIAN_MASK    = 0x00000000,
    START                = 0x00000001,
    END                  = 0x00000002,
    TYPE                 = 0x00000004,
    ALL_CARTESIAN_MASK   = START | END | TYPE
  } ;



  /**
   * Sets editing filters defining which cartesian axis attributes will be displayed 
   * in the editor. (By default inclusionMask = ALL_CART_MASK and 
   * exclusionMask = NO_CART_MASK).
   */
  void setCartesianAxisFilter(unsigned long inclusionMask,
                              unsigned long exclusionMask);

  /**
   * Gets editing filters defining which cartesian axis attributes will be displayed 
   * in the editor. 
   */
  void getCartesianAxisFilter(unsigned long & inclusionMask,
                              unsigned long & exclusionMask) const;
 protected:
  PoXtCartesianAxisEditor (SoWidget Parent = NULL,
                           const char * name = NULL,
                           SbBool buildInsideParent = TRUE);
  
  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setAxisFilter();
  
  virtual ~PoXtCartesianAxisEditor ();
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  virtual void copyAxisFields(PoAxis * dest, PoAxis * source);
  virtual void updateAxisFromXtElements ();

  virtual int getMenuItems();

  // Attribute

  unsigned long   _incCartMask;
  unsigned long   _excCartMask;

 private:
  int _classMenusNb;
  SbBool _isCartesianSet;

  // Callbacks for PoXtDialog
  static void cartesianElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};

#endif //_POXT_CARTESIAN_AXIS_EDITOR_H

