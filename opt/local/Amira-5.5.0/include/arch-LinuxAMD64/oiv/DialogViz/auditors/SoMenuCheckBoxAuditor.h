/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_MENU_CHECK_BOX_AUDITOR_
#define  _SO_MENU_CHECK_BOX_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoMenuCheckBox;

/**
 * @VSGEXT Menu CheckBox auditor
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

class DIALOGVIZ_API SoMenuCheckBoxAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoMenuCheckBoxAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void menuCheckBox(SoMenuCheckBox* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoMenuCheckBoxAuditor();

};

#endif // _SO_MENU_CHECK_BOX_AUDITOR_
