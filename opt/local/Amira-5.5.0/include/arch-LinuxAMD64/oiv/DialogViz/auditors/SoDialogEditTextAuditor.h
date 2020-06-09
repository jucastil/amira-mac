/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_EDIT_TEXT_AUDITOR_
#define  _SO_DIALOG_EDIT_TEXT_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogEditText;

/**
 * @VSGEXT Dialog EditText auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines an editText auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoDialogEditTextAuditor : public SoAuditor
{

  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoDialogEditTextAuditor();

  /**
   * To define.
   */
  virtual void dialogEditText(SoDialogEditText* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoDialogEditTextAuditor();


};

#endif // _SO_DIALOG_COMBO_BOX_AUDITOR_
