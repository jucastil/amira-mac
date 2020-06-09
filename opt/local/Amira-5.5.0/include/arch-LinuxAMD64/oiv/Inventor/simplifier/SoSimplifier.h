/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (Apr 1998)
**=======================================================================*/


#ifndef _SO_SIMPLIFIER_
#define _SO_SIMPLIFIER_


#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoNode.h>


/**
 * @VSGEXT Abstract base class for objects that encapsulate simplification algorithms.
 * 
 * @ingroup LMV
 * 
 * @DESCRIPTION
 *   This class abstract base class for objects that encapsulates simplification
 *   algorithms. This object receives a set of triangles and returns a new list
 *   representing a simplified version of the original geometry. 
 * 
 * @SEE_ALSO
 *    SoDecimator,
 *    SoSimplifyAction,
 *    SoShapeSimplifyAction,
 *    SoGlobalSimplifyAction
 * 
 * 
 */ 

class INVENTOR_API SoSimplifier {

public:
  /**
   * Constructor.
   */
  SoSimplifier () : shapeType (TRIANGLES), numTriangles (0), isShapeOpen (FALSE), 
    hasNormal (FALSE), hasColor (FALSE), color (0), hasData (FALSE), 
    numData (0), data (NULL), verbosity (FALSE) {};
  /**
   * Destructor.
   */
  virtual ~SoSimplifier();
 
    /** ShapeType */
  enum ShapeType { 
    /** TRIANGLES */
    TRIANGLES, 
    /** TRIANGLE_STRIP */
    TRIANGLE_STRIP, 
    /** TRIANGLE_FAN */
    TRIANGLE_FAN
  };

  /**
   * Starts a new shape, ShapeType defines which triangle organization to use.
   * ShapeType can be one of TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN.
   */
  virtual void beginShape(ShapeType);
  /**
   * Ends a shape started by beginShape().
   */
  virtual void endShape();

  /**
   * Specifies a new vertex location.
   */
  virtual void setVertex (const SbVec3f&);

  /**
   * Method to set optional vertex data (normal). Must be called before setVertex().
   */
  void setNormal (const SbVec3f&);
  /**
   * Method to set optional vertex data (data). Must be called before setVertex().
   */
  void setData   (int numData, const float*);
  /**
   * Method to set optional vertex data (color). Must be called before setVertex()
   */
  void setColor  (const unsigned long&);

  /**
   * Performs the simplification on the shapes and returns a simplified node. On this
   * class, this function is pure virtual; derived classes must implement this
   * function.
   */
  virtual SoNode* simplify (float ) = 0 ;

  /**
   * Removes all shapes and reset.
   */
  virtual void clear();

  /**
   * Returns the number of triangles actually stored in the object. If called after
   * simplify(), returns the remaining triangles. 
   */
  virtual int getNumTriangles() { return numTriangles; };

  /**
   * Sets whether to print messages while simplifying.
   */
  virtual void setVerbosity(SbBool v) { verbosity = v;}
  /**
   * Gets whether to print messages while simplifying.
   */
  SbBool getVerbosity() const { return verbosity;}

protected:
  
  ShapeType      shapeType;
  int            numTriangles;
  SbBool         isShapeOpen;

  // current normal, color and data (texture coordinates,...) 
  SbBool         hasNormal;
  SbVec3f        normal;
  SbBool         hasColor;
  unsigned long  color;
  SbBool         hasData;
  int            numData;
  float         *data;
  SbBool         verbosity;

};

#endif // _SO_SIMPLIFIER_








