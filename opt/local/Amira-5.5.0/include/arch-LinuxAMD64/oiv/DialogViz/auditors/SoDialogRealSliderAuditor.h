/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_REAL_SLIDER_AUDITOR_
#define  _SO_DIALOG_REAL_SLIDER_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogRealSlider;

/**
 * @VSGEXT Dialog RealSlider auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a realSlider auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogRealSliderAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogRealSliderAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void dialogRealSlider(SoDialogRealSlider* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogRealSliderAuditor();

};

#endif // _SO_DIALOG_REAL_SLIDER_AUDITOR_
