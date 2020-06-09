/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_MENU_RADIO_BUTTONS_AUDITOR_
#define  _SO_MENU_RADIO_BUTTONS_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoMenuRadioButtons;

/**
 * @VSGEXT Menu RadioButtons auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a radioButtons auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoMenuRadioButtonsAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoMenuRadioButtonsAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void menuRadioButtons(SoMenuRadioButtons* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoMenuRadioButtonsAuditor();

};

#endif // _SO_MENU_RADIO_BUTTONS_AUDITOR_
