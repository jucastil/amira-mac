/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef PO_PRINT_CGM_MONITOR_H
#define PO_PRINT_CGM_MONITOR_H

#include <HardCopy/editors/PoPrintMonitor.h>

/**
 * @HCEXT  Class to create a print CGM format dialog box.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *    Class to build a dialog box which contains all elements to configure 
 *    a printing. This class uses the SoVectorizeCGMAction class parameters.
 * 
 */
class HARDCOPYW_API PoPrintCGMMonitor : public PoPrintMonitor {

 public:

  enum PrintCGMMask {
    NO_PRINT_CGM_MASK    = 0x00000000,
    BINARY_MASK          = 0x00000001,
    VERSION_MASK         = 0x00000002,
    COLOR_TYPE_MASK      = 0x00000004,
    ALL_PRINT_CGM_MASK   = BINARY_MASK | VERSION_MASK | COLOR_TYPE_MASK
  };

  /**
   * Constructor.
   */
  PoPrintCGMMonitor(SoWidget Parent = NULL,
                    const SbString& name = "",
                    SbBool buildInsideParent = TRUE);

  /**
   * Destructor.
   */
  virtual ~PoPrintCGMMonitor();

  /**
   * Sets editing filters defining which print CGM attributes will be displayed in 
   * the dialog box. (By default inclusionMask = ALL_PRINT_CGM_MASK and 
   * exclusionMask = NO_PRINT_CGM_MASK).
   */
  void setPrintCGMFilter(unsigned long inclusionMask,
                         unsigned long exclusionMask);

  /**
   * Gets editing filters defining which print CGM attributes will be displayed in 
   * the dialog box. 
   */
  void getPrintCGMFilter(unsigned long &inclusionMask,
                         unsigned long &exclusionMask) const;

  /*----------------------------------------------------------------------------*/
 protected:

  void buildWidget(SoWidget Parent, const SbString& name, SbBool buildInsideParent);

  void destroyAction();

  void setFilter();
  int getMenuItems();

  SbString getDefaultWidgetName() const;
  SbString getDefaultTitle() const;
  SbString getDefaultIconTitle() const;

  unsigned long _incPrintCGMMask;
  unsigned long _excPrintCGMMask;

 private:
  int _classMenusNb;
  SbBool _isPrintCGMSet;
  void writeActionIntoFile();
  static void writeActionIntoFileCB(void *, PoPrintCGMMonitor * monitor);
};

#endif //PO_PRINT_CGM_MONITOR_H

