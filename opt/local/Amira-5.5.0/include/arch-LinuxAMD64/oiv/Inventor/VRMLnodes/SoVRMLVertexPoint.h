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


#ifndef  _SO_VRMLVERTEX_POINT_
#define  _SO_VRMLVERTEX_POINT_

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoTextureCoordinateBinding.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
class SoVRMLVertexPoint;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLVertexPoint
//
//  Abstract vertex-based shape node class. All nodes derived from
//  this class are shapes that are constructed from vertices at some
//  or all of the current coordinates.  They all have vertexProperty nodes,
//  and vpCaches.
//
//////////////////////////////////////////////////////////////////////////////

class SoState;

/**
 * @VSGEXT Abstract base class for the SoVRMLPointSet node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for the SoVRMLPointSet node.
 *
 * @FILE_FORMAT_DEFAULT
 *   This is an abstract class. See the reference page for SoVRMLPointSet for
 *   format and default values.
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoPickAction  @BR
 *
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord
 *       @TR   SoSFNode   @TD   set_metadata      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed 
 *       @TR   SoSFNode   @TD   metadata_changed     
 *    @TABLE_END
 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLVertexPoint : public SoVRMLGeometry {

  SO_NODE_ABSTRACT_HEADER(SoVRMLVertexPoint);
    
 public:
  /**
   * An SoVRMLCoordinate node defining the IndexedPointSet.
   * 
   */
  SoSFNode            coord;
  /**
   * An SoVRMLColor node whose colors are applied to the points of the PointSet.
   * 
   */
  SoSFNode            color;

 SoEXTENDER public:

  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

 SoINTERNAL public:

  SoMFUInt32  orderedrgba;
  unsigned char materialBinding;

  static void         initClass();
  static void         exitClass();
  
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
  SoVRMLVertexPoint();

  // This is a convenience method to simplify the job of computing
  // bounding boxes for subclasses; it can be called from a
  // subclass's computeBBox() method. It sets the given bounding box
  // to contain all vertices of the shape, assuming that the shape
  // uses the numVertices coordinates beginning at the value in
  // startIndex. (If numVertices is negative, it uses all
  // coordinates from startIndex on.) It also sets the center to the
  // average of the vertices' coordinates.
  void                computeCoordBBox(SoAction *action, int numVertices,
                                       SbBox3f &box, SbVec3f &center);

  virtual ~SoVRMLVertexPoint();
    
  // Returns TRUE if the shape should be rendered. 
  // Checks for transparency in vertexProperty node before invoking
  // render action.
  virtual SbBool      shouldGLRender(SoGLRenderAction *action,
                                   SbBool isPointsOrLines = FALSE);

  // Hack to make paths work for VRML nodes that contain other nodes
  // in their fields...  Nov-96
  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

 private:
  void                rebuildChildrenList();

 
};

#endif /* _SO_VRMLVERTEX_POINT_ */

