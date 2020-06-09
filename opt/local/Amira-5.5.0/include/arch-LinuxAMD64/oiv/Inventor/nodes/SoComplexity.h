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


#ifndef  _SO_COMPLEXITY_
#define  _SO_COMPLEXITY_

#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoBBoxTypeElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoComplexity
//
//  Shape complexity node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Shape complexity node.
 *
 * @ingroup PropertyNodes
 *
 * @DESCRIPTION
 *   This node sets the current shape complexity value. This is a heuristic value
 *   which provides a hint at what geometric complexity to render shape nodes. Values
 *   range from 0 to 1, where 0 means minimum complexity and 1 means maximum
 *   complexity. Each shape node interprets complexity in its own way.
 *
 *   Shape complexity always affects rendering and primitive generation for the
 *   SoCallbackAction. For some shapes, it also affects picking.
 *
 *   There are three ways to interpret shape complexity, depending on the #type
 *   field. BOUNDING_BOX complexity
 *   ignores the #value field and renders all shapes as
 *   bounding boxes. Each bounding box shape is drawn as if
 *   it were an SoCube and is subject to all of the drawing
 *   attributes of an SoCube (current material, drawing
 *   style, etc.) except that texturing is not applied. The
 *   other two types use the #value field to determine the tessellation of
 *   shapes into polygons. OBJECT_SPACE complexity uses #value directly to
 *   determine the tessellation. SCREEN_SPACE complexity depends on #value and
 *   the projected size of the shape on the screen; a #value of 0 produces the
 *   minimum tessellation for a shape, and a #value of 1 produces a
 *   tessellation that is fine enough that each edge of a polygon is about 1 or two
 *   pixels in length. Since the projected size depends on the camera position,
 *   objects may be tessellated differently every frame if the camera is moving; note
 *   that this may have adverse effects on render caching in SoSeparator nodes.
 *
 *   The SoComplexity node also sets a hint for the quality of textures applied to
 *   shapes, based on the value of the #textureQuality field.
 *
 * @FILE_FORMAT_DEFAULT
 *    Complexity {
 *    @TABLE_FILE_FORMAT
 *       @TR type             @TD OBJECT_SPACE
 *       @TR value            @TD 0.5
 *       @TR textureQuality   @TD 0.5
 *       @TR bboxType         @TD BBOX_AABB
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Sets the current complexity in the state.
 *        Sets: SoComplexityElement, SoComplexityTypeElement, SoTextureQualityElement
 *
 *
 * @SEE_ALSO
 *    SoShape,
 *    SoShapeHints,
 *    SoTexture2,
 *    SoInteractiveComplexity
 *
 *
 */

class INVENTOR_API SoComplexity : public SoNode {

  SO_NODE_HEADER(SoComplexity);

 public:
   /** Type */
  enum Type {
    /**
     *  Set complexity independent of screen size (default)
     */
    OBJECT_SPACE = SoComplexityTypeElement::OBJECT_SPACE,
    /**
     *  Set complexity based on screen size
     */
    SCREEN_SPACE = SoComplexityTypeElement::SCREEN_SPACE,
    /**
     *  Draw all shapes as bounding boxes
     */
    BOUNDING_BOX = SoComplexityTypeElement::BOUNDING_BOX
  };

   /** Bounding box type. */
  enum BboxType {
    /**
     *  Axis Aligned Bounding Box (default).
     */
    BBOX_AABB = SoBBoxTypeElement::BBOX_AABB,
    /**
     *  Object Oriented Bounding box.
     */
    BBOX_OOB = SoBBoxTypeElement::BBOX_OOB
  };

  /**
   * How shape complexity is interpreted.
   * Use enum #Type. Default is OBJECT_SPACE.
   * The default value can also be set using the environment variable
   * OIV_COMPLEXITY_TYPE.
   */
  SoSFEnum            type;

  /**
   * Complexity value.
   * The default value can also be set using the environment variable
   * OIV_COMPLEXITY (0.0 to 1.0).
   */
  SoSFFloat           value;

  /**
   * Hint about texture quality. A value of 0 indicates that the fastest texturing
   * should be used, while a value of 1 indicates that the best quality texturing
   * should be used.
   * The default value can be set using the environment variable
   * OIV_TEXTURE_QUALITY (0.0 to 1.0).
   *
   * The table below shows the correspondence between Open Inventor texture quality and
   * OpenGL texture mapping options.
  *
  * @TABLE_1B
  * @TR
  * @B textureQuality @b @BR
  * @TD
  * @B * minFilter value @b @BR
  * @TD
  * @B ** magFilter value @b @BR
  * @TD
  * @B *** Need Mipmaps @b @BR
  * @TD
  * @B Format @b @BR
  * @TR <= 0.5 @TD GL_NEAREST @TD GL_NEAREST @TD FALSE @TD ExtendedFormats or CompressedFormats
  * @TR <= 0.6 @TD GL_LINEAR  @TD GL_NEAREST @TD FALSE @TD ExtendedFormats or CompressedFormats
  * @TR <= 0.7 @TD GL_NEAREST_MIPMAP_NEAREST  @TD GL_NEAREST @TD TRUE @TD ExtendedFormats or CompressedFormats
  * @TR <= 0.8 @TD GL_NEAREST_MIPMAP_LINEAR  @TD GL_LINEAR @TD TRUE @TD InternalFormats or CompressedFormats
  * @TR <= 0.9 @TD GL_LINEAR_MIPMAP_NEAREST  @TD GL_LINEAR @TD TRUE @TD InternalFormats or CompressedFormats
  * @TR <= 1.0 @TD GL_LINEAR_MIPMAP_LINEAR  @TD GL_LINEAR @TD TRUE @TD InternalFormats or CompressedFormats
  * @TABLE_END
  *
  * * The minFilter value can be set explicitly using the #SoTexture::minFilter field of classes derived
  * from #SoTexture.
  *
  * ** If quality < 0.75, magFilter = GL_NEAREST, otherwise magFilter = GL_LINEAR.@BR
  * The magFilter value can be set explicitly using the #SoTexture::magFilter field of classes derived
  * from #SoTexture.
  *
  * *** Means that Open Inventor automatically generates mipmap textures. See the OpenGL
  * Programming Guide for information on mipmap textures.
   *
   */
  SoSFFloat           textureQuality;

  /**
   * Bounding box type to use.
   * Use enum #BboxType.  Default is BBOX_AABB.
   * By default an Axis Aligned Bounding Box (AABB) is used. It is simpler and faster
   * to compute but may not be a good approximation of the shape's actual volume.
   * Using an Object Oriented Bounding box is more compute intensive, but can provide
   * a tighter volume box allowing better performance for actions such as
   * culling, picking and selection.
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFEnum           bboxType;

  /**
   * Creates a complexity node with default settings.
   */
  SoComplexity();

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoComplexity();
};

#endif /* _SO_COMPLEXITY_ */

