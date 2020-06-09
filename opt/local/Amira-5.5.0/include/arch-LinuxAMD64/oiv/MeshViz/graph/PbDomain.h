/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_DOMAIN_
#define  _PB_DOMAIN_

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <MeshViz/graph/PbBase.h>

class SoTransform ;
class SoMatrixTransform ;

/**
 * @DTEXT  Class to define a domain.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define a 2D/3D domain. It is the reference of all 
 *    Graph Master & 3D Data Master nodekits classes and some fields of these 
 *    classes are expressed in a domain.
 *    
 *    The domain usually defines the data coordinate limits of graphics to be 
 *    generated. Graph Master & 3D Data Master do not calculate these limits, so 
 *    this class  provides them. In conceptual terms, a 2D domain (3D domain) is 
 *    the smallest rectangle (parallelepiped) capable of containing the data for 
 *    the image to be generated. The sides of this rectangle (parallelepiped) are 
 *    parallel to the axis.Furthermore all Graph Master & 3D Data Master nodekits 
 *    classes may be transformed according to the domain which they refer to.
 *    
 *    There are five possible transformations (we note dx = xmax - xmin, dy = ymax - 
 *    ymin and dz = zmax - zmin, xmin, ymin,..., zmax are the limits of the domain):
 *      - The transformation is a scaling and a translation (all representations
 *        are drawn between [0-1] x [0-1] x ([0-1])). (type of transformation = 
 *        TRANSFORM_01).
 *    
 *      - All representations are scaled with scaling factors x = 1, y = dx/dy, 
 *        z = dx/dz. (type of transformation = SCALE_X_FIXED).
 *    
 *      - All representations are scaled with scaling factors x = dy/dx, y =1, 
 *        z = dy/dz. (type of transformation = SCALE_Y_FIXED).
 *    
 *      - All representations are scaled with scaling factors x = dz/dx, y = dz/dy, 
 *        z = 1. (type of transformation = SCALE_Z_FIXED).
 *    
 *      - One of scale 2,3,4 is applied according to the max(dx,dy,dz). (type of 
 *        transformation = SCALE_MAX_XYZ_FIXED).
 *
 *    Except the first transformation type, the others compute a scaling only 
 *    if the domain is heterogeneous.
 * 
 *    All methods concerning 2D domain, set the value zmin to 0 and the value zmax to
 *    1.  
 *    By default xmin = ymin = zmin = 0, xmax = ymax = zmax = 1 and the type of 
 *    transformation is SCALE_X_FIXED.
 *    
 *    Data given by the user to define the coordinates of the domain (xmin, ymin,  
 *    zmin, xmax,...) can be interpreted if the user wants to. The interpretation 
 *    of these data depends on the value of  the last attribute (of type BoundingBoxType)
 *    of each method for setting domain coordinates. 
 *    Values for this attribute can be :
 *      - AS_IS: Data are not interpreted. This is the default value.
 *      - MIN_BOUNDING_CUBE: The miminum bounding square(2D 
 *        domain)/cube(3D domain) is computed from the user data to set the domain 
 *        coordinates.
 *      - MAX_BOUNDED_CUBE: The maximum bounded square(2D 
 *        domain)/cube(3D domain) is computed from the user data to set the 
 *        domain coordinates.
 *
 * 
 */
class MESHVIZ_API PbDomain : public PbBase {


 public:

  

  /**
   *  Transform type
   */
  enum TransformType {
    TRANSFORM_01,
    SCALE_X_FIXED,
    SCALE_Y_FIXED,
    SCALE_Z_FIXED,
    SCALE_MAX_XYZ_FIXED
  } ;

  

  /**
   *  Bounding box interpretation
   */
  enum BoundingBoxType {
    AS_IS,
    MIN_BOUNDING_CUBE,
    MAX_BOUNDED_CUBE
  } ;

  /**
   * Default constructor.
   */
  PbDomain() ;

  /**
   * Copy constructor.
   */
  PbDomain(const PbDomain &domain) ;

  /**
   * Constructor of a 2D domain.
   */
  PbDomain(SbBox2f &box, BoundingBoxType type = AS_IS) ;

  /**
   * Constructor of a 3D domain.
   */
  PbDomain(SbBox3f &box, BoundingBoxType type = AS_IS) ;

  /**
   * Constructor of a 2D domain.
   */
  PbDomain(float xmin, float ymin, float xmax, float ymax, BoundingBoxType type = AS_IS) ;

  /**
   * Constructor of a 3D domain.
   */
  PbDomain(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, 
           BoundingBoxType type = AS_IS) ;

  /**
   * Sets a 2D domain.
   */
  void setDomain(float xmin, float ymin, float xmax, float ymax, BoundingBoxType type = AS_IS) ;

  /**
   * Sets a 3D domain.
   */
  void setDomain(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, 
                 BoundingBoxType type = AS_IS) ;

  /**
   * Sets a 2D domain.
   */
  void setDomain(SbBox2f &box, BoundingBoxType type = AS_IS) ;

  /**
   * Sets a 3D domain.
   */
  void setDomain(SbBox3f &box, BoundingBoxType type = AS_IS) ;

  /**
   * Gets the 2D domain.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getDomain(float &xmin, float &ymin, float &xmax, float &ymax) const ;

  /**
   * Gets the 3D domain.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getDomain(float &xmin, float &ymin, float &zmin, float &xmax, float &ymax, float &zmax) const ;

  /**
   * Gets the 2D domain.
   * [OIVJAVA-WRAPPER NAME{get2DDomain}]
   */
  void getDomain(SbBox2f &box) const ;

  /**
   * Gets the 3D domain.
   * [OIVJAVA-WRAPPER NAME{get3DDomain}]
   */
  void getDomain(SbBox3f &box) const ;

  /**
   * Sets the type of transformation. (SCALE_X_FIXED by default) 
   */
  void setTransformType(TransformType type) ;

  /**
   * Gets the type of transformation.
   */
  TransformType getTransformType() const
    { return m_transformType ; }

  /**
   * Get the domain transform matrix in an SoMatrixTransform object.
   */
  SoMatrixTransform* getMatrixTransform() const ;

  /**
   * Get the domain transform matrix in an SoTransform object.
   */
  SoTransform*       getTransform() const ;

  /**
   * Get the domain transform matrix in an SbMatrix object.
   */
  SbMatrix           getMatrix() const ;

  /**
   * Equality comparison operator.
   */
  int operator==(const PbDomain &dom) ;

  /**
   * Inequality comparison operator.
   */
  int operator!=(const PbDomain &dom) {return !(*this == dom) ;}

  /**
   * Assignment operator.
   */
  PbDomain& operator=(const PbDomain &domain) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  void  getDelta(float &deltaX, float &deltaY) const 
    { deltaX = m_delta[0] ; deltaY = m_delta[1] ; }

  void  getDelta(float &deltaX, float &deltaY, float &deltaZ) const
    { deltaX = m_delta[0] ;  deltaY =  m_delta[1] ;  deltaZ =  m_delta[2] ; }

  float getDeltaX() const 
    { return  m_delta[0] ; }

  float getDeltaY() const
    { return  m_delta[1] ; }

  float getDeltaZ() const
    { return  m_delta[2] ; }

  SbBool isHomogeneous() const ;
  
 private:
  // Used by constructor per copy and affectation operator
  void copy(const PbDomain &domain, SbBool isConstructorPerCopy) ;

  void init(float xmin, float ymin, float xmax, float ymax, BoundingBoxType type = AS_IS) ;
  void init3(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax, 
             BoundingBoxType type = AS_IS) ;

  float m_min[3], m_max[3], m_delta[3] ;
  TransformType m_transformType ;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_DOMAIN_ */

