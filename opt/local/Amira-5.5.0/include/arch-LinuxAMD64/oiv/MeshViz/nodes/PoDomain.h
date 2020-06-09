/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_DOMAIN_
#define  _PO_DOMAIN_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

#include <MeshViz/nodes/PoNode.h>

class PbDomain ;
class SoFieldSensor ;
class SoTransform ;
class SoMatrixTransform ;

/**
 * @DTEXT  Node to define a domain.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This node defines the current domain for all subsequent MeshViz 
 *    representations.
 *    This class is used to define a 2D/3D domain.
 *    
 *    The domain usually defines the data coordinate limits of graphics to be 
 *    generated. Graph Master & 3D Data Master do not calculate these limits, so 
 *    this class  provides them. In conceptual terms, a 2D domain (3D domain) is 
 *    the smallest rectangle (parallelepiped) capable of containing the data for 
 *    the image to be generated. The sides of this rectangle (parallelepiped) are 
 *    parallel to the axis. Furthermore all Graph Master & 3D Data Master nodekits 
 *    classes may be transformed according to the domain which they depend on.
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
 *  NOTE: PoDomain is effectively a transform node, but ONLY affects MeshViz nodes.
 *  If you want the PoDomain transform to apply to other geometry, use the
 *  getTransform() method to get an SoTransform node and insert that node in the
 *  scene graph above the other geometry.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoDomain {
 *    @TABLE_FILE_FORMAT
 *       @TR min @TD 0 0 0
 *       @TR max @TD 1 1 1
 *       @TR transformType @TD SCALE_X_FIXED
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoDomain : public PoNode {

  SO_NODE_HEADER(PoDomain) ;
  

 public:

  /**
   *  Transform type.
   */
  enum TransformType {
    TRANSFORM_01,
    SCALE_X_FIXED,
    SCALE_Y_FIXED,
    SCALE_Z_FIXED,
    SCALE_MAX_XYZ_FIXED
  } ;

  /**
   *  Bounding box interpretation.
   */
  enum BoundingBoxType {
    AS_IS,
    MIN_BOUNDING_CUBE,
    MAX_BOUNDED_CUBE
  } ;

  

  /* Fields */

  /**
   * Define the minimum of the domain.
   */
  SoSFVec3f min ;

  /**
   * Define the maximum of the domain.
   */
  SoSFVec3f max ;

  /**
   * Define the transformation type of the domain.
   */
  SoSFEnum  transformType ;

  /* Methods */

  /**
   * Convenience method to define a 2D domain.
   */
  void setValues(const SbVec2f &min, const SbVec2f &max, BoundingBoxType type = AS_IS) ;

  /**
   * Convenience method to define a 3D domain.
   */
  void setValues(const SbVec3f &min, const SbVec3f &max, BoundingBoxType type = AS_IS) ;

  /**
   * Get the domain transform matrix in an SoTransform object.
   */
  SoTransform*       getTransform() ;

  /**
   * Get the domain transform matrix in an SbMatrix object.
   */
  SoMatrixTransform* getMatrixTransform() ;

  /**
   * Constructor.
   */
  PoDomain() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoDomain() ;

 private:
  void updateDomain() ;

  static void minMaxChangedCB(void *data, SoSensor *) ;
  static void transformTypeChangeCB(void *data, SoSensor *) ;

  SbBool          m_minMaxChanged, m_transformTypeChanged ;
  PbDomain        *m_domain ;
  SoFieldSensor   *m_minSensor ;
  SoFieldSensor   *m_maxSensor ;
  SoFieldSensor   *m_transformTypeSensor ;
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_DOMAIN_  */

