/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _POXT_TIME_AXIS_EDITOR_H
#define _POXT_TIME_AXIS_EDITOR_H

#include <MeshViz/graph/editors/PoXtAxisEditor.h>

/**
 * @DTEXT  Class for time axis editor.
 * 
 * @ingroup AxisEditors
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZW_API PoXtTimeAxisEditor
: public PoXtAxisEditor
{

 public:

  enum TimeAxisMask
  {
    NO_TIME_MASK        = 0x00000000,
    START_DATE          = 0x00000001,
    END_DATE            = 0x00000002,
    COORD               = 0x00000004,
    TYPE                = 0x00000008,
    LANGUAGE            = 0x00000010,
    GRAD_FIT            = 0x00000020,
    GRAD_REP            = 0x00000040,
    TIMES_PERIOD        = 0x00000080,
    DATE_FORMAT_MAPPING = 0x00000100,
    ALL_TIME_MASK       = START_DATE | END_DATE | COORD 
    | TYPE | LANGUAGE | GRAD_FIT
    | GRAD_REP | TIMES_PERIOD | DATE_FORMAT_MAPPING
  } ;



  /**
   * Constructor.
   */
  PoXtTimeAxisEditor(SoWidget parent=NULL, 
                     const char * name=NULL,
                     SbBool buildInsideParent=TRUE);

  /**
   * Destructor.
   */
  ~PoXtTimeAxisEditor();

  /**
   * Sets editing filters defining which time axis attributes will be 
   * displayed in the editor. (By default inclusionMask = ALL_TIME_MASK 
   * and exclusionMask = NO_TIME_MASK).
   */
  void setTimeAxisFilter(unsigned long inclusionMask,
                         unsigned long exclusionMask);

  /**
   * Gets editing filters defining which time axis attributes will be 
   * displayed in the editor.
   */
  void getTimeAxisFilter(unsigned long & inclusionMask,
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
  unsigned long   _incTimeMask;
  unsigned long   _excTimeMask;

 private:
  int _classMenusNb;
  SbBool _isTimeSet;

  // Callbacks for PoXtDialog
  static void timeElementsCallback (void *, const PoXtDialog::PoXtDialogDataCB *);

};

#endif //_POXT_TIME_AXIS_EDITOR_H

