/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_PUSH_BUTTON_AUDITOR_
#define  _SO_DIALOG_PUSH_BUTTON_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogPushButton;

/**
 * @VSGEXT Dialog PushButton auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a push button auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogPushButtonAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogPushButtonAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void dialogPushButton(SoDialogPushButton* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogPushButtonAuditor();

};

#endif // _SO_DIALOG_PUSH_BUTTON_AUDITOR_
