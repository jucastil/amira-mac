/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Dec 2003)
**=======================================================================*/

#ifndef  _SO_TRANSPARENCY_TYPE_
#define  _SO_TRANSPARENCY_TYPE_

#include <Inventor/elements/SoTransparencyTypeElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

/**
 * @VSGEXT Node that specifies the transparency type to use for shapes.
 *
 * @ingroup PropertyNodes
 *
 * @DESCRIPTION
 *
 *  The class allows you to specify the transparency type to
 *  use for all subsequent shapes.
 *
 *  You can also specify the transparency type using SoGLRenderAction.
 *  However, there are some differences in behavior depending on which
 *  class you use to set the transparency type.
 *  - Setting transparency type SORTED_LAYERS_BLEND in an
 *      SoTransparencyType node is equivalent to setting transparency
 *      type SCREEN_DOOR. This transparency type is only effective
 *      when set in the SoGLRenderAction or viewer.
 *  - When transparency type SORTED_LAYERS_BLEND or DELAYED_SORTED_LAYERS_BLEND is set
 *      in the SoGLRenderAction or viewer, you must be careful using
 *      SoTransparencyType nodes in the scene graph. Objects that
 *      are assigned to a DELAYED_ or SORTED_ transparency
 *      type by an SoTransparencyType node will not be taken into
 *      account in the SORTED_LAYERS_BLEND or DELAYED_SORTED_LAYERS_BLEND processing (they
 *      will be rendered after this processing).
 *
 * See SoGLRenderAction for a detailed description of when
 * different shapes, including transparent shapes, are rendered
 * during scene graph traversal.
 *
 * @B NOTE: @b When using a delayed transparency mode, paths to transparent objects are saved in a list.
 * After all opaque objects have been rendered, this list is rendered. In order to avoid
 * unnecessary rendering, the common part of each path is rendered only once. This can increase performance on
 * very complex scene graphs. However, in some cases, it
 * can lead to incorrect rendering. In the figure below, node A has a side effect on node B (clipping, shader...).
 * When this optimization is on (the default), node A will not be traversed during the transparency pass,
 * which will lead
 * to incorrect rendering. When a case like this occurs in your scene graph, set OIV_USE_COMPACT_PATHS to false
 * to disable this optimization.
 * @BR
 * @IMAGE CompactPathList.png
 * @BR

 * @FILE_FORMAT_DEFAULT
 *    TransparencyType {
 *    @TABLE_FILE_FORMAT
 *       @TR type   @TD SCREEN_DOOR
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    Sets: SoTransparencyTypeElement
 *
 * @SEE_ALSO
 *    SoGLRenderAction.
 *
 */

class INVENTOR_API SoTransparencyType : public SoNode {

  SO_NODE_HEADER(SoTransparencyType);

public:

  /**
   * Various levels of transparency rendering quality.
   */
  enum TransparencyType {
    /**
     * Uses stipple patterns for screen-door transparency.
     * Note that SCREEN_DOOR transparency does not work when
     * transparency values are specified for each vertex of a shape nor when
     * transparent textures are used. In these cases, use one of the other
     * transparency types. @BR
     */
    SCREEN_DOOR = SoTransparencyTypeElement::SCREEN_DOOR,

    /**
     * Uses additive alpha blending. @BR
     */
    ADD = SoTransparencyTypeElement::ADD,

    /**
     *  Uses multiplicative alpha blending. @BR
     */
    BLEND = SoTransparencyTypeElement::BLEND,

    /**
     * Uses additive blending, rendering all transparent objects after opaque ones. @BR
     */
    DELAYED_ADD = SoTransparencyTypeElement::DELAYED_ADD,

    /**
     *  Uses multiplicative alpha blending, rendering all transparent objects after
     * opaque ones. @BR
     */
    DELAYED_BLEND = SoTransparencyTypeElement::DELAYED_BLEND,

    /**
     * Same as DELAYED_ADD, but sorts transparent objects by distances of bounding
     * boxes from camera. @BR
     */
    SORTED_OBJECT_ADD = SoTransparencyTypeElement::SORTED_OBJECT_ADD,

    /**
     * Same as DELAYED_BLEND, but sorts transparent objects by distances of bounding
     * boxes from camera. @BR
     */
    SORTED_OBJECT_BLEND = SoTransparencyTypeElement::SORTED_OBJECT_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the transparent triangles of all objects of the scene are collected,
     * and then sorted by triangle position.
     * - We recommend this transparency type when transparent objects may
     * intersect other transparent objects.
     * - Performance for this type of transparency depends on the current
     * axis sorting and on the number of triangles that intersect the
     * triangles of other objects.
     * - Best performance is comparable to other delayed transparency types and
     * occurs when the objects are sorted in the same way as they are in the scene graph,
     * and when there is no intersection between objects.
     * - In the worst case, this kind of transparency is very time consuming. Unfavorable
     * cases occur when the projection of objects on the current sorting axis
     * lets appear a lot of mixed triangles between each objects.
     * In this case
     * the object rendering is fragmented and the number of traversals to render
     * transparent objects scene is the number of fragments. In the worst case, the number of
     * fragments is equal to the number of transparent triangles in these objects.
     * - See SoGLRenderAction methods setSortedTrianglesSortFrequency() and
     * setSortedTrianglesNumCaches()
     * for information on managing the triangle sorting caches and the sorting frequency.
     *
     * @BR
     */
    SORTED_TRIANGLES_ADD = SoTransparencyTypeElement::SORTED_TRIANGLES_ADD,

    /**
     * Same as SORTED_TRIANGLES_ADD, but uses multiplicative alpha blending.
     *
     * NOTE: Triangles are sorted according to their barycenter; in some cases
     * this sort can fail.
     *
     * @BR
     */
    SORTED_TRIANGLES_BLEND = SoTransparencyTypeElement::SORTED_TRIANGLES_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the triangles of all transparent objects of the scene are
     * collected and then sorted by object.
     * - We recommend this transparency type when the different transparent objects
     * are not intersecting.
     * - In the best case, performance for this type of transparency is comparable to
     * the other delayed transparency types. This case happens when the sorted objects
     * are found in the same order as the scene graph order. In this best case, the rendering
     * is made by only one traversal.
     * - In the worst case (object sorting is reverse of scene graph traversal), performance
     * depends on the number of independent transparent objects to render. In this worst case,
     * the number of traversal to render the scene is equal to the number of transparent objects.
     * - See SoGLRenderAction methods setSortedTrianglesSortFrequency() and setSortedTrianglesNumCaches()
     * for information on managing the triangle sorting caches and the sorting frequency.
     *
     * @BR
     */
    SORTED_OBJECT_TRIANGLES_ADD = SoTransparencyTypeElement::SORTED_OBJECT_TRIANGLES_ADD,

    /**
     * Same as SORTED_OBJECT_TRIANGLES_ADD, but uses multiplicative alpha blending.
     *
     * NOTE: Triangles are sorted according to their barycenter; in some cases
     * this sort can fail.
     *
     * @BR
     */
    SORTED_OBJECT_TRIANGLES_BLEND = SoTransparencyTypeElement::SORTED_OBJECT_TRIANGLES_BLEND,

    /**
     * Uses a fragment-level depth sorting technique.
     *
     * NOTE: Setting transparency type SORTED_LAYERS_BLEND in an
     *  SoTransparencyType node is equivalent to setting transparency
     *  type SCREEN_DOOR. This transparency type is only effective
     *  when set in the SoGLRenderAction or viewer.
     *
     * If OIV_SORTED_LAYERS_TEXTURE_UNIT is not set, this transparency type reserves
     * the texture unit SoFragmentShader::getMaxTextureImageUnit()-1.
     *
     * @B Limitations: @b
     *  - This transparency type does not work with VolumeViz nodes. @BR
     *    Use DELAYED_SORTED_LAYERS_BLEND instead.
     *  - This transparency type is not compatible with interlaced stereo.
     *  - Texturing on transparent objects is limited to one texture and to MODULATE mode.
     *
     * @BR
     */
    SORTED_LAYERS_BLEND = SoTransparencyTypeElement::SORTED_LAYERS_BLEND,

    /**
     * Same as SORTED_LAYERS_BLEND, but renders opaque objects in a separate pass.
     *
     * If OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT is not set, this transparency type reserves
     * the texture unit SoFragmentShader::getMaxTextureImageUnit()-2 and OIV_SORTED_LAYERS_TEXTURE_UNIT.
     */
    DELAYED_SORTED_LAYERS_BLEND = SoTransparencyTypeElement::DELAYED_SORTED_LAYERS_BLEND

  };

  /**
   * Transparency type.
   * Use enum #TransparencyType. Default is SCREEN_DOOR.
   */
  SoSFEnum type;

  /**
   * Constructor.
   */
  SoTransparencyType();

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

//-------------------------------------------------------------------------
 SoEXTENDER public:
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual int32_t getRenderUnitID() const;

//-------------------------------------------------------------------------
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

protected:
  virtual ~SoTransparencyType();

private:
  SoTransparencyTypeElement::TransparencyType m_type;

//------------------------------------------------------------------------
};

#endif  // _SO_TRANSPARENCY_TYPE_

/**/
