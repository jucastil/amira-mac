/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : D. DALLA ROSA (Jun 2008)
**=======================================================================*/


#ifndef  _SO_TRANSFORMPROJECTION_
#define  _SO_TRANSFORMPROJECTION_


#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <Inventor/projection/SbProjection.h>
#include <Inventor/nodes/SoProjection.h>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif


/**
 * @VSGEXT Scale/recenter projection node
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *
 *  This property node is a specific SoProjection which applies a scale and recenter to a geometry. 
 *
 *  The computation is done on the CPU before the transfer to OpenGL. The main purpose of this feature 
 *  is to transform the vertex coordinates before sending them to OpenGL in order to avoid single
 *  precision issues, especially with the depth buffer.
 *
 *  Essentially this is a convenience node that automatically creates an SbTransformProjection
 *  and calls the setProjection() method for you.
 *
 *  The result of a bounding box action is the coordinates of the bounding box after 
 *  the projection because we need this version of the bounding box for rendering/clipping.
 *
 *  See SoProjection for important limitations of projection nodes.
 *
 *  @FILE_FORMAT_DEFAULT
 *    TransformProjection {
 *    @TABLE_FILE_FORMAT
 *       @TR parameters           @TD ""
 *       @TR matrix               @TD identity
 *       @TR isOn                 @TD TRUE
 *       @TR floatParameters      @TD 1
 *       @TR projTypeId           @TD 0
 *
 *       @TR scaleFactor          @TD 1.0
 *       @TR centerPosition       @TD 0.0 0.0 0.0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  SbTransformProjection,
 *  SoProjection,
 *  SoGeoProjection
 *
 * 
 */ 
class INVENTOR_API SoTransformProjection : public SoProjection 
{

  SO_NODE_HEADER( SoTransformProjection );

public:

  /**
  * Constructor
  */
  SoTransformProjection();

  /**
  * Scale factor applied to the geometry. @BR
  * Note: Each coordinate is multiplied by this value.
  */
  SoSFFloat scaleFactor;

  /**
  * Translation applied to the geometry. @BR
  * Note: This value is subtracted from each coordinate.
  */
  SoSFVec3f centerPosition;

 SoINTERNAL public:
  static void  initClass();
  static void  exitClass();

protected:
  
  /**
  * Destructor
  */
  ~SoTransformProjection();

private:
	
  SbProjection* m_transformProjectionRoutine;

};

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif /* _SO_TRANSFORMPROJECTION_ */

