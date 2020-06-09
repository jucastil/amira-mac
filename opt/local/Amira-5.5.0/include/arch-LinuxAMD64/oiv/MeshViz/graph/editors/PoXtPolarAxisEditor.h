/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_POLAR_AXIS_EDITOR_H
#define _POXT_POLAR_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtAxisEditor.h>

/**
 * @DTEXT  Abstract class for polar axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtPolarAxisEditor : public PoXtAxisEditor
{

 public:

  enum PolarAxisMask
  {
    NO_POLAR_MASK         = 0x00000000,
    OFFSET                = 0x00000001,
    START_RADIUS          = 0x00000002,
    END_RADIUS            = 0x00000004,
    THETA                 = 0x00000008,
    MULT_FACTOR_POSITION  = 0x00000010,
    MULT_FACTOR_DIST_AXIS = 0x00000020,
    ALL_POLAR_MASK        = OFFSET | START_RADIUS 
    | END_RADIUS | THETA  
    | MULT_FACTOR_POSITION | MULT_FACTOR_DIST_AXIS
  } ;



  /**
   * Sets editing filters defining which polar axis attributes will be displayed in 
   * the editor. (By default inclusionMask = ALL_POLAR_MASK and 
   * exclusionMask = NO_POLAR_MASK).
   */
  void setPolarAxisFilter(unsigned long inclusionMask,
                          unsigned long exclusionMask);

  /**
   * Gets editing filters defining which polar axis attributes will be displayed in 
   * the editor. 
   */
  void getPolarAxisFilter(unsigned long & inclusionMask,
                          unsigned long & exclusionMask) const;
 protected:
  PoXtPolarAxisEditor (SoWidget Parent = NULL,
                       const char * name = NULL,
                       SbBool buildInsideParent = TRUE);
  
  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setAxisFilter();
  
  virtual ~PoXtPolarAxisEditor ();
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  virtual void copyAxisFields(PoAxis * dest, PoAxis * source);
  virtual void updateAxisFromXtElements ();

  virtual int getMenuItems();

  // Attribute

  unsigned long   _incPolarMask;
  unsigned long   _excPolarMask;

 private:
  int _classMenusNb;
  SbBool _isPolarSet;

  // Callbacks for PoXtDialog
  static void polarElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_POLAR_AXIS_EDITOR_H

