/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2003)
**=======================================================================*/


#ifndef  _SO_SEARCHSTEP_ACTION_
#define  _SO_SEARCHSTEP_ACTION_

#include <Inventor/actions/SoSearchAction.h>

class SoSearchStepAction;

/** 
 * @VSGEXT Searches for nodes in the scene graph step by step.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *  This class extends SoSearchAction.
 *  This class allows the user to add a \oivnetdoc delegate \else callback \endoivnetdoc to control which paths are added
 *  to the path list.
 *  This user \oivnetdoc delegate \else callback \endoivnetdoc is called just before the found path would be added to the list. It
 *  determines whether or not the path will be added to the list. 
 *  The use of this class is particularly interesting when the found paths are potentially
 *  numerous and the user wants to filter the returned path list to retrieve only some of them.
 *
 * @SEE_ALSO
 *    SoSearchAction,
 *    SoSearchPathAction
 * 
 */
class INVENTOR_API SoSearchStepAction : public SoSearchAction {

  SO_ACTION_HEADER(SoSearchStepAction);

 public:

  /**
   * Constructor.
   */
  SoSearchStepAction();

  /**
   * Destructor.
   */
  virtual ~SoSearchStepAction();

  /** 
  * SoSearchStepAction callback function prototype.
  * @param foundPath Corresponds to the current found path.
  * @param userData Is the data passed by user.
  * @param thisSSA Retrieves the inquiring SoSearchStepAction instance.
  */
typedef SbBool AddingPathCallback(SoFullPath* foundPath, void* userData, SoSearchStepAction* thisSSA);

  /**
   * Add the user callback that the SearchAction must call while building the
   * path list.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
 void setAddingPathCallBack(AddingPathCallback *ap_cb, void *u_data);

SoEXTENDER public:
  virtual void    setFound();

SoINTERNAL public:
  static void     initClass();
  static void     exitClass();

private:
    AddingPathCallback *addingPathCB;
    void *addingPathCB_udata;
};

#endif /* _SO_SEARCHSTEP_ACTION_ */

