/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_ANGULAR_AXIS_EDITOR_H
#define _POXT_ANGULAR_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtAxisEditor.h>

/**
 * @DTEXT  Class for angular axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtAngularAxisEditor
: public PoXtAxisEditor
{

 public:

  enum AngularAxisMask
  {
    NO_ANGULAR_MASK        = 0x00000000,
    OFFSET                 = 0x00000001,
    START_ANGLE            = 0x00000002,
    END_ANGLE              = 0x00000004,
    RADIUS                 = 0x00000008,
    ANGLE_STEP             = 0x00000010,
    GRAD_FIT               = 0x00000020,
    ALL_ANGULAR_MASK       = OFFSET | START_ANGLE | END_ANGLE 
    | RADIUS | ANGLE_STEP | GRAD_FIT
  } ;



  /**
   * Constructor.
   */
  PoXtAngularAxisEditor(SoWidget parent=NULL, 
                        const char * name=NULL,
                        SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtAngularAxisEditor();

  /**
   * Sets editing filters defining which angular axis attributes will be displayed 
   * in the editor. (By default inclusionMask = ALL_ANGULAR_MASK and 
   * exclusionMask = NO_ANGULAR_MASK).
   */
  void setAngularAxisFilter(unsigned long inclusionMask,
                            unsigned long exclusionMask);

  /**
   * Gets editing filters defining which angular axis attributes will be displayed 
   * in the editor.
   */
  void getAngularAxisFilter(unsigned long & inclusionMask,
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
  unsigned long   _incAngularMask;
  unsigned long   _excAngularMask;

 private:
  int _classMenusNb;
  SbBool _isAngularSet;

  // Callbacks for PoXtDialog
  static void angularElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_ANGULAR_AXIS_EDITOR_H

