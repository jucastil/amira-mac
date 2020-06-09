/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/

#ifndef _SB_PROJECTION_COORDINATES
#define _SB_PROJECTION_COORDINATES

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h> 

#include <Inventor/STL/vector>

#if defined(_WIN32)
#pragma warning ( push )
#pragma warning ( disable: 4251 )
#endif

class SoNode;
class SoProjection;

/**
 * Cache projected coordinates.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This class stores the projected coordinates associated with a given geometry
 *  node and a given SoProjection node during a scene graph traversal.
 *  Each instance of SbProjectionCoordinates maintains a cache, based on the node IDs 
 *  of the associated node and projection node.
 *  Calling resetCache() will force the projected coordinates to be recomputed during 
 *  the next traversal.
 *  
 * @SEE_ALSO
 *  SoProjection,
 *  SoGeoProjection
 * 
 * 
 */
class INVENTOR_API SbProjectionCoordinates
{
public:

  /**
  * Constructor
  */
  SbProjectionCoordinates( SoProjection *projection );

  /**
  * Constructor
  */
  SbProjectionCoordinates();

  /**
  * Destructor
  */
  ~SbProjectionCoordinates();

  /**
  * Return coordinates
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{UNKNOWN}]
  */
  SbVec3f *getCoordinates(){return m_projCoords;}
  
  /**
  * Set associated projection
  */
  void setProjection( SoProjection *projection){ m_projection = projection;}

  /**
  * Reset the cache
  */
  void resetCache(SoNode *node);

  /**
  * Initialisation
  */
  void initCoordinates(SoNode *node,int size);

  /**
  * Return whether the cache is valid or not.
  */
  SbBool cacheIsValid(SoNode *node);

protected:

  /**
  * Initialisation
  */
  void init();

  /**
  * Max size of coordinates buffer
  */
  int m_maxSize;

  /**
  * size of coordinates buffer
  */
  int m_size;

  /**
  * Projected coordinates
  */
  SbVec3f *m_projCoords;

  /**
  * Projection node
  */
  SoProjection *m_projection;

private:
  /**
   * Node nodeID used for cache validation
   */
  uint64_t m_nodeId;

  /**
   * Projection node nodeID used for cache validation
   */
  uint64_t m_projNodeId;
};

#if defined(_WIN32)
#pragma warning ( pop )
#endif

#endif /* _SB_PROJECTION_ */

