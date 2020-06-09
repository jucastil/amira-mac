/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiStreamlineExtractBase_H
#define  _MiStreamlineExtractBase_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>

/**
 * @DTEXT Base class for all streamline extractors.
 * 
 * @ingroup MeshIViz_Extract_Streamline
 * 
 * @DESCRIPTION
 *
 *    The base streamline extract interface defines the commun optional parameters
 *    and the direction enum used to integrate streamlines
 * 
 */

class MESHIVIZ_API MiStreamlineExtractBase : virtual public MiBaseExtractor
{
public:

  virtual ~MiStreamlineExtractBase() {}

  /**
  * Sets the maximum life time of the streamlines.
  * This method is not pure virtual so that no definition is needed if not used
  * @param maxLifeTime maximum life time of the streamlines.
  * Default: 0, i.e infinite life time.
  */
  virtual void setMaxLifeTime(double UNREF_PARAM(maxLifeTime)) {}
  /**
  * Sets the maximum length of the streamlines.
  * This method is not pure virtual so that no definition needed if not used
  * @param maxLength maximum length of the streamlines.
  * Default: 0, i.e infinite length.
  */
  virtual void setMaxLength(double UNREF_PARAM(maxLength)) {}
  /**
  * Sets the minimum speed of the streamlines.
  * This method is not pure virtual so that no definition needed if not used
  * @param minSpeed minimum speed of the streamlines.
  * Default: 0, i.e no speed constraint.
  */
  virtual void setMinSpeed(double UNREF_PARAM(minSpeed)) {}
  /**
  * Sets the step length factor for the streamlines integration.
  * This method is not pure virtual so that no definition needed if not used
  * @param factor length factor for the streamlines integration.
  * Defaul: 0.3.
  */
  virtual void setIntegrationStepLengthFactor(double UNREF_PARAM(factor)) {}
  /**
  * Sets the maximum step number during the streamlines integration.
  * This method is not pure virtual so that no definition needed if not used
  * @param maxStepNumber maximum step number.
  * Default: 0, i.e infinite step number.
  */
  virtual void setIntegrationMaxStepNumber(int UNREF_PARAM(maxStepNumber)) {} 

  /**
  * Integration direction
  */
  enum IntegrationDirection {
    FORWARD,  /**< Integration is done in the direction of the vectors.*/
    BACKWARD  /**< Integration is done in the opposite direction of the vectors. */
} ;

  /**
  * Sets the direction for the streamlines integration.
  * This method is not pure virtual so that no definition needed if not used
  * @param direction direction for the streamlines integration.
  * Default: FORWARD.
  */
  virtual void setIntegrationDirection(IntegrationDirection UNREF_PARAM(direction)) {}

};

#endif /* _MiStreamlineExtractBase_H */


