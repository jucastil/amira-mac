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


#ifndef  _SO_VRMLVERTEX_SHAPE_
#define  _SO_VRMLVERTEX_SHAPE_

#include <Inventor/SbBasic.h>

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/threads/SbThreadRWMutex.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLVertexShape
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
 * @VSGEXT Abstract base class for various geometry nodes. 
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   SoVRMLVertexShape is an abstract base class for the SoVRMLIndexedFaceSet node.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract base class. See the derived class for the format and
 *   default values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord      
 *       @TR   SoSFNode   @TD   set_normal      
 *       @TR   SoSFNode   @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed      
 *       @TR   SoSFNode   @TD   normal_changed      
 *       @TR   SoSFNode   @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLVertexShape : public SoVRMLGeometry {

  SO_NODE_ABSTRACT_HEADER(SoVRMLVertexShape);
    
 public:
  /**
   * An SoVRMLCoordinate node defining the IndexedFaceSet.
   * 
   */
  SoSFNode            coord;
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
   * IndexedFaceSet.
   * 
   */
  SoSFNode            color;
  /**
   * If TRUE, colors are applied to the vertices of the IndexedFaceSet. If FALSE, the
   * colors are applied to the faces.
   * 
   */
  SoSFBool            colorPerVertex;
  /**
   * If TRUE, normals are applied to the vertices of the IndexedFaceSet. If FALSE,
   * the normals are applied to the faces.
   * 
   */
  SoSFBool            normalPerVertex;

 SoEXTENDER public:

  // Subclasses may define this method to generate normals to use
  // when the normal binding is DEFAULT and there aren't enough
  // normals in the state. This should use the given SoNormalBundle
  // to generate the normals. Returns TRUE if normals were generated.
  virtual SbBool      generateDefaultNormals(SoState *state,
                                             SoNormalBundle *nb);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        search(SoSearchAction *action);
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
#if 0
  enum Binding {
    OVERALL =               SoMaterialBindingElement::OVERALL,
    PER_PART =              SoMaterialBindingElement::PER_PART,
    PER_PART_INDEXED =      SoMaterialBindingElement::PER_PART_INDEXED,
    PER_FACE =              SoMaterialBindingElement::PER_FACE,
    PER_FACE_INDEXED =      SoMaterialBindingElement::PER_FACE_INDEXED,
    PER_VERTEX =            SoMaterialBindingElement::PER_VERTEX,
    PER_VERTEX_INDEXED =    SoMaterialBindingElement::PER_VERTEX_INDEXED
  };
#endif
  // Constructor - makes this abstract
  SoVRMLVertexShape();

  virtual ~SoVRMLVertexShape();
    
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
                                     int numNormals, const SbVec3f *normals,
                                     const SoNormalBindingElement::Binding binding
                                     );

  // Returns the current normal cache, or NULL if there is none
  SoNormalCache       *getNormalCache() const { return normalCache; }

  // Hack to make paths work for VRML nodes that contain other nodes
  // in their fields...  Nov-96
  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

 private:
  void                rebuildChildrenList();
  // This allows instances to cache normals that have been generated
  SoNormalCache *normalCache;

  SoINTERNAL public:

  SoMFUInt32  orderedrgba;
  unsigned char normalBinding;
  unsigned char materialBinding;

};

#endif /* _SO_VRMLVERTEX_SHAPE_ */

