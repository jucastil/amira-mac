/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_GEN_AXIS_EDITOR_H
#define _POXT_GEN_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtCartesianAxisEditor.h>

/**
 * @DTEXT  Class for generalized axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtGenAxisEditor
: public PoXtCartesianAxisEditor
{

 public:

  enum GenAxisMask
  {
    NO_GEN_MASK        = 0x00000000,
    GRAD_LIST          = 0x00000001,
    ALL_GEN_MASK       = GRAD_LIST
  } ;



  /**
   * Constructor.
   */
  PoXtGenAxisEditor(SoWidget parent=NULL, 
                    const char * name=NULL,
                    SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtGenAxisEditor();

  /**
   * Sets editing filters defining which generalized axis attributes will be 
   * displayed in the editor. (By default inclusionMask = ALL_GEN_MASK and 
   * exclusionMask = NO_GEN_MASK).
   */
  void setGenAxisFilter(unsigned long inclusionMask,
                        unsigned long exclusionMask);

  /**
   * Gets editing filters defining which generalized axis attributes will be 
   * displayed in the editor. 
   */
  void getGenAxisFilter(unsigned long & inclusionMask,
                        unsigned long & exclusionMask) const;
 protected:
  virtual void buildWidget (SoWidget Parent, 
                            const char * name,
                            SbBool buildInsideParent);
  virtual void setAxisFilter();
  
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
  
  virtual void copyAxisFields (PoAxis *, PoAxis *);
  virtual void updateAxisFromXtElements ();
  
  virtual int getMenuItems();
  
  // Attribute
  unsigned long   _incGenMask;
  unsigned long   _excGenMask;
  
 private:
  int _classMenusNb;
  SbBool _isGenSet;

  // Callbacks for PoXtDialog
  static void genElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_GEN_AXIS_EDITOR_H

