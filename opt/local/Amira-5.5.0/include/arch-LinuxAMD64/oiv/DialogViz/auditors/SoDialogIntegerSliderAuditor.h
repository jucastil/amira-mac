/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_INTEGER_SLIDER_AUDITOR_
#define  _SO_DIALOG_INTEGER_SLIDER_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogIntegerSlider;

/**
 * @VSGEXT Dialog IntegerSlider auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines an integerSlider auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogIntegerSliderAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogIntegerSliderAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void dialogIntegerSlider(SoDialogIntegerSlider* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogIntegerSliderAuditor();

};

#endif // _SO_DIALOG_INTEGER_SLIDER_AUDITOR_
