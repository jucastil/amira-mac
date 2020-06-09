/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_CHOICE_AUDITOR_
#define  _SO_DIALOG_CHOICE_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogChoice;

/**
 * @VSGEXT Dialog Choice auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a choice component auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogChoiceAuditor : public SoAuditor
{

  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogChoiceAuditor();

  /**
   * To define.
   */
  virtual void dialogChoice(SoDialogChoice* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogChoiceAuditor();


};

#endif // _SO_DIALOG_CHOICE_AUDITOR_
