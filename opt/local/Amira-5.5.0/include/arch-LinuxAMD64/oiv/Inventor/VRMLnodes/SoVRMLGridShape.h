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


#ifndef  _SO_VRMLGRID_SHAPE_
#define  _SO_VRMLGRID_SHAPE_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/VRMLnodes/SoVRMLCoordinate.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/threads/SbThreadRWMutex.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLGridShape
//
//  Abstract vertex-based shape node class. All nodes derived from
//  this class are shapes that are constructed from vertices at some
//  or all of the current coordinates.  They all have vertexProperty nodes,
//  and vpCaches.
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;
class SoNormalCache;
class SoState;

/**
 * @VSGEXT Abstract base class for the SoVRMLElevationGrid node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node is an abstract base class for the SoVRMLElevationGrid node.
 *
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page of a derived
 *   class for the format and default values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoPickAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoMFFloat  @TD   set_height      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLGridShape : public SoVRMLGeometry {

  SO_NODE_ABSTRACT_HEADER(SoVRMLGridShape);
    
 public:
  /**
   * Number of divisions of the grid in the Z direction.
   * 
   */
  SoSFInt32           zDimension;
  /**
   * Number of divisions of the grid in the X direction.
   * 
   */
  SoSFInt32           xDimension;
  /**
   * Distance between the vertices in the Z direction.
   * 
   */
  SoSFFloat           zSpacing;
  /**
   * Distance between the vertices in the X direction.
   * 
   */
  SoSFFloat           xSpacing;
  /**
   * xDimension by zDimension array of scale factors representing the height above
   * the grid for each vertex. The heights are stored in row major order.
   * 
   */
  SoMFFloat           height;
  /**
   * An SoVRMLTextureCoordinate node.
   * 
   */
  SoSFNode            texCoord;
  /**
   * An SoVRMLNormalNode containing the normals. If NULL, the normals will be
   * automatically generated.
   * 
   */
  SoSFNode            normal;
  /**
   * An SoVRMLColor node whose colors are applied to the vertices or faces of the
   * ElevationGrid.
   * 
   */
  SoSFNode            color;
  /**
   * If TRUE, colors are applied to the vertices of the ElevationGrid. If FALSE, the
   * colors are applied to the faces.
   * 
   */
  SoSFBool            colorPerVertex;
  /**
   * If TRUE, normals are applied to the vertices of the ElevationGrid. If FALSE, the
   * normals are applied to the faces.
   * 
   */
  SoSFBool            normalPerVertex;

 SoEXTENDER public:

  enum Binding {
    OVERALL =               SoMaterialBindingElement::OVERALL,
    PER_PART =              SoMaterialBindingElement::PER_PART,
    PER_PART_INDEXED =      SoMaterialBindingElement::PER_PART_INDEXED,
    PER_FACE =              SoMaterialBindingElement::PER_FACE,
    PER_FACE_INDEXED =      SoMaterialBindingElement::PER_FACE_INDEXED,
    PER_VERTEX =            SoMaterialBindingElement::PER_VERTEX,
    PER_VERTEX_INDEXED =    SoMaterialBindingElement::PER_VERTEX_INDEXED
  };
  // Subclasses may define this method to generate normals to use
  // when the normal binding is DEFAULT and there aren't enough
  // normals in the state. This should use the given SoNormalBundle
  // to generate the normals. Returns TRUE if normals were generated.
  virtual SbBool      generateDefaultNormals(SoState *state,
                                             SoNormalBundle *nb);

 SoINTERNAL public:
  SoMFUInt32  orderedrgba;
  unsigned char normalBinding;
  unsigned char materialBinding;
  SoVRMLCoordinate     *myCoord;
  static void         initClass();
  static void         exitClass();
  virtual void        doAction(SoAction *action);
  virtual void        search(SoSearchAction *action);
  //virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);

  virtual SoChildList *getChildren() const;

  virtual SbBool      validateNewFieldValue(SoField *pField,
                                            void *newValue);

  // Redefines this to invalidate normal cache
  virtual void        notify(SoNotList *list);

  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

 protected:
  // Constructor - makes this abstract
  SoVRMLGridShape();

  virtual ~SoVRMLGridShape();
    
  // Returns TRUE if the shape should be rendered. 
  // Checks for transparency in vertexProperty node before invoking
  // render action.
  virtual SbBool      shouldGLRender(SoGLRenderAction *action,
                                     SbBool isPointsOrLines);

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVRMLVertexPropertyCache   vpCache;

  // Sets up a cache to hold normals. This assumes the cache depends
  // on only the current coordinates, shape hints, and crease angle.
  void                setNormalCache(SoState *state,
                                     int numNormals, 
                                     const SbVec3f *normals,
                                     const SoNormalBindingElement::Binding binding
                                     );

  // Returns the current normal cache, or NULL if there is none
  SoNormalCache       *getNormalCache() const { return normalCache; }

  // Hack to make paths work for VRML nodes that contain other nodes
  // in their fields...  Nov-96
  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

  // Mutex to protect access to the normalCache
  SbThreadRWMutex *normalCacheMutex;

 private:
  void                rebuildChildrenList();

  // This allows instances to cache normals that have been generated
  SoNormalCache       *normalCache;
 
};

#endif /* _SO_VRMLGRID_SHAPE_ */

