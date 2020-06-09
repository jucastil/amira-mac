/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T. DUFOUR (Nov 2002)
**=======================================================================*/
#ifndef  _SO_VOLUME_GROUP_
#define  _SO_VOLUME_GROUP_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbColor.h>
#include <LDM/nodes/SoTransferFunction.h>
#include <Inventor/sys/SoGLType.h>


class SoClipPlaneElement;
class SoVolumeShader;
class SoVolumeData;
class SoVolumeDataDrawStyle;

/**
 * @VREXT Groups multiple volumes to be rendered in the same scene.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *
 *   The SoVolumeGroup node allows multiple volumes to be rendered correctly
 *   in the same scene.  All SoVolumeRender nodes that are under the same
 *   SoVolumeGroup node are rendered together with correct blending,
 *   subject to some limitations.  Other types of geometry, for example
 *   SoOrthoSlice, are not affected by SoVolumeGroup.
 *
 *   The SoVolumeRender nodes can represent different volume data sets
 *   (see SoVolumeData) or different subvolumes (see SoROI) of the same volume
 *   data set.
 *
 *   For best results, use 3D texture rendering (SoVolumeData::TEX3D) and
 *   the viewAlignedSlices option.  With these settings even volumes that
 *   are rotated with respect to each other are correctly rendered. Using
 *   2D texture rendering (TEX2D), all the volumes must be aligned (i.e.,
 *   their XYZ axes must be parallel) to get the correct image.  There is
 *   a small performance decrease when multi-volume support is enabled.
 *
 *   The #multiVolumes field (TRUE by default) controls whether the
 *   SoVolumeGroup's special handling of SoVolumeRender nodes is applied.
 *   If the (sub)volumes being rendered do not overlap in 3D space or only
 *   one of the volumes is transparent, then SoVolumeGroup special handling
 *   is probably not necessary to get the correct image.
 *
 *   SoVolumeGroup is primarily intended for cases where the volumes are
 *   sampled on different grids.  For example if the volume dimension,
 *   size (3D extent) or orientation are different.  For volumes that are
 *   actually multiple data sets sampled on the same grid, for example
 *   seismic attribute volumes, it may be more appropriate to blend the
 *   volumes using an SoDataCompositor or SoVolumeShader node.
 *
 *   Note: Under the SoVolumeGroup node, the SoTransferFunction node has to be inserted
 *   after the SoVolumeData.
 *
 * @B Limitations: @b
 * @UL
 *  @LI Using shaders (i.e. SoVolumeShader) with  multiple volumes gives incorrect lighting results.
 * @ul
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeRender {
 *    @TABLE_FILE_FORMAT
 *       @TR multiVolumes      @TD TRUE
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
 *    SoVolumeRender,
 *    SoGroup,
 *    SoDataCompositor,
 *    SoVolumeShader
 *
 *
 */

class VOLUMEVIZ_API SoVolumeGroup : public SoGroup {

  SO_NODE_HEADER( SoVolumeGroup );

 public:
  /**
   * Activates the multi-volumes feature. Default is TRUE.
   * If set to FALSE, behaves as a regular SoGroup.
   */
  SoSFBool multiVolumes;

  /**
   * Constructor.
   */
  SoVolumeGroup();

  //------------------------------------------------------------------------------

 private:

  void GLRender(SoGLRenderAction *action);

  //------------------------------------------------------------------------------

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
   * Uniform position
   */
  enum UniformPos
  {
    SLICE_SPACING = 0,
    DU,
    DV,
    DW,
    NVIDIA_WORKAROUND,
    SCALE_FACTOR,
    ONE_OVER_SLICE_DENSITY,
    ZAXIS,
    LAST_POS
  };
  typedef std::vector<GLint> UniformLocationList;

  void addColormap(SoTransferFunction*, int, unsigned int *);
  void addVolume(SoState*, SoTransferFunction::GLColorMapType, SbBool, int, int, SbVec3f&,
                 const SoClipPlaneElement*, const SbVec3f& scale, float sliceDensity, SoVolumeData* vd);
  void addBrick(const SbVec4f*, float[3]);
  void addSlice(int, int, float[][3], float, const SbVec3f& zAxis);

  //Set uniform locations of the current volume
  void setVolumeUniformLocations(const UniformLocationList& uniformLocations);

  //Set material info for the current volume
  void setVolumeMaterial(float color[4], const SbColor &ambientColor, const SbColor &specularColor,
                         const SbColor &emissiveColor, float shininess);
  //Set shader infos for the current volume
  void setVolumeShaderInfos(SbBool useExternalShader, unsigned int externalProgram,
                            SoVolumeShader *volumeShader, SoVolumeDataDrawStyle* vds);

 protected:
  // Destructor
  virtual ~SoVolumeGroup();
  void     sortSlices();
  void     renderSlices(SoState *state);

 private:
   SbPList m_colormaps;
   SbPList m_volumes;
   SbPList m_bricks;
   SbPList m_slices;

   int m_currentColormap;
   int m_currentVolume;
   int m_currentBrick;
   int m_currentSlice;
   SbMatrix m_currentMatrix, m_currentMatrixInv;
   SbVec3f  m_currentPlane;
};
#endif // _SO_VOLUME_GROUP_
