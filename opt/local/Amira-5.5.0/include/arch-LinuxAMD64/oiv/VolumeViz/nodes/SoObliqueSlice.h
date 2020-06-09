/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_OBLIQUE_SLICE_
#define  _SO_OBLIQUE_SLICE_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/STL/vector>
#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <VolumeViz/nodes/SoSlice.h>

class SoVolumeData;
class SoCache;
class SoGLVolCacheList;
class SoLDMObliqueSliceGeom;

class SoObliqueSliceLdm;
class SoObliqueSliceInterface;
class SoObliqueSlicePaging;
class SoVolumeStateSlice;

/**
 * @VREXT Oblique slice shape node.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *   This node defines an oblique (arbitrarily oriented) slice which is the intersection of the 
 *   volume data defined by an SoVolumeData node and the plane defined by the #plane field.
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
 *   current transfer function.  The SoObliqueSliceDetail class allows you to get the
 *   voxel position and value after picking.
 *
 *     @B Note: @b The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoObliqueSlice.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @FILE_FORMAT_DEFAULT
 *    ObliqueSlice {
 *    @TABLE_FILE_FORMAT
 *       @TR plane           @TD 0, 0, 1, 0
 *       @TR interpolation   @TD LINEAR
 *       @TR alphaUse        @TD ALPHA_BINARY
 *       @TR composition     @TD ALPHA_BLENDING
 *       @TR useRGBA         @TD FALSE
 *       @TR alternateRep    @TD NULL
 *       @TR enableBumpMapping @TD FALSE
 *       @TR bumpScale       @TD 1.0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws a textured polygon based on current SoVolumeData, SoTransferFunction, and
 *        SoROI nodes.
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
 *    SoOrthoSlice,
 *    SoVolumeShader
 *
 *
 */

class VOLUMEVIZ_API SoObliqueSlice : public SoSlice {
  SO_NODE_HEADER( SoObliqueSlice );

 public:

  /**
   * Plane defining the slice. The default plane corresponds to the XY plane.
   */
  SoSFPlane plane;

  /**
   * Constructor.
   */
  SoObliqueSlice();

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
  
protected:
  /**
   * Send all fields to the SoOrthoSliceInterface
   * @return false if there is no volumedata on state
   */
  bool setupSliceInterface(SoAction* action);

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
   * Render the slice
   */
  void doRendering(SoGLRenderAction *action);

  /**
   * Reads data into instance. Returns FALSE on error.
   * Deletes alternateRep subgraph unless requested not to.
   */
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

SoINTERNAL public:
  /**
   * Node init
   */
  static void initClass();
  static void exitClass();

  /**
   * Create a subgraph for the alternateRep field that gives approximately
   * the same appearance, but using only core Open Inventor nodes.  Used by the
   * write() method when SoVolumeRendering::setWriteAlternateRep(TRUE) was
   * called.  Might be useful in other cases.
   */
  virtual SoNode* createAlternateRep( SoAction *action );

protected:

  /**
   * Destructor
   */
  virtual ~SoObliqueSlice();

  /**
   * remember if we created the altRep
   */
  SbBool m_altRepCreatedHere;

  SoObliqueSliceInterface* m_sliceInterface;
  SoObliqueSliceLdm* m_sliceLdm;
  SoObliqueSlicePaging* m_slicePaging;

  SoVolumeStateSlice* m_vs;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_OBLIQUE_SLICE_

