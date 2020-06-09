/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORMATION_
#define  _SO_TRANSFORMATION_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransformation
//
//  Abstract base class for all nodes that affect the current
//  transformation. This class exists only to support type-id requests
//  for all types of transformation nodes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all geometric transformation nodes.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This is the abstract base class for all nodes that perform geometric
 *   transformations. It exists only to make it easy for applications to test whether
 *   a particular node is a transformation node (that is, is derived from this
 *   class).
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoAntiSquish,
 *    SoMatrixTransform,
 *    SoResetTransform,
 *    SoRotation,
 *    SoRotationXYZ,
 *    SoScale,
 *    SoSurroundScale,
 *    SoTransform,
 *    SoTransformManip,
 *    SoTransformSeparator,
 *    SoTranslation  SoUnits
 * 
 * 
 */ 

class INVENTOR_API SoTransformation : public SoNode {

  SO_NODE_HEADER(SoTransformation);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Constructor - protected since this is abstract
  SoTransformation();

 protected:
  virtual ~SoTransformation();
};

#endif /* _SO_TRANSFORMATION_ */

