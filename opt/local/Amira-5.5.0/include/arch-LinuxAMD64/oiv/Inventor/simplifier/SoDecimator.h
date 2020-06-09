/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (Apr 1998)
**=======================================================================*/


#ifndef _SO_DECIMATOR_
#define _SO_DECIMATOR_


#include <Inventor/SbLinear.h>
#include <Inventor/simplifier/SoSimplifier.h>

class DoDecimate;

/**
 * @VSGEXT Encapsulates an algorithm for simplifying shapes through mesh decimation.
 * 
 * @ingroup LMV
 * 
 * @DESCRIPTION
 *   This class implements a mesh decimation algorithm for simplifying shapes.
 *   
 *   Not all geometry nodes can be decimated. The following geometry nodes are
 *   decimated:
 *   
 *   - SoFaceSet @BR
 *   - SoIndexedFaceSet @BR
 *   - SoIndexedNurbsSurface @BR
 *   - SoIndexedTriangleStripSet @BR
 *   - SoNurbsSurface @BR
 *   - SoTriangleStripSet @BR
 *   - SoVRMLIndexedFaceSet
 *   
 *   The following geometry nodes are not decimated:
 *   
 *   - SoAnnoText3 @BR
 *   - SoAsciiText @BR
 *   - SoCone @BR
 *   - SoCube @BR
 *   - SoCylinder @BR
 *   - SoIndexedLineSet @BR
 *   - SoIndexedNurbsCurve @BR
 *   - SoLineSet @BR
 *   - SoNurbsCurve @BR
 *   - SoPointSet @BR
 *   - SoQuadMesh @BR
 *   - SoSphere @BR
 *   - SoText2 @BR
 *   - SoText3 @BR
 *   - SoVRMLBox @BR
 *   - SoVRMLCone @BR
 *   - SoVRMLElevationGrid @BR
 *   - SoVRMLExtrusion @BR
 *   - SoVRMLIndexedLineSet @BR
 *   - SoVRMLPointSet @BR
 *   - SoVRMLSphere @BR
 *   - SoVRMLText @BR
 *   - Any geometry under an SoLOD @BR
 *   - Any geometry under an SoLevelOfDetail @BR
 *   - Any geometry under an SoLevelOfSimplification @BR
 *   - Any geometry under an SoVRMLLOD
 *   
 *   The decimator does not decimate nodes such as SoCone, that adjust their
 *   complexity automatically (based on SoComplexity and/or the viewer-requested
 *   decimation level). The decimator also does not decimate nodes such as
 *   SoVRMLElevationGrid where decimation would not preserve the type of geometry.
 *   Decimated geometry is always an indexed face set. 
 * 
 * @SEE_ALSO
 *    SoSimplifier,
 *    SoSimplifyAction,
 *    SoShapeSimplifyAction,
 *    SoGlobalSimplifyAction
 * 
 * 
 */ 

class INVENTOR_API SoDecimator : public SoSimplifier {

public:
  /**
   * Constructor.
   */
  SoDecimator ();
  /**
   * Destructor.
   */
  ~SoDecimator();

  /**
   * Starts a new shape. Shape Type defines which triangle organization to use.
   */
  virtual void beginShape(ShapeType);

  /**
   * End shape
   */
  virtual void endShape();

  /**
   * Methods used to specify data to simplify.
   */
  virtual void setVertex (const SbVec3f&);

  /**
   *  
   * Sets the shape type used for building 
   * the simplified node.
   * Only SoIndexedFaceSet and SoFaceSet are supported.
   * SoIndexedFaceSet is used by default.
   */
  virtual void setSimplifiedShapeType(SoType simplifiedShapeType) ;

  /** 
   * Performs the simplification on the shapes
   * and builds the simplified node.
   */
  virtual SoNode* simplify (float ) ;

  /**
   * Removes all shapes and reset.
   */
  virtual void clear();

  /** 
   * Verbose mode
   */
  virtual void setVerbosity(SbBool v);
  
private:
  
  SoType simplifiedShapeType ;

  DoDecimate *decimer;
  
  int edge[2];
  int edgeCount;

  SbBool isModelComplete;
  
};

#endif // _SO_DECIMATOR_








