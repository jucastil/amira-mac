/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/

#ifndef _SB_PROJECTION_
#define _SB_PROJECTION_

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h> 

#include <Inventor/STL/vector> 

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 ) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif

#define NUM_MAX_PARAMS 256
#define MAX_PARAM_LENGTH 256

class SoProjection;

/**
 * Base class for coordinate projection classes.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This is the base class for classes that define a coordinate projection.
 *  The projection of a point P consists of computing a point P' and replacing internally 
 *  the coordinates of P with the coordinates of P'.  Projections can modify points in
 *  complex ways that are not possible with a transformation matrix.  For example,
 *  projections allow the use of spherical coordinates, geospatial coordinates and others.
 *  An SoProjection node applies a coordinate projection to geometry nodes.
 *  A valid instance of a SbProjection class is needed by an SoProjection node put
 *  in a scene graph.
 *
 *  To create a new projection class, implement a class inheriting from SbProjection.
 *  The only mandatory method to define a projection is the apply() method.
 *  To obtain the result of a projected point, call the project() method, 
 *  which internally computes the result and calls apply().
 *  You can also define the inverse() method, which is only used for applications
 *  that must compute the inverse of a projected point.
 *
 *  The applyPreProjection() method can be defined and will be called just before
 *  a point is projected.
 *  The applyPostProjection() method can be defined and will be called just after a 
 *  point has been projected.
 *
 *  A projection class stores a list of string parameters and a list of float parameters.
 *  You can set or inquire a parameter using setParameter() or getParameter()
 *
 *  The projection routine can get parameter values from the fields of the associated SoProjection 
 *  node (if any). The parameters for a projection should be stored in the SoProjection node, 
 *  as it is the only entry in the scene graph.  The SoProjection::floatParameters field stores
 *  the float values that are synchronized with the float parameters of the projection class.
 *  The SoProjection::parameters field stores the string values that are synchronized with the 
 *  string parameters of the projection class.
 *
 *  The init() method is called each time a parameter of the associated SoProjection node 
 *  is modified.  The exit() method is called at the SbProjection instance destruction.
 *
 *  If using the VolumeViz extension, defining the getProjectedBoundingBox() method
 *  will improve the rendering speed (see #getProjectedBoundingBox comments).
 *
 * @SEE_ALSO
 * 
 *  SbProj4Projection,
 *  SbSphericalProjection,
 *  SoProjection,
 *  SoGeoProjection,
 *  SbProjectionCoordinates
 *  
 * 
 */

class INVENTOR_API SbProjection
{

public:

  /**
  * Constructor
  */
  SbProjection();

  /**
  * Constructor
  */
  SbProjection(SoProjection *node);

  /**
  * Copy constructor.
  */
  SbProjection(const SbProjection &proj);

  /**
  * Destructor.
  */
  virtual ~SbProjection();

  /**
  * Initialisation method. 
  */
  virtual void init(){}

  /**
  * Exit method.
  */
  virtual void exit(){}
 
  /**
  * Apply the inverse coordinate to one point.  Modifies the given object.
  */
  virtual void inverse(SbVec3f &point);

  /**
  * Return projected bounding box if available.
  * 
  * Note: Projecting a bounding box is most of the time not equivalent to the result of 
  * a bounding box that contains all projected point. 
  *
  * It depends on the projection, and it is why by default it returns false, 
  * and should be redefined by the specific inherited projection class if it make sense.
  *
  */
  virtual bool getProjectedBoundingBox(SbBox3f& bbox);

  /**
  * Apply the complete computation (matrix, pre-projection, 
  * projection, post-projection) to one point.  Modifies the given object.
  */
  void project(SbVec3f &point);

  /**
  * Apply the complete computation to a set of points.  Modifies the given objects.
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void project( int numPoints, float *points);

  /**
  * Apply the complete computation to a set of coordinates.
  * [OIV-WRAPPER-ARG NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY,ARRAY]
  * [OIV-WRAPPER-HELPER BEGIN{System::Diagnostics::Debug::Assert((coords == projectedCoords) || (coords != NULL && projectedCoords != NULL && coords->Length <= projectedCoords->Length))}]
  */
  void project(int32_t numCoords, const SbVec3f *coords, SbVec3f *projectedCoords);

  /**
  * Return associated projection node.
  */
  inline SoProjection *getProjectionNode() const
  {return m_projection;}

  /**
  * Set string parameter. 
  */
  virtual void setParameter( int parameterId, const SbString &parameterString );

  /**
  * Set float parameter. 
  */
  virtual void setParameter( int parameterId, const float &parameterFloat );

  /**
  * Set number of string parameters to use.
  */
  void setNumStringParameters( int numParameters );

  /**
  * Set number of float parameters to use.
  */
  void setNumFloatParameters( int numParameters );

  /**
  * Get number of used string parameters.
  */
  int getNumStringParameters() const;

  /**
  * Get number of used float parameters.
  */
  int getNumFloatParameters() const;

  /**
  * Get string parameter at position pos.
  * [OIVJAVA-WRAPPER NAME{getStringParameter}]
  */
  SbBool getParameter( int pos, SbString& parameter ) const;

  /**
  * Get float parameter at position pos.
  * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{throw new IllegalArgumentException()}]
  * [OIVJAVA-WRAPPER NAME{getFloatParameter}]
  */
  SbBool getParameter( int pos, float& parameter ) const;

SoEXTENDER_Documented protected:
  /**
  * Apply the coordinate projection to one point.   Modifies the given object.
  */
  virtual void apply(SbVec3f &point);

  /**
  * Method called before the projection computation if redefined.  Modifies the given object.
  */
  virtual void applyPreProjection( SbVec3f &point );

  /**
  * Method called after the projection computation if redefined. Modifies the given object.
  */
  virtual void applyPostProjection( SbVec3f &point );

SoINTERNAL public:

  /**
  * Set string parameter. If notifyNode is TRUE, add parameter to the node. 
  * If callInit is TRUE, call the init() method.
  */
  virtual void internalSetParameter( int parameterId, const SbString &parameterString, SbBool notifyNode = TRUE, SbBool callInit = TRUE);

  /**
  * Set float parameter. If notifyNode is TRUE, add parameter to the node. 
  * If callInit is TRUE, call the init() method.
  */
  virtual void internalSetParameter( int parameterId, const float &parameterString, SbBool notifyNode = TRUE, SbBool callInit = TRUE);

  /**
  * Set input string parameter. If notifyNode is TRUE, add parameter to the node. 
  * If callInit is TRUE, call the init() method.
  */
  virtual void internalSetParameterIn( int parameterId, const SbString &parameterString, SbBool notifyNode = TRUE, SbBool callInit = TRUE);

  //copy the parameters to the projection node.
  void copyParams();

protected:

  //initialisation of parameters.
  void initParameters();

  //synchronization with node.
  void afterSettingParameters( SbBool notifyNode, SbBool callInit );

  //string parameters list.
  char *m_stringParameters[NUM_MAX_PARAMS];

  //number of used string params.
  int m_numStringParams;

  //string parameters list.
  char *m_stringParametersIn[NUM_MAX_PARAMS];

  //number of used string params.
  int m_numStringParamsIn;

  //Float parameters.
  std::vector< float > m_floatParameters;

  //Apply matrix before projecting.
  void applyMatrix(SbVec3f &point);

  static const double deg2rad;
  static const double rad2deg;

private:
  /// Projection node.
  SoProjection *m_projection;
};


inline void SbProjection::apply(SbVec3f &)
{}

inline void SbProjection::inverse(SbVec3f &)
{}

inline void SbProjection::applyPreProjection( SbVec3f &)
{}

inline void SbProjection::applyPostProjection( SbVec3f &)
{}

inline bool SbProjection::getProjectedBoundingBox(SbBox3f& ) 
{ return false; }

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif /* _SB_PROJECTION_ */
