/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_CHECK_BOX_AUDITOR_
#define  _SO_DIALOG_CHECK_BOX_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogCheckBox;

/**
 * @VSGEXT Dialog CheckBox auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a checkBox auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogCheckBoxAuditor : public SoAuditor
{

  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogCheckBoxAuditor();

  /**
   * To define.
   */
  virtual void dialogCheckBox(SoDialogCheckBox* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogCheckBoxAuditor();


};

#endif // _SO_DIALOG_CHECK_BOX_AUDITOR_
