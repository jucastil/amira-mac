/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef PO_PRINT_HPGL_MONITOR_H
#define PO_PRINT_HPGL_MONITOR_H

#include <HardCopy/editors/PoPrintMonitor.h>

/**
 * @HCEXT  Class to create a print HPGL format dialog box.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *    Class to build a dialog box which contains all elements to configure 
 *    a printing. This class uses the SoVectorizeHPGLAction class parameters. 
 * 
 */
class HARDCOPYW_API PoPrintHPGLMonitor : public PoPrintMonitor {

 public:

  /**
   * Constructor.
   */
  PoPrintHPGLMonitor(SoWidget Parent = NULL,
                     const SbString& name = "",
                     SbBool buildInsideParent = TRUE);


  /**
   * Destructor.
   */
  virtual ~PoPrintHPGLMonitor();

  /*----------------------------------------------------------------------------*/
 protected:
  void buildWidget(SoWidget Parent, const SbString& name, SbBool buildInsideParent);

  void destroyAction();

  SbString getDefaultWidgetName() const;
  SbString getDefaultTitle() const;
  SbString getDefaultIconTitle() const;

 private:
  void writeActionIntoFile();
  static void writeActionIntoFileCB(void *, PoPrintHPGLMonitor *);
};
#endif //PoPrintHPGLMonitor

