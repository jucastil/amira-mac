/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORM_VEC3F_
#define  _SO_TRANSFORM_VEC3F_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFVec3f.h>

/**
 * Transforms a 3D vector by a 4x4 matrix.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a three dimensional floating-point vector and a
 *   transformation matrix. The vector is assumed to be a row vector.
 *   
 *   The engine multiplies the vector by the matrix and returns the result in the
 *   output #point. The output #direction contains the result when the
 *   matrix multiplication assumes the vector is a direction, and therefore ignores
 *   the translation part of the matrix. The output #normalDirection contains
 *   the normalized #direction
 * 
 * @FILE_FORMAT_DEFAULT
 *    TransformVec3f {
 *    @TABLE_FILE_FORMAT
 *       @TR vector         @TD 0 0 0
 *       @TR matrix         @TD 1 0 0 0
 *       @TR                @TD 0 1 0 0
 *       @TR                @TD 0 0 1 0
 *       @TR                @TD 0 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoTransformVec3f : public SoEngine {

  SO_ENGINE_HEADER(SoTransformVec3f);
    
 public:

  /**
   * Input row vector. 
   */
  SoMFVec3f   vector;
  /**
   * Input transformation matrix. 
   */
  SoMFMatrix  matrix;
    
  /**
   * ( SoMFVec3f )  Vector transformed by matrix.
   */
  SoEngineOutput point;
  /**
   * ( SoMFVec3f )  Vector transformed by matrix, ignoring translation.
   */
  SoEngineOutput direction;
  /**
   * ( SoMFVec3f )  Normalized direction.
   */
  SoEngineOutput normalDirection;
    
  /**
   * Constructor
   */
  SoTransformVec3f();
    
 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:
  // Destructor
  ~SoTransformVec3f();
 private:


  // Evaluation method
  virtual void evaluate();
};

#endif  /* _SO_TRANSFORM_VEC3F_ */

