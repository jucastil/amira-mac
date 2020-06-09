/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTRANSFORM_
#define  _SO_VRMLTRANSFORM_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>

class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTransform
//
//  Geometric transformation node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Grouping node that defines a coordinate system for its children.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   A SoVRMLTransform is a grouping node that defines a coordinate system for its
 *   children that is relative to the coordinate systems of its parents. 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   A SoVRMLTransform is a grouping node that defines a coordinate system for its
 *   children that is relative to the coordinate systems of its parents. See also
 *   "Concepts - Coordinate Systems and Transformations." 
 *   
 *   See the "Concepts - Grouping and Children Nodes" section for a description of the
 *   @B children @b, @B addChildren @b, and @B removeChildren @b fields and
 *   eventIns.
 *   
 *   The @B bboxCenter @b and @B bboxSize @b fields specify a bounding box that
 *   encloses the SoVRMLTransform's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default @B bboxSize @b value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the @B bboxCenter @b and @B bboxSize @b
 *   fields.
 *   
 *   The #translation, #rotation, #scale, #scaleOrientation
 *   and #center fields define a geometric 3D transformation consisting of (in
 *   order) a (possibly) non-uniform scale about an arbitrary point, a rotation about
 *   an arbitrary point and axis, and a translation. The #center field
 *   specifies a translation offset from the local coordinate system's origin,
 *   (0,0,0). The #rotation field specifies a rotation of the coordinate
 *   system. The #scale field specifies a non-uniform scale of the coordinate
 *   system - #scale values must be >= 0.0. The #scaleOrientation
 *   specifies a rotation of the coordinate system before the scale (to specify
 *   scales in arbitrary orientations). The #scaleOrientation applies only to
 *   the scale operation. The #translation field specifies a translation to the
 *   coordinate system.
 *   
 *   Given a 3-dimensional point @B P @b and Transform node, @B P @b is transformed
 *   into point @B P @b' in its parent's coordinate system by a series of
 *   intermediate transformations. In matrix-transformation notation, where C
 *   (center), SR (scaleOrientation), T (translation), R (rotation), and S (scale)
 *   are the equivalent transformation matrices,
 *   
 *   <PRE>
 *    P' = T x C x R x SR x S x -SR x -TC x P 
 *    (where P is a column vector)
 *    </PRE>
 *    The SoVRMLTransform node: 
 *   
 *   <PRE>
 *    Transform { 
 *    center C 
 *    rotation R 
 *    scale S 
 *    scaleOrientation SR 
 *    translation T 
 *    children [...] 
 *   } </PRE>
 *    is equivalent to the nested sequence of: 
 *   
 *   <PRE>
 *    Transform { translation T 
 *    Transform { translation C 
 *    Transform { rotation R 
 *    Transform { rotation SR 
 *    Transform { scale S 
 *    Transform { rotation -SR 
 *    Transform { translation -C 
 *    ... 
 *   }}}}}}} 
 *    </PRE>
 *    
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTransform {
 *    @TABLE_FILE_FORMAT
 *       @TR center             @TD 0 0 0
 *       @TR children           @TD []
 *       @TR rotation           @TD 0 0 1 0
 *       @TR scale              @TD 1 1 1
 *       @TR scaleOrientation   @TD 0 0 1 0
 *       @TR translation        @TD 0 0 0
 *       @TR bboxCenter         @TD 0 0 0
 *       @TR bboxSize           @TD -1 -1 -1
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction,  SoGetMatrixAction,  SoSearchAction,  SoWriteAction  @BR
 *      Sets: SoModelMatrixElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   addChildren      
 *       @TR   SoMFNode   @TD   removeChildren      
 *       @TR   SoSFVec3f   @TD   set_center      
 *       @TR   SoMFNode   @TD   set_children      
 *       @TR   SoSFRotation   @TD   set_rotation      
 *       @TR   SoSFVec3f   @TD   set_scale      
 *       @TR   SoSFRotation   @TD   set_scaleOrientation      
 *       @TR   SoSFVec3f   @TD   set_translation
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFVec3f   @TD   center_changed      
 *       @TR   SoMFNode   @TD   children_changed      
 *       @TR   SoSFRotation   @TD   rotation_changed      
 *       @TR   SoSFVec3f   @TD   scale_changed      
 *       @TR   SoSFRotation   @TD   scaleOrientation_changed      
 *       @TR   SoSFVec3f   @TD   translation_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTransform : public SoVRMLGroup {

  SO_NODE_HEADER(SoVRMLTransform);

 public:
  // Fields
  /**
   * Translation vector.
   */
  SoSFVec3f           translation;

  /**
   * Rotation.
   */
  SoSFRotation        rotation;

  /**
   * Scale factor.
   */
  SoSFVec3f           scale;

  /**
   * Rotational orientation for scale.
   */
  SoSFRotation        scaleOrientation;

  /**
   * Origin of scale and rotation.
   */
  SoSFVec3f           center;

  /**
   * Constructor.
   */
  SoVRMLTransform();

  /**
   * Constructor that takes approximate number of children
   */
  SoVRMLTransform(int nChildren);

  /**
   * Sets the transform to translate the origin to the fromPoint and rotate the
   * negative z-axis (0,0,-1) to lie on the vector from fromPoint to toPoint. This
   * always tries to keep the "up" direction the positive y-axis, unless that is
   * impossible. All current info in the node is wiped out.
   */
  void                pointAt(const SbVec3f &fromPoint,
                              const SbVec3f &toPoint);

  /**
   * Returns composite matrix that transforms from object space to
   * scale space (the space after the scale).
   */
  void                getScaleSpaceMatrix(SbMatrix &mat, SbMatrix &inv) const;

  /**
   * Returns composite matrix that transforms from object space to
   * rotation space (the space after the scale and rotation).
   */
  void                getRotationSpaceMatrix(SbMatrix &mat,
                                             SbMatrix &inv) const;
  /**
   * Returns composite matrix that transforms from object space to
   * translation space (the space after scale, rotation, and translation).
   */
  void                getTranslationSpaceMatrix(SbMatrix &mat,
                                                SbMatrix &inv) const;

  /**
   * Convenience function that combines the effects of a matrix transformation into
   * the transformation stored in this node. This method premultiplies the
   * transformation.
   */
  void                multLeft(const SbMatrix &mat);

  /**
   * Convenience function that combines the effects of a matrix transformation into
   * the transformation stored in this node. This method postmultiplies the
   * transformation.
   */
  void                multRight(const SbMatrix &mat);

  /**
   * Same as multLeft() except that the transformation
   * to multiply into this node comes from another transformation node.
   */
  void                combineLeft(SoVRMLTransform *nodeOnLeft);

  /**
   * Same as multRight() except that the transformation
   * to multiply into this node comes from another transformation node.
   */
  void                combineRight(SoVRMLTransform *nodeOnRight);

  /**
   * Sets the fields in the node to implement the transformation represented by the
   * given matrix
   */
  void                setMatrix(const SbMatrix &mat);

  /**
   * Changes the center of the transformation to the given point without affecting
   * the overall effect of the transformation
   */
  void                recenter(const SbVec3f &newCenter);

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        search(SoSearchAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  virtual void        notify(SoNotList *list);

 protected:

  virtual ~SoVRMLTransform();

 private:
  void                 setupModelMatrixElement(SoState *state);

};

#endif /* _SO_VRMLTRANSFORM_ */

