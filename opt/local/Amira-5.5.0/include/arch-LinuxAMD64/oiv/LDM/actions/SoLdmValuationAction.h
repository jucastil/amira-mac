/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SOLDMVALUATIONACTION_H
#define SOLDMVALUATIONACTION_H

#include <Inventor/actions/SoSubAction.h>
#include <LDM/SoLDMLargeDataManagement.h>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
*
* @LDMEXT LDM valuation action.
*
* @ingroup LDMActions
*
* @DESCRIPTION
*    This is a internal pre-rendering action used by LDM to 
*    define which LDM tiles should be loaded or unloaded.
*
*/
class LDM_API SoLdmValuationAction : public SoAction
{
  SO_ACTION_HEADER(SoLdmValuationAction);

public:
  /**
   * Constructor.
   */
  SoLdmValuationAction();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** Return a new instance */
  static SoAction* createCb();

  /** Return true if action is gathering LDM geometries */
  bool isCollecting() const { return m_isCollecting; }

  /** Add ds to the list of traversed datasets */
  void addDataSet(SoDataSet* ds);

protected:
  virtual void beginTraversal(SoNode *node);

private:
  static void callDoAction(SoAction *action, SoNode *node);
  static void voidAction(SoAction *action, SoNode *node);
  static void doValuationActionDataSet(SoAction *action, SoNode *node);
  static void doValuationAction(SoAction *action, SoNode *node);
  static void doActionOnRTT(SoAction *action, SoNode* node);

  /** Value all LDM octrees */
  void valueOctree();

  bool m_isCollecting;

  /** List of traversed dataset */
  SoLDM::DsVector m_dsList;
  SoLDM::DsVector m_prevDsList;
};

#ifndef HIDDEN_FROM_DOC
class LDM_API SoLdmValuationActionInterface
{
public:
  /** Register ldm nodes */
  virtual void ldmAction(SoLdmValuationAction* action) = 0;

  /** Destructor */
  virtual ~SoLdmValuationActionInterface() 
  {};
};
#endif //HIDDEN_FROM_DOC

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif
