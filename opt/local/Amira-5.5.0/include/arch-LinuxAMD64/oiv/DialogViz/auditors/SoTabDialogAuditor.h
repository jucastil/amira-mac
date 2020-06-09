/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Dec 2005)
**=======================================================================*/

#ifndef  _SO_TAB_DIALOG_AUDITOR_
#define  _SO_TAB_DIALOG_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoTabDialog;

/**
 * @VSGEXT Tab Dialog auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a tab dialog auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoTabDialogAuditor : public SoAuditor
{

  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoTabDialogAuditor();

  /**
   * To define.
   */
  virtual void tabDialog(SoTabDialog* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoTabDialogAuditor();


};

#endif // _SO_TAB_DIALOG_AUDITOR_
