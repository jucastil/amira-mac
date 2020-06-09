/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOVOLUMEMASK_H
#define SOVOLUMEMASK_H

#include <VolumeViz/nodes/SoVolumeData.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoMFVec4f.h>


class SoVolumeMaskReader;
class SoCpuBufferUniform;
class SoCpuBufferBasicProperty;

/**
* @VREXT Volume mask.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*   This node specifies an arbitrary voxel-based region of a volume data set
*   (SoVolumeData). A volume mask is itself a data volume consisting of binary 
*   values. Zero values are "false" and non-zero values are "true".
*   A large number of masks may be defined simultaneously, using an
*   SoVolumeMask node for each one, and mask regions may overlap if desired.
*
*   SoVolumeMask is derived from SoVolumeData.  Like SoVolumeData it accesses
*   its data through an SoVolumeReader class.  I.e. the data may be in a file
*   or in memory (or any data source using a custom volume reader). The mask 
*   volume can be any data type, but unsigned byte is currently the most 
*   memory efficient representation.
*
*   SoVolumeMask nodes must follow these rules:
*   - Each mask volume must have exactly the same voxel dimensions, tile
*     size and overlap value as the data volume it is applied to.
*   - All SoVolumeMask nodes must be children of an SoVolumeMaskGroup node.
*   - The SoVolumeData node and the SoVolumeMaskGroup nodes must be children
*     of an SoMultiDataSeparator node.
*   - The SoVolumeData and associated SoVolumeMask nodes must each have a
*     different value assigned to their dataSetId field (see SoDataSet).
*     Note that SoVolumeData and SoVolumeMask both have a default value of
*     1 for the dataSetId field, so some ids must be explicitly set.
*   - Currently SoVolumeMask nodes only affect volume rendering (SoVolumeRender).
*     They do not affect slice rendering or other VolumeViz primitives.
*
*   SoVolumeMask can be used to clip the data volume on a per-voxel basis.  
*   But the mask mechanism is much more powerful than that.  Each region can 
*   have its own transfer function (color map) using SoTransferFunction nodes.
*   Each region can also have its own draw style (volume rendering, isosurface
*   or boundary) using SoVolumeDataDrawStyle nodes.  Each region, including the
*   original unmasked volume, is only visible if there exists a transfer 
*   function (SoTransferFunction) with the same id value.
*
*   Mask regions:
*
*   A single SoVolumeMask node effectively defines two regions:
*   - False voxels (where the mask voxel = 0), and
*   - True voxels (where is mask voxel != 0).
*
*   Because intersecting regions are allowed, two SoVolumeMask nodes define 
*   (up to) four regions:
*   - False (where all masks are 0),
*   - True only in mask 1,
*   - True only in mask 2, and
*   - True in more than one mask (intersection region).
*
*   Each additional mask defines one additional region (voxels that are true
*   only in that mask).
*
*   In addition, if there exists a transfer function with the same id as the
*   original volume (SoVolumeData node), the color value from that transfer
*   function is combined with the color value from the mask region's transfer
*   function.
*
*   Transfer functions:
*
*   A separate transfer function can be specified for each of these regions 
*   using SoTransferFunction nodes. The transfer function nodes may be placed
*   under the SoVolumeMaskGroup node, but this is not required.
*
*   - A transfer function is associated with a specific mask (i.e. with the voxels
*     that are true only in that mask), by setting the SoTransferFunction
*     node's @I transferFunctionId @i equal to the mask's @I dataSetId @i.
*     If there is no transfer function with the same id as the mask, then
*     that mask is ignored.
*
*   - A transfer function is associated with all "false" voxels (voxels that
*     do not belong to any mask) by setting its @I transferFunctionId @i equal to zero.
*     If there is no transfer function with id = 0, then "false" voxels are
*     not rendered.
*
*   - A transfer function is associated with all "intersection" voxels
*     (voxels that belong to more than one mask) by setting its @I transferFunctionId @i
*     equal to SoVolumeMaskGroup::TRANSFERFUNCTION_INTERSECTION_ID.
*     If there is no transfer function with this id value, then intersection
*     voxels (if any) are rendered using the default GRAY color map.
*
*   Draw Styles:
*
*   A separate draw style can be specified for each mask region and for the
*   intersection voxels (but not for false voxels) using SoVolumeDataDrawStyle
*   nodes:
*
*   - Unlike transfer functions, a draw style is associated with a mask (voxels
*     that are true only in that mask) by traversal order.  In other words, each
*     mask uses the draw style that is current when the mask is traversed.  So 
*     you need to put SoVolumeDataDrawStyle nodes under the VolumeMaskGroup, 
*     alternating draw style, mask, draw style, mask.
*
*   - A draw style is associated with all "intersection" voxels (voxels that
*     belong to more than one mask) by placing it before the SoVolumeMaskGroup
*     node in the scene graph.
*
* @FILE_FORMAT_DEFAULT
*    VolumeMask {
*    }
*
* @SEE_ALSO
*    SoVolumeDataDrawStyle,
*    SoVolumeRender,
*    SoOrthoSlice,
*    SoObliqueSlice,
*    SoVolumeReader,
*    SoVolumeSkin,
*    SoVolumeMask,
*    SoVolumeMaskGroup,
*    SoMultiDataSeparator
*
*
*/
class VOLUMEVIZ_API SoVolumeMask : public SoVolumeData
{
  SO_NODE_HEADER(SoVolumeMask);
public:
  /**
   * Constructor.
   */
  SoVolumeMask();

  /**
  * Save editing done on the volume mask data. @BR
  * Returns true if save was successful.
  */
  bool saveEditing(SbString filename, bool recomputeLowerResolution = TRUE, const std::vector<char*> = std::vector<char*>());

  /**
  * Set default value of the volume mask.  Default is 0.
  */
  void setDefaultValue( const bool defValue );

  /**
  * Returns default value of the volume mask.
  */
  bool getDefaultValue() const;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  SoLDMReader* getAppropriateLDMReader(const SbString& pathname);
  /** Generate the final texture mask */
  virtual SoBufferObject* getTransformedTile(const SoLDMTileID& tile, const SoLDM::DataSetIdPair& pair,
                                             SoState * state = NULL, const bool useExtendedData=false);

SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction* action);

  inline virtual void setIsReadChar(bool flag);

  // Returns SoVolumeData node that this mask applies to
  virtual SoVolumeData* getVolumeData();

  virtual void setProperties( SbVec3i32 dimension, SbVec3i32 tileSize, int border );

protected:
 ~SoVolumeMask();
 void readerChanged();

private:
  struct MTStruct
  {
    SoCpuBufferBasicProperty* m_tileBufferObjFinal;
    SoCpuBufferUniform* m_tileBufferUniformObjFinal;
  };
};

void
SoVolumeMask::setIsReadChar(bool flag)
{
  m_dataCharRead = flag;
}

#endif
