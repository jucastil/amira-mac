/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/

#ifndef  _SO_MENU_FILE_SELECTION_AUDITOR_
#define  _SO_MENU_FILE_SELECTION_AUDITOR_

#include <DialogViz/auditors/SoAuditor.h>

class SoMenuFileSelection;

/**
 * @VSGEXT Menu FileSelection auditor
 * 
 * @ingroup Auditors
 * 
 * @DESCRIPTION
 *   This class defines a file selection auditor. 
 * 
 * @SEE_ALSO
 *   SoDialogAuditor
 *
 */

class DIALOGVIZ_API SoMenuFileSelectionAuditor : public SoAuditor
{
  SO_AUDITOR_HEADER();

 public:

  /**
   * Constructor
   */
  SoMenuFileSelectionAuditor();

  /**
   * Virtual function that user has to redefine.
   */
  virtual void menuFileSelection(SoMenuFileSelection* cpt) = 0;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoMenuFileSelectionAuditor();

};

#endif // _SO_MENU_FILE_SELECTION_AUDITOR_
