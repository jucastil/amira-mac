/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_VOLUME_SKIN_
#define  _SO_VOLUME_SKIN_

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbBox.h>

#include <VolumeViz/nodes/SoSlice.h>

class SoVertexShader;
class SoVolumeSkinLdm;
class SoVolumeSkinPaging;
class SoVolumeSkinInterface;
class SoVolumeStateSkin;

/**
 * @VREXT Draws a data volume skin.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *   This node draws the "skin" (outer faces) of the data volume defined by
 *   the current SoVolumeData node.  This skin is a set of textured polygons
 *   similar to ortho slices.
 *
 *   For a non-RGBA (scalar valued) volume,
 *   each voxel's RGBA value is determined by the current SoDataRange and SoTransferFunction.
 *   The current @B diffuse color @b and @B transparency @b (set, for example, with
 *   an SoMaterial node) modify the appearance of the voxels.  This means that, for
 *   example, the current transparency can be used as a @I global alpha @i value
 *   to modulate the overall opacity.
 *   For an RGBA volume each voxel's RGBA value comes directly from the volume data.
 *
 *   When using an opaque transfer function (no alpha values < 1), this node
 *   generates the same image as SoVolumeRender, but with much higher
 *   performance, because only slices are rendered.
 *   A common pattern is to put an SoVolumeRender node and an SoVolumeSkin node
 *   under an SoSwitch node.  This makes it easy to switch between skin rendering
 *   and volume rendering.
 *
 *   The #interpolation field controls how the texture is interpolated.
 *
 *   Optionally a bump mapping effect may be applied. Normal vectors are automatically
 *   computed from the data value gradient.  The #enableBumpMapping and #bumpScale
 *   fields control whether bump mapping is active and the intensity of the effect.
 *
 *   The current SoROI (Region of Interest) node, if any, limits rendering to a
 *   subvolume.  The SoROI node's EXCLUSION_BOX mode can also be used to exclude
 *   a sub-region from the skin, forming what is sometimes called a "chair cut".
 *   Volume clipping nodes (SoVolumeClippingGroup, SoUniformGridClipping)
 *   may also be used to limit the extent of the skin.
 *
 *   The current SoVolumeShader node, if any, allows custom shaders to be defined for
 *   special computation or rendering effects, including blending multiple volumes.
 *
 *   The entire skin is pickable, even where it is transparent as a result of the
 *   current transfer function.  The SoVolumeSkinDetail class allows you to get the
 *   voxel position and value after picking.
 *
 *   When the "large slice" feature is enabled (see SoSlice::largeSliceSupport), if all the
 *   required full resolution tiles have already been loaded, then
 *   the slice data is taken from LDM system memory cache as usual. But if some required
 *   tiles are not currently in memory, the required slice data will be loaded directly
 *   from the volume reader @I without @i loading the complete tiles. This reduces disk I/O
 *   and reduces the amount of system memory required to display the slice at full resolution,
 *   so larger (or more) slices can be displayed. The required tiles are then scheduled to be
 *   loaded asynchronously in case adjacent slices are displayed later.
 *   For example, loading a 1024x1024 SoOrthoSlice from an 8-bit dataset with 128x128x128
 *   tiles would normally require loading 1024x1024x128 bytes of data (as complete tiles).
 *   With largeSliceSupport enabled, only 1024x1024 bytes (maximum) of data need to
 *   be loaded (in the worst case where no high resolution data is currently in memory).
 *
 *     @B Note: @b The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoVolumeSkin.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @B Note: @b
 * For performance reasons, SoVolumeSkin accumulates small textures into a bigger
 * one. When using compressed RGBA textures (via #SoDataSet's field useCompressedTexture),
 * this optimization cannot be done.
 * If you want to favor performance rather than memory usage, you should disable compression
 * (enabled by default if supported by the graphic card)
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeSkin {
 *    @TABLE_FILE_FORMAT
 *       @TR interpolation      @TD LINEAR
 *       @TR alphaUse           @TD ALPHA_AS_IS
 *       @TR composition        @TD ALPHA_BLENDING
 *       @TR useRGBA            @TD FALSE
 *       @TR enableBumpMapping  @TD FALSE
 *       @TR bumpScale          @TD 1.0
 *       @TR faceMode           @TD FRONT
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    @B SoGLRenderAction @b @BR
 *       Draws a volume-rendered image based on current SoVolumeData.
 *
 *    @B SoGetBoundingBoxAction @b @BR
 *       Computes the bounding box that encloses the volume.
 *
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoTransferFunction,
 *    SoROI,
 *    SoVolumeShader
 *
 *
 */

class VOLUMEVIZ_API SoVolumeSkin : public SoSlice
{
  SO_NODE_HEADER( SoVolumeSkin );

public:

  /**
   * Use this enum with the #faceMode field.
   */
  enum FaceMode
  {
    /** Display only front faces */
    FRONT,
    /** Display only back faces */
    BACK,
    /** Display front and back faces */
    FRONT_AND_BACK
  };

  /**
   * Constructor.
   */
  SoVolumeSkin();

  /**
   * Display front (facing the camera) faces or back faces. 
   * Use enum #FaceMode. Default is FRONT.
   * Displaying only front (or back) faces reduces the amount of data
   * that must be loaded and reduces the rendering time.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFEnum faceMode;

SoEXTENDER public:

  /**
   * Returns an alternate represention for this node. @BR
   * This is typically a scene graph that gives approximately the same
   * appearance using only core Open Inventor nodes.  For example the
   * volume skin could be represented using SoTexture2 nodes.
   * This class implements an alternate for PDF and U3D export.
   */
  virtual SoNode* getAlternateRep( SoAction* action );

  /**
   * Returns true if the shape intersects the given tile
   */
  virtual bool intersect(SoLDMNodeFrontManager* nfm, const SoLDMTileID& tileId);

  /**
   * Compute bounding box
   */
  void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

SoINTERNAL public:
  /**
   * Node init
   */
  static void initClass();
  /**
   * Node exit
   */
  static void exitClass();

  /**
   * Create a subgraph for the alternateRep field that gives approximately
   * the same appearance, but using only core Open Inventor nodes.
   * Might be useful in other cases.
   */
  virtual SoNode* createAlternateRep( SoAction *action );

  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

private:
  /**
   * Create and set the good rendering class
   */
  bool setupRenderInterface(SoAction* action);

  /**
   * Overrides standard method to create an SoVolumeSkin instance
   * representing a picked intersection with a triangle that is half
   *  of the face of a cube.
   */
  SoDetail *createTriangleDetail(SoRayPickAction *,
                                 const SoPrimitiveVertex *v1,
                                 const SoPrimitiveVertex *,
                                 const SoPrimitiveVertex *,
                                 SoPickedPoint *);

  /** Interface for LDM mode */
  SoVolumeSkinLdm* m_volSkinLdm;

  /** Interface for paging */
  SoVolumeSkinPaging* m_volSkinPaging;

  /** Current active render Interface*/
  SoVolumeSkinInterface* m_volSkinInterface;

protected:
  /**
   * Destructor
   */
  virtual ~SoVolumeSkin();

  /**
   * Performs GL rendering
   */
  virtual void doRendering(SoGLRenderAction *action);

  /**
   * Generate triangles
   */
  void generatePrimitives(SoAction *action);

  SoVolumeStateSkin* m_vs;
};
#endif // _SO_VOLUME_SKIN_
