/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_POLAR_LOG_AXIS_EDITOR_H
#define _POXT_POLAR_LOG_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtPolarAxisEditor.h>

/**
 * @DTEXT  Class for polar logarithmic axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtPolarLogAxisEditor
: public PoXtPolarAxisEditor
{

 public:

  enum PolarLogAxisMask
  {
    NO_POLAR_LOG_MASK     = 0x00000000,
    DECADE_LIST_DEF       = 0x00000001,
    DECADE_LIST           = 0x00000002,
    DECADE_REP            = 0x00000004,
    DECADE_FONT_NAME      = 0x00000008,
    DECADE_FONT_SIZE      = 0x00000010,
    TEN_POWER_REP         = 0x00000020,
    ALL_POLAR_LOG_MASK    = DECADE_LIST_DEF | DECADE_LIST 
    | DECADE_REP | DECADE_FONT_NAME 
    | DECADE_FONT_SIZE | TEN_POWER_REP
  } ;



  /**
   * Constructor.
   */
  PoXtPolarLogAxisEditor(SoWidget parent=NULL, 
                         const char * name=NULL,
                         SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtPolarLogAxisEditor();

  /**
   * Sets editing filters defining which polar logarithmic axis 
   * attributes will be displayed in the editor. (By default 
   * inclusionMask = ALL_POLAR_LOG_MASK and exclusionMask = 
   * NO_POLAR_LOG_MASK).
   */
  void setPolarLogAxisFilter(unsigned long inclusionMask,
                             unsigned long exclusionMask);

  /**
   * Gets editing filters defining which polar logarithmic axis 
   * attributes will be displayed in the editor.
   */
  void getPolarLogAxisFilter(unsigned long & inclusionMask,
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

  // Attributes
  unsigned long   _incPolarLogMask;
  unsigned long   _excPolarLogMask;

 private:
  int _classMenusNb;
  SbBool _isPolarLogSet;

  // Callbacks for PoXtDialog
  static void polarLogElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);
};


#endif //_POXT_POLAR_LOG_AXIS_EDITOR_H

