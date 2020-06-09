/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/


#ifndef  _SO_PROJECTION_
#define  _SO_PROJECTION_

#include <Inventor/fields/SoSFBool.h> 
#include <Inventor/fields/SoMFFloat.h> 
#include <Inventor/fields/SoMFVec3f.h> 
#include <Inventor/fields/SoMFString.h> 
#include <Inventor/fields/SoSFFloat.h> 
#include <Inventor/fields/SoSFEnum.h> 
#include <Inventor/fields/SoSFMatrix.h> 

#include <Inventor/STL/vector>
#include <Inventor/projection/SbProjection.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoHandleEventAction.h>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif

class SoFieldSensor;
class SbSphericalProjection;

/**
 * @VSGEXT Coordinate projection node
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *
 *  This property node defines a coordinate projection that will be applied 
 *  to all subsequent shapes in the scene graph.  Coordinate transform nodes
 *  like SoTransform can only apply transforms that can be expressed as a
 *  matrix. A coordinate projection can be any algorithm that takes a coordinate
 *  and returns a different coordinate.  This is particularly useful for geospatial
 *  coordinate systems (see SoGeoProjection), but is also useful for using
 *  spherical, cylindrical and other coordinate systems directly.
 *  
 *  This node works together with projection classes derived from the SbProjection class.
 *  The projection classes implement the projection computations applied to 3D points.
 *  Applications can create new subclasses of SbProjection.
 *
 *  To use a specific projection, call setProjection() with an instance of the 
 *  SbProjection class. Each instance of SoProjection can also store a list of projections,
 *  each one associated with a unique id. This is convenient for switching between
 *  different geospatial projections. Changing the #projTypeId value activates the 
 *  projection registered with the corresponding id.
 *
 *  The default projection is spherical coordinates (SbSphericalProjection).
 *
 *  The projection classes will use the string parameters and float parameters in the 
 *  fields #parameters and #floatParameters respectively.  See the projection class
 *  documentation for relevant parameters.
 *
 *  @B LIMITATIONS @b
 *
 *  The following shapes are @B not @b supported by SoProjection:
 *
 *    - Text nodes (SoAnnoText3, SoAsciiText, SoText2, SoText3 )
 *    - SoCylinder
 *    - SoImage
 *    - NURBS shapes
 *    - VRML shapes (nodes derived from SoVRMLGeometry)
 *    - All VolumeViz shapes except SoVolumeRender with some limitations (see SoVolumeRender doc for details)
 *
 *  The projection mechanism is not compatible with transform and manipulator nodes.
 *  Using nodes derived from SoTransformation, for example SoTransform or SoTabBoxManip will 
 *  give unexpected results.  To apply a transformation matrix to projected shapes, set the 
 *  matrix field to the expected value.  Shape vertices will be multiplied by the matrix 
 *  before being projected.
 *
 *  Because draggers are composed with SoTransformation nodes, they can't be projected using an 
 *  SoProjection node.
 *
 *  Because shape coordinates must be duplicated, memory consumption will increase when using 
 *  projections.
 *
 *  @FILE_FORMAT_DEFAULT
 *    Projection {
 *    @TABLE_FILE_FORMAT
 *       @TR parameters           @TD ""
 *       @TR matrix               @TD identity
 *       @TR isOn                 @TD true
 *       @TR floatParameters      @TD 1
 *       @TR projTypeId           @TD 0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *        Sets: SoCoordinateElement
 * 
 * @SEE_ALSO
 *  SbProjection,
 *  SbSphericalProjection,
 *  SoGeoProjection
 *
 * 
 */ 
class INVENTOR_API SoProjection : public SoNode 
{

  SO_NODE_HEADER( SoProjection );

public:

  /**
  * Constructor
  */
  SoProjection();

  /**
  * If set to FALSE, projection is inactive.  Default is TRUE.
  */
  SoSFBool isOn;

  /**
  * Matrix that can be applied before projecting a point. Set to Identity by default
  */
  SoSFMatrix matrix;

  /**
  * Current projection id.  Default is zero.
  * 
  */
  SoSFInt32 projTypeId;

  /**
  * Float parameters stored for projections.
  */
  SoMFFloat floatParameters;

  /**
  * String parameters stored for projections.
  */
  SoMFString parameters;

  /**
  * String parameters stored for projections.
  */
  SoMFString parametersIn;

  /**
  * Add a projection with the given name and id to the list.
  * The projection name is just for convenience.  The projection id value
  * should be greater than zero because the default spherical projection
  * already uses this id. If multiple projections are assigned the same
  * id, the first one added to the list will be used.
  */
  void addProjection( SbString &projectionName, SbProjection *projection , int id);

  /**
  * Set the current projection.
  * The specified projection is used regardless of whether it is in the list.
  * In this case the value of the projTypeId field is not used.
  */
  void setProjection( SbProjection *projection );

  /**
  * Return current projection name and id.
  */
  void getCurrentProjectionInfos(SbString &name, int &id);

  /**
  * Return current projection.
  */
  inline SbProjection* getProjection() const
  { return m_projection; }

  /**
  * Apply projection to given coordinates.
  * Store projected coordinates in current SoCoordinate3 element.
  * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY]
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{(coords != NULL? coords->Length: 0)}]
  */
  static SbVec3f * checkProjection( SoState *state,
    SoNode *node,
    int32_t numCoords,
    const SbVec3f *coords);

  SoEXTENDER public:
  virtual void        doAction        ( SoAction *action );
  virtual void        GLRender        ( SoGLRenderAction *action ){ return doAction( action );}
  virtual void        callback        ( SoCallbackAction *action ){ return doAction( action );}
  virtual void        getBoundingBox  ( SoGetBoundingBoxAction *action ){ return doAction( action );}
  virtual void        getMatrix       ( SoGetMatrixAction *action ){ return doAction( action );}
  virtual void        handleEvent     ( SoHandleEventAction *action ){ return doAction( action );}
  virtual void        pick            ( SoPickAction *action ){ return doAction( action );}
  virtual void        rayPick         ( SoRayPickAction *action ){ return doAction( action );}

  SoINTERNAL public:

  static void         initClass();
  static void         exitClass();

  static SbBool getLocalPoint( SoState* state, SbVec3f &point);

  /**
  * Check projection for given point.
  */
  static void checkProjection( SoState* state, SbVec3f &point, SbBool inverse= FALSE);

  /**
  * Apply projection to given coords
  * Store projected coords in current Coordinate element
  */
  bool checkProjection( SoNode *node, SoAction *action, SoMFVec3f &coords );

  /**
  * Reset projection : put initial coordinates in current SoCoordinate3 element.
  */
  void resetProjection( SoAction *action, SoMFVec3f &coords);

  /**
  * Set input projection pamameters.
  */
  void setParametersIn( SoMFString &parameters);

  /**
  * fields sensor Callbacks
  */
  static void parametersChangedCB( void *data, SoSensor* );

  static void typeIdChangedCB( void *data, SoSensor* );

protected:

  // Destructor
  virtual ~SoProjection();

  // ids
  std::vector< int > m_projIds;

  // names
  std::vector< SbString > m_projNames;

  // associated projections
  std::vector< SbProjection *> m_projections;

  // current projection
  SbProjection* m_projection;

  // created spherical projection
  SbSphericalProjection* m_sphericalProjection;

  // coords used for temporary check
  SbVec3f* m_storedCoords;

  SbBool m_enableDeleteValues;

  // Field sensors
  SoFieldSensor* m_parameterSensor;

  SoFieldSensor* m_floatParameterSensor;

  //Called if projection type id has changed
  SoFieldSensor* m_projTypeIdSensor;
};

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif /* _SO_PROJECTION_ */

