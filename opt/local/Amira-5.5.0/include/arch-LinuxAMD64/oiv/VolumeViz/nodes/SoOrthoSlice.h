/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_ORTHO_SLICE_
#define  _SO_ORTHO_SLICE_

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/SbBox.h>
#include <Inventor/STL/vector>
#include <LDM/SoLDMTileManager.h>
#include <LDM/nodes/SoTransferFunction.h>

#include <VolumeViz/nodes/SoSlice.h>

class SoVolumeData;
class SoCache ;
class SoGLVolCacheList;
class SoLDMOrthoSliceGeom;
class SoOrthoSliceInterface;
class SoOrthoSliceLdm;
class SoOrthoSlicePaging;
class SoVolumeStateSlice;

/**
 * @VREXT Ortho slice shape node.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *   This node defines an ortho (axis aligned) slice along the X, Y, or Z axis of the volume data
 *   defined by an SoVolumeData node. The slice orientation and position are defined by the #axis
 *   and #sliceNumber fields.
 *
 *   For a non-RGBA (scalar valued) volume, 
 *   each voxel's RGBA value is determined by the current SoDataRange and SoTransferFunction.
 *   The current @B diffuse color @b and @B transparency @b (set, for example, with
 *   an SoMaterial node) modify the appearance of the slice.  This means that, for
 *   example, the current transparency can be used as a @I global alpha @i value
 *   to modulate the overall opacity of the slice.  
 *   For an RGBA volume each voxel's RGBA value comes directly from the volume data.
 *
 *   The #interpolation field controls how the texture is interpolated.
 *
 *   The #alphaUse field (SoSlice) controls how the voxel's alpha component is used when drawing the slice.
 *
 *   The #composition field controls how the slice is blended with other objects in the scene.
 *
 *   Optionally, this node also defines a clipping plane. Similar to SoClipPlane, this
 *   clipping plane affects all subsequent geometry, including SoVolumeRender.
 *   The #clipping and #clippingSide fields control whether clipping is
 *   active and which half-space is clipped.
 *
 *   Optionally a bump mapping effect may be applied. Normal vectors are automatically
 *   computed from the data value gradient.  The #enableBumpMapping and #bumpScale
 *   fields (SoSlice) control whether bump mapping is active and the intensity of the effect.
 *
 *   The current SoROI (Region of Interest) node, if any, limits the slice to a
 *   subvolume.  Volume clipping nodes (SoVolumeClippingGroup, SoUniformGridClipping)
 *   may also be used to limit the extent of the slice.
 *
 *   The current SoVolumeShader node, if any, allows custom shaders to be defined for
 *   special computation or rendering effects, including blending multiple volumes.
 *
 *   The entire slice is pickable, even where it is transparent as a result of the
 *   current transfer function.  The SoOrthoSliceDetail class allows you to get the
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
 *   @B Note: @b The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoOrthoSlice.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @B Note: @b
 * For performance reasons, #SoOrthoSlice accumulates small textures into a bigger
 * one. When using compressed RGBA textures (via #SoDataSet's field useCompressedTexture),
 * this optimization cannot be done.
 * If you want to favor performance rather than memory usage, you should disable compression
 * (enabled by default if supported by the graphic card)
 *
 * @FILE_FORMAT_DEFAULT
 *    OrthoSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR sliceNumber     @TD 0
 *       @TR axis            @TD Z
 *       @TR interpolation   @TD LINEAR
 *       @TR alphaUse        @TD ALPHA_BINARY
 *       @TR composition     @TD ALPHA_BLENDING
 *       @TR useRGBA         @TD FALSE
 *       @TR clipping        @TD FALSE
 *       @TR clippingSide    @TD BACK
 *       @TR alternateRep    @TD NULL
 *       @TR enableBumpMapping @TD FALSE
 *       @TR bumpScale       @TD 1.0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws a textured rectangle based on current SoVolumeData, SoTransferFunction,
 *        and SoROI nodes. Sets: SoClipPlaneElement
 *
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the slice.
 *
 *
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoDataRange,
 *    SoTransferFunction,
 *    SoROI,
 *    SoSlice,
 *    SoObliqueSlice
 *
 *
 */

class VOLUMEVIZ_API SoOrthoSlice : public SoSlice
{
  SO_NODE_HEADER( SoOrthoSlice );

public:

  /**
   * Slice number.
   */
  SoSFUInt32 sliceNumber;

  /** Slice Axis */
  enum Axis {
    /** X Axis */
    X,
    /** Y Axis */
    Y,
    /** Z Axis (Default) */
    Z
  };

  /**
   * Slice axis (X, Y, or Z).
   * Use enum #Axis. Default is Z.
   */
  SoSFEnum axis;

  /** Clipping Side mode */
  enum ClippingSide {
    /** Front */
    FRONT,
    /** Back (Default) */
    BACK
  };

  /**
   * Specify the clipping side.
   * Use enum #ClippingSide. Default is BACK.
   *
   *    @TABLE_0B
   *       @TR These figures show an ortho slice clipping a data volume.
   *
   *           Right:
   *             - #alphaUse = ALPHA_BINARY @BR
   *             - #interpolation = LINEAR
   *
   *           Bottom left:
   *             - #alphaUse = ALPHA_OPAQUE @BR
   *             - #interpolation = LINEAR
   *
   *           Bottom right:
   *             - #alphaUse = ALPHA_BINARY @BR
   *             - #interpolation = NEAREST
   *
   *       @TD @IMAGE binarylinear.jpg
   *       @TR @IMAGE opaquelinear.jpg
   *       @TD @IMAGE binarynearest.jpg
   *    @TABLE_END
   */
  SoSFEnum clippingSide;

  /**
   * Activate/deactivate the clipping plane on a per-slice basis.
   */
  SoSFBool clipping;

  /**
   * Constructor.
   */
  SoOrthoSlice();

  /**
   * Return true if the shape intersect given tile
   */
  virtual bool intersect(SoLDMNodeFrontManager* nfm, const SoLDMTileID& tileId);

SoEXTENDER public:
  /**
   * Compute the bounding box
   */
  void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

  /**
   * Implements SoWriteAction for this node.
   * Creates alternateRep subgraph if enabled.
   */
  virtual void write(SoWriteAction *action);

  /**
   * Returns an alternate represention for this node. @BR
   * This is typically a scene graph that gives approximately the same
   * appearance using only core Open Inventor nodes.  For example a
   * slice can be represented using a FaceSet and a Texture2 node.
   */
  virtual SoNode* getAlternateRep( SoAction* action );

SoINTERNAL public:
  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

protected:
  /**
   * Generate primitive for the raypick action
   */
  void generatePrimitives(SoAction *action);

  /**
   * Create triangle detail for the raypick action
   */
  SoDetail *createTriangleDetail( SoRayPickAction *,
                                  const SoPrimitiveVertex *v1,
                                  const SoPrimitiveVertex *,
                                  const SoPrimitiveVertex *,
                                  SoPickedPoint *);

  /**
   * Clamp slice number between dataset dimensions
   */
  int  getSliceNumber(SoVolumeData*);

  /**
   * Render the slice
   */
  virtual void doRendering(SoGLRenderAction *action);

  /**
   * Reads data into instance. Returns FALSE on error.
   * Deletes alternateRep subgraph unless requested not to.
   */
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  //------------------------------------------------------------------------------

  SoINTERNAL public:
    static void initClass();
    static void exitClass();

  /**
   * Overrides default method on SoShape. It must return TRUE if clip plane
   * is activated.  Used internally, especially for path traversal.  Probably
   * no reason for applications to ever call it.
   */
  virtual SbBool affectsState() const;

  /**
   * Create a subgraph for the alternateRep field that gives approximately
   * the same appearance, but using only core Open Inventor nodes.  Used by the
   * write() method when SoVolumeRendering::setWriteAlternateRep(TRUE) was
   * called.  Might be useful in other cases.
   */
  virtual SoNode* createAlternateRep( SoAction *action );

  /**
   * Internal method used to activate timing benchmarking
   * on LDM orthoslice
   */
  void activateLdmSliceTiming();

  SoINTERNAL public:

  /** Sets back face culling. */
  void setBackFace( const bool backFace );

#ifndef HIDDEN_FROM_DOC
protected:
  /** clamp sliceNumber field between 0 and dataDim[axis]-1*/
  void clampSliceNumber(SoVolumeData* vd);

  /**
   * Install clipping planes on the state if needed
   */
  void installClippingPlanes();

  /**
   * Send all fields to the SoOrthoSliceInterface
   * @return false if there is no volumedata on state
   */
  bool setupSliceInterface(SoAction* action);

  /**
   * Destructor
   */
  virtual ~SoOrthoSlice();

  /**
   * remember if we created the altRep
   */
  SbBool       m_altRepCreatedHere;
#endif // HIDDEN_FROM_DOC

  SoOrthoSliceInterface* m_sliceInterface;
  SoOrthoSliceLdm* m_sliceLdm;
  SoOrthoSlicePaging* m_slicePaging;

  SoVolumeStateSlice* m_vs;
};

#ifdef _WIN32
#pragma warning( pop )
#endif
#endif // _SO_ORTHO_SLICE_
