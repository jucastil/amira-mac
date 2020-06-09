/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ludovic PEINE (Jun 2007)
**=======================================================================*/


#ifndef  SO_DISTRIBUTE_ACTION
#define  SO_DISTRIBUTE_ACTION

#include <Inventor/actions/SoSubAction.h>

/**
 * @VSGEXT Computes a distribution of the scene graph for use in depth 
 * compositing in ScaleViz.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class is used to compute a distribution of the scene graph for use 
 *   in depth compositing in ScaleViz.
 * 
 * In order to simplify the distribution of the scene graph, 
 * two different algorithms are supported for the automatic 
 * allocation of render unit IDs of each separator in a scene graph: 
 *
 * - ROUND_ROBIN, which implements a round robin algorithm, does static allocation based
 * on the number of running OIRUs. This algorithm is the fastest way to distribute a scene
 * graph between all running OIRUs, but as it does not take in account the weight of the sub
 * scene graph assigned to each OIRU, it can potentially result in an unbalanced distribution.
 * 
 * - TRIANGLE_COUNT is a dynamic algorithm that takes in account the weight of each separator,
 * and tries to distribute the scene graph as equally as possible between OIRUs. Compared
 * with the first algorithm, it is more time consuming, but the result is a better balanced scene
 * graph distribution.  This is the default.
 * 
 * To specify the desired distribution algorithm, instantiate an SoDistributeAction, 
 * specify the the desired algorithm, and apply the action on the scene graph that you want 
 * to distribute.
 * 
 * @SEE_ALSO
 *   SoSeparator,
 *   SoVRMLGroup
 *   SoDepthComposer
 * 
 * 
 */ 
class INVENTOR_API SoDistributeAction : public SoAction
{
  SO_ACTION_HEADER(SoDistributeAction);

public:
  /**
   *    Algorithms for scene graph distribution.
   */
  enum DistributeMethod
  {
    ROUND_ROBIN,
    TRIANGLE_COUNT
  };

  /**
   * Constructor. 
   */
  SoDistributeAction();

  /**
   * Destructor.
   */
#ifndef HIDDEN_FROM_DOC
  virtual ~SoDistributeAction();
#endif // HIDDEN_FROM_DOC

  /**
   *    Specifies the algorithm used to distribute the scene graph. @BR
   *    Default is TRIANGLE_COUNT.
   */
  void setDistributeMethod( DistributeMethod distribMethod );

  /**
   *    Returns the algorithm used to distribute the scene graph.
   */
  DistributeMethod getDistributeMethod();

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  /**
   *    Sets the initial weight of the scene graph. @BR
   *    Default is 0.
   */
  void setInitialWeight ( uint32_t initWeight );

  /**
   *    Sets the kind of cache used to weight each separator
   *    in the scene graph.
   */
  void setAverageWeight( uint32_t newAverage );

  /**
   *    Retrieves the current average weight.
   */
  uint32_t getAverageWeight();

  /**
   *    Retrieves the current render unit Id.
   */
  uint32_t getCurrentRUId();

  /**
   *    Sets the current render unit Id.
   */
  void setCurrentRUId( uint32_t currentRenderUnitId );


  /**
   *    Sets the weight to a given render unit Id.
   */
  void setRUIdWeight( uint32_t renderUnitId, uint32_t weight );

  /**
   *    Retrieves the weight associated with a given render unit Id.
   */
  uint32_t getRUIdWeight( uint32_t renderUnitId );

  /**
   *    Sets a weight to the current render unit Id.
   */
  uint32_t setCurRUIdWeight( uint32_t weight );

  /**
   *    Gets the weight of the scene graph not yet assigned.
   */
  uint32_t getRemainingWeight();

  /**
   *    Sets the weight of the scene graph not yet assigned.
   */
  void setRemainingWeight( uint32_t weight );

  /**
   *    Returns a new Render Unit Id using the brute force algorithm.
   */
  uint32_t getBruteForceRUId();

protected:
  
  /**
   * Description:
   *    Applies action to the graph rooted by a node.
   *
   * Use: public
   */
  void beginTraversal( SoNode* node );

private:

  DistributeMethod m_distributeMethod;
  uint32_t m_averageWeight;
  uint32_t m_currentRenderUnitId;
  uint32_t* m_weightAssigned;
  uint32_t m_initialWeight;
  uint32_t  m_remainingWeight;

  void resetParam();
  uint32_t getNextRUId();
};

// INLINE METHODS

inline void
SoDistributeAction::setDistributeMethod( SoDistributeAction::DistributeMethod distribMethod )
{
  m_distributeMethod = distribMethod;
}

inline SoDistributeAction::DistributeMethod 
SoDistributeAction::getDistributeMethod()
{ 
  return m_distributeMethod; 
}

inline uint32_t 
SoDistributeAction::getAverageWeight()
{
  return m_averageWeight;
}

inline void
SoDistributeAction::setAverageWeight( uint32_t newAverage )
{
  m_averageWeight = newAverage;
}

inline uint32_t
SoDistributeAction::getCurrentRUId()
{
  return m_currentRenderUnitId;
}

inline void
SoDistributeAction::setCurrentRUId( uint32_t currentRenderUnitId )
{
  m_currentRenderUnitId = currentRenderUnitId;
}

inline uint32_t 
SoDistributeAction::getRemainingWeight()
{
  return m_remainingWeight;
}

inline void
SoDistributeAction::setRemainingWeight( uint32_t weight )
{
  m_remainingWeight = weight;
}

#endif // SO_DISTRIBUTE_ACTION

/**/
