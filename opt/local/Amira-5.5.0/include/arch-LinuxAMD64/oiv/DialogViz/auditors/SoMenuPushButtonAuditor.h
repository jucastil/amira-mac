/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_MENU_PUSH_BUTTON_AUDITOR_
#define  _SO_MENU_PUSH_BUTTON_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoMenuPushButton;

/**
 * @VSGEXT Menu PushButton auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a pushButton auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoMenuPushButtonAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoMenuPushButtonAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void menuPushButton(SoMenuPushButton* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoMenuPushButtonAuditor();

};

#endif // _SO_MENU_PUSH_BUTTON_AUDITOR_
