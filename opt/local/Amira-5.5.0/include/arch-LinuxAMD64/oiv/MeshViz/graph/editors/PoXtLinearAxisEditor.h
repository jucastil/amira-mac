/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_LINEAR_AXIS_EDITOR_H
#define _POXT_LINEAR_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtCartesianAxisEditor.h>


/**
 * @DTEXT  Class for linear axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtLinearAxisEditor
: public PoXtCartesianAxisEditor
{

 public:

  enum LinearAxisMask
  {
    NO_LINEAR_MASK        = 0x00000000,
    STEP                  = 0x00000001,
    GRAD_FIT              = 0x00000002,
    MULT_FACTOR_POSITION  = 0x00000004,
    MULT_FACTOR_DIST_AXIS = 0x00000008,
    FORMAT                = 0x00000010,
    ALL_LINEAR_MASK       = STEP | GRAD_FIT | MULT_FACTOR_POSITION 
    | MULT_FACTOR_DIST_AXIS | FORMAT
  } ;



  /**
   * Constructor.
   */
  PoXtLinearAxisEditor(SoWidget parent=NULL, 
                       const char * name=NULL,
                       SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  virtual ~PoXtLinearAxisEditor();

  /**
   * Sets editing filters defining which linear axis attributes will be displayed in 
   * the editor. (By default inclusionMask = ALL_LINEAR_MASK and 
   * exclusionMask = NO_LINEAR_MASK).
   */
  void setLinearAxisFilter(unsigned long inclusionMask,
                           unsigned long exclusionMask);

  /**
   * Sets editing filters defining which linear axis attributes will be displayed in 
   * the editor.
   */
  void getLinearAxisFilter(unsigned long & inclusionMask,
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
  unsigned long   _incLinearMask;
  unsigned long   _excLinearMask;

 private:
  int _classMenusNb;
  SbBool _isLinearSet;

  // Callbacks for PoXtDialog
  static void linearElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_LINEAR_AXIS_EDITOR_H

