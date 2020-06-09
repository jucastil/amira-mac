/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_DIALOG_AUDITOR_
#define  _SO_DIALOG_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoDialogCheckBox;
class SoDialogComboBox;
class SoDialogIntegerSlider;
class SoDialogEditText;
class SoDialogPushButton;
class SoDialogRadioButtons;
class SoDialogRealSlider;
class SoTabDialog;
//class SoDialogTree;
class SoMenuCheckBox;
class SoMenuFileSelection;
class SoMenuPushButton;
class SoMenuRadioButtons;

/**
 * @VSGEXT Dialog auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 * 
 * @SEE_ALSO
 *
 */

class DIALOGVIZ_API SoDialogAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * 
   */
  virtual void dialogPushButton(SoDialogPushButton* cpt);

  /**
   * 
   */
  virtual void dialogCheckBox(SoDialogCheckBox* cpt);

  /**
   * 
   */
  virtual void dialogComboBox(SoDialogComboBox* cpt);

  /**
   * 
   */
  virtual void dialogEditText(SoDialogEditText* cpt);

  /**
   * 
   */
  virtual void dialogIntegerSlider(SoDialogIntegerSlider* cpt);

  /**
   * 
   */
  virtual void dialogRadioButtons(SoDialogRadioButtons* cpt);

  /**
   * 
   */
  virtual void dialogRealSlider(SoDialogRealSlider* cpt);

  /**
   * 
   */
  virtual void tabDialog(SoTabDialog* cpt);

  /**
   * 
   */
//  virtual void dialogTree(SoDialogTree* cpt);

  /**
   * 
   */
  virtual void menuPushButton(SoMenuPushButton* cpt);

  /**
   * 
   */
  virtual void menuCheckBox(SoMenuCheckBox* cpt);

  /**
   * 
   */
  virtual void menuFileSelection(SoMenuFileSelection* cpt);

  /**
   * 
   */
  virtual void menuRadioButtons(SoMenuRadioButtons* cpt);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual ~SoDialogAuditor();

 protected:
  SoDialogAuditor();
};

#endif // _SO_DIALOG_AUDITOR_
