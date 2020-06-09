/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOVOLUMEMASKGROUP_H
#define SOVOLUMEMASKGROUP_H

#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <Inventor/nodes/SoGroup.h>

class SoGLTexture;
class SbVec4ub;
class SoVolumeDataDrawStyle;
class SoTransferFunction;

/**
* @VREXT Volume mask group.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*   This node is used to define a collection of one or more volume masks.
*   See SoVolumeMask for details about using volume masks.  Every volume
*   mask node in the scene graph must have an SoVolumeMaskGroup as its
*   parent node.  The SoVolumeMaskGroup node, as well as the SoVolumeData
*   node, must be the child of an SoMultiDataSeparator node because the
*   masks are effectively multiple data volumes.
*
*   This class also defines the constant TRANSFERFUNCTION_INTERSECTION_ID.
*   If a transfer function (SoTransferFunction) with this id exists in the
*   traversal state, that transfer function will be used to color voxels
*   which belong to more than one mask.  See SoVolumeMask for details about
*   the regions defined by volume masks.
*
*   Note that when not using volume masks, the traversal order of
*   transfer functions is important, because each VolumeViz rendering
*   node uses the current (last traversed) transfer function independent
*   of the transfer function ids.  However if an SoVolumeMaskGroup node
*   is traversed before the rendering node (regardless of whether there
*   are any SoVolumeMask nodes in the group), the volume will only be
*   rendered using the transfer function (if any) with the same id value
*   as the volume data node.
*
* @FILE_FORMAT_DEFAULT
*    VolumeMaskGroup {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoVolumeDataDrawStyle,
*    SoVolumeRender,
*    SoVolumeMask,
*    SoMultiDataSeparator,
*    SoTransferFunction
*/
class VOLUMEVIZ_API SoVolumeMaskGroup : public SoGroup
{
  SO_NODE_HEADER(SoVolumeMaskGroup);
public:
  /**
   * Constructor.
   */
  SoVolumeMaskGroup();

  /**
   * Intersections between masks will be rendered with the transfer function
   * with id = TRANSFERFUNCTION_INTERSECTION_ID.
   */
  static short TRANSFERFUNCTION_INTERSECTION_ID;

SoINTERNAL public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void doAction(SoAction *action);
  virtual void pick(SoPickAction *action);

  static void initClass();
  static void exitClass();

  static int getInfoTextureUnit();

protected:
  /** Check if texture must be recreated */
  void updateCache(SoState *state);

  ~SoVolumeMaskGroup();

private:
  struct BoundaryPalette
  {
    /**Init everything to 0*/
    BoundaryPalette();
    unsigned char renderStyle;
    unsigned char padRenderStyle[3];
    unsigned char diffuse[4];
    unsigned char specular[3];
    unsigned char shininess;
  };

  /** Put default intersection DrawStyle on state if needed */
  void setupIntersectionDrawStyle(SoAction* state);

  /**
   * Return the draw style of the masked volume data
   * This drawstyle will be applied on the whole volume
   */
  SoVolumeDataDrawStyle* getVolumeDataDrawStyle(SoState* state);

  /** Allocate and set gl parameter for info texture */
  void initVmTexture(SoState* state);

  /** Fill m_renderStyleTex with drawing style value for each mask */
  void generateMaterialTexture(SoState* state, const SoLDM::DataSetIdPairList& dsList);

  /** Create test texture needed for boundary rendering */
  void generateBoundaryTexture(SoState* state, const SoLDM::DataSetIdPairList& dsList);

  /** Activate the boundary texture */
  void bindVmTexture(SoState* state, const SoLDM::DataSetIdPairList& dsList);

  /** Return true if this node can be used */
  static bool isSupported(SoState* state);

  /** Invalidate all mask textures */
  void invalidateVolumeMaskTextures(SoState* state);

  /** Texture used to render boundary */
  SoGLTexture* m_vmTex;

  /** Check if texture MaskGroup Data invalidation is needed */
  SoCache* m_cacheData;

  /** Check if texture MaskGroup Style invalidation is needed */
  SoCache* m_cacheStyle;

  /** Default drawstyle for intersections */
  SoVolumeDataDrawStyle* m_defaultIntersectionDrawStyle;

  /** Default tf for intersections */
  SoTransferFunction* m_defaultIntersectionTf;

  friend struct SetBoundsColorsAndStyles;
};

#endif
