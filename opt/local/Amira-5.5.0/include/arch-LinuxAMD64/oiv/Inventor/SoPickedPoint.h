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


#ifndef _SO_PICKED_POINT_
#define _SO_PICKED_POINT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoLists.h>

class SoDetail;
class SoGetMatrixAction;
class SoPath;
class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickedPoint
//
//  An SoPickedPoint represents a point on the surface of an object
//  that was picked by applying an SoRayPickAction to a scene. It
//  contains the point of intersection, the surface normal and texture
//  coordinates at that point, and other items.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Represents point on surface of picked object.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   An SoPickedPoint represents a point on the surface of an object that was picked
 *   by applying an SoRayPickAction to a scene. It contains a path to the picked
 *   shape, the point of intersection, the surface normal and texture coordinates at
 *   that point, and other information.  Note that it is not always necessary to
 *   explicitly apply an SoRayPickAction to the scene.  The getPickedPoint method may
 *   also be called on an SoHandleEventAction or an SoEventCallback node.
 *   
 *   Each node in the picked path may have a corresponding instance of a detail
 *   subclass. These detail instances are stored in the SoPickedPoint.
 * 
 * @SEE_ALSO
 *    SoRayPickAction,
 *    SoPickStyle,
 *    SoDetail,
 *    SoPath,
 *    SoEventCallback
 * 
 * 
 */ 

class INVENTOR_API SoPickedPoint {

 public:
  /**
   * Default constructor.
   */
  SoPickedPoint();

  /**
   * Copy constructor.
   */
  SoPickedPoint(const SoPickedPoint &pp);

  /**
   * Destructor.
   */
  ~SoPickedPoint();

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  SoPickedPoint *     copy() const;

  /**
   * Returns the intersection point in world space.
   */
  const SbVec3f &     getPoint() const         { return worldPoint; }
  /**
   * Returns the surface normal in world space.
   */
  const SbVec3f &     getNormal() const        { return worldNormal; }
  /**
   * Returns the texture coordinates in image space.
   */
  const SbVec4f &     getTextureCoords() const { return imageTexCoords; }

  /**
   * Returns the index into the current set of materials of the material active at
   * the intersection point. Note that if the materials are interpolated between
   * vertices, the index will correspond to the material at one of the vertices.
   */
  int                 getMaterialIndex() const { return materialIndex; }

  /**
   * Returns the path to the object that was intersected.
   */
  SoPath *            getPath() const          { return path; }

  /**
   * Returns whether the intersection is actually on the geometry of the character
   * that was hit, as opposed to being on the bounding box. The pick style (see
   * SoPickStyle) affects this decision.
   */
  SbBool              isOnGeometry() const     { return onGeometry; }

  //////////////////////
  //
  // The following methods all take a pointer to a node in the
  // returned path. If the node pointer is NULL (the default), the
  // information corresponding to the tail of the path is returned.
  //

#ifdef OIV_NET_DOC
  /**
  * Returns the detail that corresponds to the given node in the path returned by
  * getPath(). If the node reference is NULL (the default), the detail
  * corresponding to the tail of the (full) path is returned.
  */

#else
  /**
  * Returns the detail that corresponds to the given node in the path returned by
  * getPath(). If the node pointer is NULL (the default), the detail
  * corresponding to the tail of the (full) path is returned.
  */

#endif //OIV_NET_DOC
  const SoDetail *    getDetail(const SoNode *node = NULL) const;

#ifdef OIV_NET_DOC
  /**
  * Returns the transformation matrix between the object space and world
  * space corresponding to the given node in the path. If the node reference is NULL
  * (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#else
  /**
  * Returns the transformation matrix between the object space and world
  * space corresponding to the given node in the path. If the node pointer is NULL
  * (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#endif //OIV_NET_DOC
  SbMatrix            getObjectToWorld(const SoNode *node = NULL) const;
#ifdef OIV_NET_DOC
  /**
  * Returns the transformation matrix between world space and the object
  * space corresponding to the given node in the path. If the node reference is NULL
  * (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#else
  /**
  * Returns the transformation matrix between world space and the object
  * space corresponding to the given node in the path. If the node pointer is NULL
  * (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#endif //OIV_NET_DOC
  SbMatrix            getWorldToObject(const SoNode *node = NULL) const;

#ifdef OIV_NET_DOC
  /**
  * Returns the texture transformation matrix between the object space and 
  * image space corresponding to the given node in the path. If the node reference is
  * NULL (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#else
  /**
  * Returns the texture transformation matrix between the object space and 
  * image space corresponding to the given node in the path. If the node pointer is
  * NULL (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#endif //OIV_NET_DOC
  SbMatrix            getObjectToImage(const SoNode *node = NULL) const;
#ifdef OIV_NET_DOC
  /**
  * Returns the texture transformation matrix between image space and the
  * object space corresponding to the given node in the path. If the node reference is
  * NULL (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#else
  /**
  * Returns the texture transformation matrix between image space and the
  * object space corresponding to the given node in the path. If the node pointer is
  * NULL (the default), the matrix corresponding to the tail of the (full) path is
  * returned.
  */

#endif //OIV_NET_DOC
  SbMatrix            getImageToObject(const SoNode *node = NULL) const;

#ifdef OIV_NET_DOC
  /**
  * Returns the intersection point in
  * the object space corresponding to the given node in the path. If the node
  * reference is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#else
  /**
  * Returns the intersection point in
  * the object space corresponding to the given node in the path. If the node
  * pointer is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#endif //OIV_NET_DOC
  SbVec3f             getObjectPoint(const SoNode *node = NULL) const;
#ifdef OIV_NET_DOC
  /**
  * Returns the surface normal in
  * the object space corresponding to the given node in the path. If the node
  * reference is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#else
  /**
  * Returns the surface normal in
  * the object space corresponding to the given node in the path. If the node
  * pointer is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#endif //OIV_NET_DOC
  SbVec3f             getObjectNormal(const SoNode *node = NULL) const;
#ifdef OIV_NET_DOC
  /**
  * Returns the texture coordinates in
  * the object space corresponding to the given node in the path. If the node
  * reference is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#else
  /**
  * Returns the texture coordinates in
  * the object space corresponding to the given node in the path. If the node
  * pointer is NULL (the default), the information corresponding to the tail of the
  * (full) path is returned.
  */

#endif //OIV_NET_DOC
  SbVec4f             getObjectTextureCoords(const SoNode *node=NULL) const;

  //
  //////////////////////

 SoEXTENDER public:

  // NOTE: these methods should be called ONLY by the node that
  // causes the SoPickedPoint instance to be created, and ONLY at
  // the time it is created. Setting or changing the normal or
  // texture coordinates at a later time may cause undefined results.

  // Sets the normal in object space
  void                setObjectNormal(const SbVec3f &normal);

  // Sets the texture coordinates in object space
  void                setObjectTextureCoords(const SbVec4f &texCoords);

  // Sets the material index
  void                setMaterialIndex(int index)  { materialIndex = index; }

  // Sets the detail corresponding to the given node in the path.
  // NULL may be passed to remove a detail. All detail pointers are
  // NULL by default.
  void                setDetail(SoDetail *detail, SoNode *node);

 SoINTERNAL public:

  // The constructor is internal since instances are created only by
  // the SoRayPickAction
  SoPickedPoint(const SoPath *path, SoState *state,
                const SbVec3f &objSpacePoint);

  // override the current path this is usefull for alternat representation 
  void overridePath(const SoPath* _path);

 private:
  // This action is used to get the world-to-object matrix
  SoGetMatrixAction   *matrixAction;

  // Intersection point and normal in world space, and texture
  // coordinates in image space
  SbVec3f             worldPoint;
  SbVec3f             worldNormal;
  SbVec4f             imageTexCoords;

  // ViewportRegion, which is needed when figuring out matrices
  SbViewportRegion    vpRegion;

  // Material index
  int                 materialIndex;

  // TRUE if pick was on geometry of shape as opposed to bbox
  SbBool              onGeometry;

  // The path to the shape that was picked
  SoPath              *path;

  // Details corresponding to nodes in path, one per node in path.
  // Many may be NULL.
  SoDetailList        details;

  // The pointer to the state allows us to access matrices to
  // convert from object space to world and image space. This
  // pointer is valid only during construction and setting of the
  // info inside the instance.
  SoState             *state;

  // Returns index in path of given node, or -1 if not found
  int                 getNodeIndex(const SoNode *node) const;

  // Applies SoGetMatrixAction to path to node
  void                getMatrix(const SoNode *node) const;

  // Multiplies SbVec4f by matrix - for transforming texture coords
  static SbVec4f multVecMatrix4(const SbMatrix &m, const SbVec4f v);

};

#endif /* _SO_PICKED_POINT_ */

