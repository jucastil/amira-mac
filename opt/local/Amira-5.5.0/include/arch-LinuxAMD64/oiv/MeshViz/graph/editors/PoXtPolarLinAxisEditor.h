/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_POLAR_LIN_AXIS_EDITOR_H
#define _POXT_POLAR_LIN_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtPolarAxisEditor.h>

/**
 * @DTEXT  Class for polar linear axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtPolarLinAxisEditor
: public PoXtPolarAxisEditor
{

 public:

  enum PolarLinAxisMask
  {
    NO_POLAR_LIN_MASK        = 0x00000000,
    STEP                     = 0x00000001,
    GRAD_FIT                 = 0x00000002,
    FORMAT                   = 0x00000004,
    ALL_POLAR_LIN_MASK       = STEP | GRAD_FIT | FORMAT
  } ;



  /**
   * Constructor.
   */
  PoXtPolarLinAxisEditor(SoWidget parent=NULL, 
                         const char * name=NULL,
                         SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtPolarLinAxisEditor();

  /**
   * Sets editing filters defining which polar linear axis attributes will be 
   * displayed in the editor. (By default inclusionMask = 
   * ALL_POLAR_LIN_MASK and exclusionMask = NO_POLAR_LIN_MASK).
   */
  void setPolarLinAxisFilter(unsigned long inclusionMask,
                             unsigned long exclusionMask);

  /**
   * Gets editing filters defining which polar linear axis attributes will be 
   * displayed in the editor. 
   */
  void getPolarLinAxisFilter(unsigned long & inclusionMask,
                             unsigned long & exclusionMask) const;
 protected:
  virtual void buildWidget (SoWidget Parent, 
                            const char * name, 
                            SbBool buildInsideParent);
  virtual void setAxisFilter();
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  virtual void copyAxisFields(PoAxis * dest, PoAxis * source);
  virtual void updateAxisFromXtElements ();

  virtual int getMenuItems();

  // Attribute
  unsigned long   _incPolarLinMask;
  unsigned long   _excPolarLinMask;

 private:
  int _classMenusNb;
  SbBool _isPolarLinSet;

  // Callbacks for PoXtDialog
  static void polarLinElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_POLAR_LIN_AXIS_EDITOR_H

