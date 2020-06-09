/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_NORMAL_GENERATOR_
#define  _SO_NORMAL_GENERATOR_

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoNeighborToleranceElement.h>

/**
* Surface normal generator.
*
* @ingroup General
*
* @DESCRIPTION
*  This class can be used by polyhedral shape classes to generate
*  surface normals when they do not have valid ones specified. To
*  generate normals, create an instance of this class, then specify
*  each polygon in the shape, then call generate(). After generate()
*  is called, the normals can be accessed from the instance. There
*  will be one normal generated for each vertex of each polygon, in
*  the order passed in.
*
*  For convenience, there is a method to send down a triangle of
*  vertices.
*
*  For efficiency, a constructor is provided that takes an
*  approximate number of vertices that will be specified. Use this
*  constructor if you know roughly how many vertices will be sent;
*  this will cut down on allocation overhead.
*
*  The generate() method takes a crease angle that is used to
*  determine whether to create normals that simulate a sharp crease
*  at an edge between two polygons or to create normals that simulate
*  smooth shading over the edge. The crease angle is the minimum
*  angle (in radians) between the face normals on either side of an
*  edge that will be used to consider the edge a crease. For example,
*  a crease angle of pi/4 radians (45 degrees) means that adjacent
*  face normals must be within 45 degrees of each other for the edge
*  to be shaded smoothly.
*
*  @B NOTE @b The SoNormalGenerator destructor DOES NOT delete the
*  array of generated normals. The caller is responsible for doing
*  so. This allows the normals to be cached elsewhere without having
*  to copy them.
*
*/

SoEXTENDER class INVENTOR_API SoNormalGenerator {

 public:
  /**
   * Constructor.
   */
   SoNormalGenerator(
     const SbBool isCCW,
     const int approxNumVertices=16,
     const int approxNumFaces=6,
     const float creaseAngle =0.0f,
     const float toleranceFactor = SoNeighborToleranceElement::getDefault()
     );

  /**
   * Destructor.
   */
  ~SoNormalGenerator();

  /**
   * Resets the approximative number of vertices and faces that
   * we have to generate normals for. These correspond to the same parameters in 
   * the constructor, but allows setting them after creation. @BR
   * Note: Must be called before first call to polygonVertex or triangle calls..
   */
  void setupApproxShapeSize(const int32_t approxNumVertices,const int32_t approxNumFaces);

  /**
   * Send a polygon's worth of vertices. Begin a polygon, send as
   * many vertices as you want, and then end the polygon.
   */
  void beginPolygon();
  void polygonVertex(const SbVec3f &point);
  void endPolygon();

  /** Send a triangle */
  void triangle(const SbVec3f &p1,const SbVec3f &p2,const SbVec3f &p3);

  /**
   * Specifies a pointer to the array of points that will be used
   * in subsequent calls to polygonVertex(index) and triangle(index1,index2,index3). @BR
   *
   * Using this mode allows reusing vertices, avoiding data copy and increasing performance.
   * IMPORTANT NOTE:
   * - This function should be called before any call to polygonVertex/triangle functions.
   * - The data should remain valid until generate() has ended.
   * - Once setupIndexedVertexArray has been called, only "by index" functions are valid.
   */
  void setupIndexedVertexArray(const SbVec3f* pointArray);

  /** 
   * Specifies a per-vertex connectivity array. @BR
   * This array should be dimensioned the number of vertices, and represent a double link list of
   * connectivity for each vertex.
  */
  void setupIndexedConnectivity(const int32_t* connectivityArray);

  /**
   * Send a polygon's worth of vertices using indexed vertices. @BR
   * NOTE: must be called after setupIndexedVertexArray().
   */
  void polygonVertex(const int32_t pointIndex);

  /** 
   * Send a triangle using indexed vertices. @BR
   * NOTE: must be called after setupIndexedVertexArray().
   */
  void triangle(const int32_t index1,const int32_t index2,const int32_t index3);

  /** Calculate the normals once all vertices have been sent */
  void generate();

  /**
   * Returns number of normals generated. @BR
   * This will be equal to the number of points sent. @BR
   * NOTE: must be called after generate().
   */
  int getNumNormals() const   { return numVertNormals; }

  /** 
   * Truncate the array so there are only the given number of normals. @BR
   * NOTE: must be called after generate().
   */
  void setNumNormals(int newNum);

  /**
   * Returns a pointer to the array of normals. @BR
   * NOTE: must be called after generate().
   */
  const SbVec3f *getNormals() const
  { return vertNormals; }

  /**
   * Returns the i'th normal in the array. @BR
   * NOTE: must be called after generate().
   */
  const SbVec3f & getNormal(int32_t i) const
  { return vertNormals[i]; }

  /**
   * Add or modify a normal vector. @BR
   * Some shapes may need to adjust or reorder normals after
   * generation. This method can be used to change a normal. It will
   * insert room in the array if necessary to accommodate the new
   * normal.
   * NOTE: must be called after generate().
   */
  void setNormal(int32_t index, const SbVec3f &newNormal);

  /** 
   * Returns the number of connected points that have different normals. @BR
   * If 0 then the shape is fully smooth and using 
   * indexed normals could be an optimization for the caller. @BR
   *  if -1 this info is not available.
   */
  int32_t numNormalCrack() const
  {return m_numNormalCrack; };

SoINTERNAL public:
  /*
   * Some shapes may need to adjust or reorder all normals after
   * generation. This method can be used to change all normal in one 
   * shot without any copy. 
   */
  void setNormalBuffer(int32_t numNormals, const SbVec3f *normals);

  /**
   * return TRUE if shape was indexed
   */
  bool isIndexedMode() const
  {return m_isIndexedMode; }

 private:
  // Arrays of vertex points, face normals, and vertex normals. The
  // face normals are stored one per vertex. The other vars are the
  // number of items in the arrays, and the allocated sizes of the
  // arrays. Since the points and faceNormals arrays are always the
  // same size, no need for extra variables.
  // Depending on setupIndexedVertexArray call or not, data are used 
  // from points or pointsIndex array.
  SbVec3f             *points, *faceNormals, *vertNormals;
  int32_t             *pointIndexes;
  int32_t             numPoints, numVertNormals;
  int32_t             maxPoints, maxFaceNormals, maxVertNormals;
  SbVec3f             polygonSum;

  // Flag: if TRUE, polygons are oriented counter-clockwise
  SbBool              m_isCCW;
  float               m_creaseAngle;
  float               m_toleranceFactor;

  int32_t             m_approxNumVertices;
  int32_t             m_approxNumFaces;
  int32_t             m_faceIndex;
  int32_t             m_pointIndex;

  // Index into points array where current polygon started
  int32_t             beginPolygonIndex;
  SbBox3f	            m_bbox;

  // 
  int                 m_numNormalCrack;
  bool                m_isIndexedMode;
  int32_t             *m_userConnectivity;

  // grow point or pointsIndexes array depending on current number of point.
  void growPointsArray(const int requestedMaxPoints);
  // grow current facenormals array .
  void growNormalFaceArray(const int requestedNormalFaceArraySize);


  inline bool needToComputeConnectivity() const
  { return (( m_creaseAngle != 0.0f ) && ( m_userConnectivity == NULL )); }

  // compute a double link list of point that are connected.
  // the resulting array has a size of numPoints
  // the caller is responsible fro release this memory.
  int32_t* computeConnectivity();

  // Returns TRUE if the two points are the same within given tolerance
  static SbBool equal(const SbVec3f &a, const SbVec3f &b, const float tol);

  static SbBool s_useOldTolerance;
};

#endif /* _SO_NORMAL_GENERATOR_ */
