/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_LOG_AXIS_EDITOR_H
#define _POXT_LOG_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtCartesianAxisEditor.h>

/**
 * @DTEXT  Class for logarithmic axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtLogAxisEditor
: public PoXtCartesianAxisEditor
{

 public:

  enum LogAxisMask
  {
    NO_LOG_MASK           = 0x00000000,
    DECADE_LIST_DEF       = 0x00000001,
    DECADE_LIST           = 0x00000002,
    DECADE_REP            = 0x00000004,
    DECADE_FONT_NAME      = 0x00000008,
    DECADE_FONT_SIZE      = 0x00000010,
    TEN_POWER_REP         = 0x00000020,
    MULT_FACTOR_POSITION  = 0x00000040,
    MULT_FACTOR_DIST_AXIS = 0x00000080,
    ALL_LOG_MASK          = DECADE_LIST_DEF | DECADE_LIST 
    | DECADE_REP | DECADE_FONT_NAME 
    | DECADE_FONT_SIZE | TEN_POWER_REP 
    | MULT_FACTOR_POSITION | MULT_FACTOR_DIST_AXIS
  } ;



  /**
   * Constructor.
   */
  PoXtLogAxisEditor(SoWidget parent=NULL, 
                    const char * name=NULL,
                    SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtLogAxisEditor();

  /**
   * Sets editing filters defining which logarithmic axis attributes will be 
   * displayed in the editor. (By default inclusionMask = ALL_LOG_MASK and 
   * exclusionMask = NO_LOG_MASK).
   */
  void setLogAxisFilter(unsigned long inclusionMask,
                        unsigned long exclusionMask);

  /**
   * Gets editing filters defining which logarithmic axis attributes will be 
   * displayed in the editor. 
   */
  void getLogAxisFilter(unsigned long & inclusionMask,
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
  unsigned long   _incLogMask;
  unsigned long   _excLogMask;
  
 private:
  int _classMenusNb;
  SbBool _isLogSet;

  // Callbacks for PoXtDialog
  static void logElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_LOG_AXIS_EDITOR_H

