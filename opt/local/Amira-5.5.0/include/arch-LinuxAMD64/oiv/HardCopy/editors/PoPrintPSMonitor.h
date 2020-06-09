/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef PO_PRINT_PS_MONITOR_H
#define PO_PRINT_PS_MONITOR_H

#include <HardCopy/editors/PoPrintMonitor.h>

/**
 * @HCEXT  Class to create a dialog box for PostScript printing.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *    Class to build a dialog box which contains all the necessary
 *    elements for configuring PostScript output. 
 *    This class uses the SoVectorizePSAction class parameters.
 * 
 */
class HARDCOPYW_API PoPrintPSMonitor : public PoPrintMonitor {

 public:

  enum PrintPSMask {
    NO_PRINT_PS_MASK    = 0x00000000,
    COLORED_MASK        = 0x00000001,
    ALL_PRINT_PS_MASK   = COLORED_MASK
  };
  
  /**
   * Constructor.
   */
  PoPrintPSMonitor(SoWidget Parent = NULL,
                   const SbString& name = "",
                   SbBool buildInsideParent = TRUE);


  /**
   * Destructor.
   */
  virtual ~PoPrintPSMonitor();

  /**
   * Sets editing filters defining which print PostScript attributes 
   * will be displayed in 
   * the dialog box. (By default inclusionMask = ALL_PRINT_PS_MASK and 
   * exclusionMask = NO_PRINT_PS_MASK).
   */
  void setPrintPSFilter(unsigned long inclusionMask,
                        unsigned long exclusionMask);

  /**
   * Returns the editing filters. See #setPrintPSFilter. 
   */
  void getPrintPSFilter(unsigned long &inclusionMask,
                        unsigned long &exclusionMask) const;

  /*----------------------------------------------------------------------------*/
 protected:
  void buildWidget(SoWidget Parent, 
                   const SbString& name, 
                   SbBool buildInsideParent);

  void destroyAction();

  void setFilter();
  int getMenuItems();

  SbString getDefaultWidgetName() const;
  SbString getDefaultTitle() const;
  SbString getDefaultIconTitle() const;

  unsigned long _incPrintPSMask;
  unsigned long _excPrintPSMask;

 private:
  int _classMenusNb;
  SbBool _isPrintPSSet;
  void writeActionIntoFile();
  static void writeActionIntoFileCB(void *, PoPrintPSMonitor *);
};


#endif //PO_PRINT_PS_MONITOR_H

