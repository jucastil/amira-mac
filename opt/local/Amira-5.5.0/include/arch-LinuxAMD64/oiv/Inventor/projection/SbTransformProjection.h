/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : D. DALLA ROSA (Jun 2008)
**=======================================================================*/

#ifndef  _SB_TRANSFORMPROJECTION_
#define  _SB_TRANSFORMPROJECTION_


#include <Inventor/projection/SbProjection.h>
#include <Inventor/nodes/SoTransformProjection.h>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif


/**
 * @VSGEXT Scale/recenter projection class
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This class implements a projection that applies a scale and recenter to geometry. 
 *
 *  This class can be used with an SoProjection node, but mainly exists to be used
 *  internally by the SoTransformProjection node.
 *
 * @SEE_ALSO
 *  SbProjection,
 *  SoTransformProjection
 *
 * 
 * [OIVNET-WRAPPER-CLASS MODULE{Inventor}]
 */

//---------------------------------------------------------------------------
class SbTransformProjection : public SbProjection
{
public:

  /**
  * Constructor.
  */
  SbTransformProjection( SoProjection *node );

  /**
  * Destructor.
  */
  virtual ~SbTransformProjection() {};

  /** Compute projected bounding box. @BR
  * As this projection is linear, projecting a bounding box
  * is equivalent to the bbox of the projected points.
  * Defining this method speeds up some rendering nodes.
  */
  virtual bool getProjectedBoundingBox( SbBox3f& bbox );

SoEXTENDER_Documented protected:
  /**
  * @copydoc SbProjection::apply
  */
  virtual void apply( SbVec3f &point );
};


//---------------------------------------------------------------------------
inline
SbTransformProjection::SbTransformProjection( SoProjection *node )
:SbProjection( node )
{
}


//---------------------------------------------------------------------------
inline void
SbTransformProjection::apply( SbVec3f &point )
{
  // Ok there is our projection node.
  SoTransformProjection* projection = (SoTransformProjection *)getProjectionNode();

  // We get some values from the configuration ndoe.
  float scaleFactor = projection->scaleFactor.getValue();
  SbVec3f centerPosition = projection->centerPosition.getValue();

  // We translate the point.
  point -= centerPosition;

  // We rescale it.
  point *= scaleFactor;
}

inline bool 
SbTransformProjection::getProjectedBoundingBox( SbBox3f& bbox )
{
  SbVec3f boundary[2];
  bbox.getBounds(boundary[0],boundary[1]);
  project(boundary[0]);
  project(boundary[1]);
  bbox.setBounds(boundary[0],boundary[1]);
  return true;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

//---------------------------------------------------------------------------

#endif /* _SB_TRANSFORMPROJECTION_ */

