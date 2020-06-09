/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/


#ifndef _SO_ISOSURFACE_H_
#define _SO_ISOSURFACE_H_


#include <Inventor/SbBasic.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/nodes/SoVolumeShader.h>


/*----------------------------------------------------------------------------*/

class SoMaterial;
class SoGLLazyElement;
class SoDataRange;
class SoIsosurfaceTexture;
class SoMaterial;
class SoVolumeDataDrawStyle;

/**
 *
 * @VREXT Isosurface property node
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * This property node causes subsequent SoVolumeRender nodes to draw isosurfaces instead of
 * classical volume rendering of the volume data defined by the current SoVolumeData.
 *
 * The isosurfaces are only rendered, not geometrically computed.  So it is not possible to
 * directly get the geometry corresponding to the rendered isosurface. (The MeshViz
 * extension includes algorithms to extract an isosurface as geometry, see MoMeshIsosurface.)
 *
 * The isovalues to display are specified in the #isovalues field.
 *
 * You may not use both SoVolumeShader and SoVolumeIsosurface with the same
 * SoVolumeRender node. However since Open Inventor 7.1 it is possible to use
 * both SoVolumeRenderingQuality and SoVolumeIsosurface with SoVolumeRender.
 *
 * Remember this is a shader node. The effect will usually be undesirable if it is
 * applied to standard geometry (polygons, lines, etc).  Therefore applications
 * should generally keep the volume visualization nodes and standard geometry
 * nodes separate in the scene graph (i.e. under different SoSeparator nodes).
 *
 * The multiple fields SoMaterial::diffuseColor, SoMaterial::transparency, SoMaterial::specularColor, and SoMaterial::shininess of the current
 * SoMaterial specify the material of each isosurface. All isosurfaces share the first
 * SoMaterial::specularColor and SoMaterial::shininess.
 * The first material will be for the first isosurface, the second material for the second
 * isosurface, and so on.
 *
 * Surfaces are lighted with the first directional light found in the scene graph.
 * No other lights affect the isosurface.
 *
 * This node forces the use of 3D textures and view-aligned slices.
 * It doesn't, however, actually modify the SoVolumeData::storageHint or
 * SoVolumeRender::viewAlignedSlices fields. Rather the values of these fields are
 * ignored during traversal.
 *
 * This technique requires a minimum tile overlap of 3 to avoid holes in the surface.
 * With overlap of 3 or less, this technique needs more slices than are typically
 * required for normal volume rendering.  See the numSlices field in SoVolumeRender.
 * With tile overlap of 5, a smaller number of slices can be used, allowing higher
 * performance.  For LDM format files the tile overlap was specified when the file
 * was created, e.g. by the LDM converter, and can be queried from the @I overlapping @i
 * field of the SoLDMResourceParameters associated with the volume.
 * See the @I ldmResourceParameters @i field of SoDataSet.
 * For non-LDM volumes, e.g. DICOM, the tile overlap can be specified using the
 * overlapping field.
 *
 * Like SoVolumeShader, this node searches for its predefined shaders in the
 * following directories in this order: current directory, $OIV_FILE_SEARCH_PATHS, 
 * SoInput directory list, $IVVR_SHADERS_PATH, and $OIVHOME/data/volumeviz/shaders. 
 * On Windows, the directory containing the VolumeViz DLL is searched last.
 *
 * Because this node is derived from SoVolumeShader, IVVR_FIRST_RESERVED_TEXTURE_UNIT applies
 * to it. See SoVolumeShader for more information.
 *
 *     Note: The volume size and orientation (like geometry) can be modified by
 *     transformation nodes in the scene graph and this in turn modifies the
 *     appearance of volume rendering nodes like SoVolumeIsosurface.
 *     However the same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeIsosurface {
 *    @TABLE_FILE_FORMAT
 *       @TR isovalues          @TD []
 *    @TABLE_END
 *    }
 * @ACTION_BEHAVIOR
 * SoGLRenderAction @BR
 * Sets volume isosurface parameters in the traversal state.
 *
 * @SEE_ALSO
 *  SoVolumeRender,
 *  SoVolumeShader,
 *  SoVolumeRenderingQuality,
 *  SoPreferences
 *
 *
 */
class VOLUMEVIZ_API SoVolumeIsosurface : public SoVolumeShader {

  SO_NODE_HEADER(SoVolumeIsosurface);

public:
  /**
   * Constructor
   */
  SoVolumeIsosurface();

  /**
   * Specifies the list of isovalues to display
   */
  SoMFFloat isovalues;

#ifndef HIDDEN_FROM_DOC
SoINTERNAL public:
  void GLRender(SoGLRenderAction *action);
  // Initializes the classes.
  static void initClass() ;
  static void exitClass() ;

  //Install special textures needed for isosurface rendering
  void installTextures(SoState *state);
  //Generate textures if needed according to current state
  void generateTextures(SoState *state);

  /** Helper for multivolume mode */
  void installTextures(SoState *state, SoVolumeData* vd, SoMaterial* mat);

  /** Return true if the fake isosurface drawstyle is on state */
  bool isFakeDrawStyleOnState(SoState* state) const;

SoEXTENDER public:
  virtual void rayPick(SoRayPickAction *action);

protected:
  virtual ~SoVolumeIsosurface();

  /**
   * Handle field change
   */
  virtual void handleFieldChange(SoField* f);

  /** Create a shader suitable for shadowmap generation pass */
  virtual SoShaderProgram* generateShadowShader() const;

  /** Return main fragment filename according to state */
  SbString getNeededFragmentMainFilename(SoState* state);

#endif // HIDDEN_FROM_DOC

private:
  /**
   * Set needed rendering modes
   */
  void handleVolumeRenderingQuality(SoState* state);

  /** Update isovalues of the shader used for shadowmap pass */
  void updateShadowShaderIsoValue();

  //Used to switch the vertex program when the camera projection type
  //changes
  SoVertexShader *m_vpCameraPersp;

  SoGLLazyElement *m_lazyInCache;
  SoCache *m_cache; //Dependency on SoDataRangeElement
  void addCacheDependencies(SoCache *cache, SoState *state);

  /** Proxy draw style used to assign a iso style during ray pick action*/
  SoVolumeDataDrawStyle* m_volumeDataDrawStyle;

  bool m_needUpdate;
};
/*----------------------------------------------------------------------------*/

#endif /*_SO_ISOSURFACE_H_*/
