/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOVOLUMEDATADRAWSTYLE_H
#define SOVOLUMEDATADRAWSTYLE_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFMaterial.h>

#include <LDM/SoLDM.h>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @VREXT Volume draw style.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*   This node specifies the volume rendering style for a volume or for
*   one of the voxel regions of a volume defined by SoVolumeMask nodes.
*   The available draw styles are hidden (not rendered), direct volume
*   rendering, a set of isosurfaces and the boundary surface according
*   to the #style field.  Volume rendering always uses the current transfer
*   function and material in the scene graph.  Isosurfaces and boundary
*   surfaces use the current material by default, but can optionally
*   be rendered using materials specified in the #isosurfacesMaterial
*   or #boundaryMaterial fields.
*
*   Notes:
*
*   - Draw style only applies to SoVolumeRender nodes.
*
*   - See SoVolumeMask for discussion of how draw styles are associated
*     with mask regions.
*
*   - When not using volume masks, the draw style node must be traversed
*     before the SoVolumeData node.
*
*   - The MASK_BOUNDARY style is ignored if not using volume masks.
*
*   - The ISOSURFACE style is functionally equivalent to using an
*     SoVolumeIsosurface node.
*
* @FILE_FORMAT_DEFAULT
*    VolumeMask {
*    @TABLE_FILE_FORMAT
*       @TR style     @TD VOLUME_RENDER
*       @TR boundaryMaterial     @TD NULL
*       @TR isosurfacesMaterial @TD NULL
*       @TR isovalues @TD []
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoVolumeData,
*    SoVolumeRender,
*    SoVolumeMask,
*    SoVolumeMaskGroup,
*    SoMultiDataSeparator,
*    SoTransferFunction
*
*/
class VOLUMEVIZ_API SoVolumeDataDrawStyle : public SoNode
{
  SO_NODE_HEADER(SoVolumeDataDrawStyle);
public:
  /**
   * Creates a volume draw style node with default settings.
   */
  SoVolumeDataDrawStyle();

#ifndef HIDDEN_FROM_DOC
  //WARNING: This enum must stay in sync with defines from shaders source
#endif
  /** Volume rendering style. @BR
   *  These values may be combined and are used in the #style field.
   */
  enum DrawStyle {
    /**
     * Display nothing
     */
    NONE = 0,
    /**
     * Display the volume mask using the associated transfer function. (Default)
     */
    VOLUME_RENDER = 1,
    /**
     * Display only the mask boundary, using #boundaryMaterial.
     */
    MASK_BOUNDARY = 1 << 1,

    /**
     * Display isosurfaces using #isovalues and #isosurfacesMaterial.
     */
    ISOSURFACE = 1 << 2
  };

  /**
   * Set the draw style used for a volume or mask:
   *
   * -NONE: Display nothing
   *
   * -VOLUME_RENDER: Display the volume using the associated transfer function. This is the default value.
   *
   * -MASK_BOUNDARY: Display only the mask boundary, don't render the masked volume.
   *
   * -ISOSURFACE: Display the set of isosurfaces defined in #isovalues field.
   *
   * Modes can be combined.
   */
  SoSFBitMask style;

  /**
   * Material used to render the mask boundary.  Default is none.
   */
  SoSFMaterial boundaryMaterial;

  /**
   * Values of isosurfaces to display. Default is none.
   */
  SoMFFloat isovalues;

  /**
   * Material used to render isosurfaces. @BR
   * If this field is empty, the current or default SoMaterial is used.
   */
  SoSFMaterial isosurfacesMaterial;

SoEXTENDER public:
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void pick(SoPickAction *action);

SoINTERNAL public:
  typedef std::map<SoLDM::DataSetIdPair, SoVolumeDataDrawStyle::DrawStyle> MaskDrawStyleValueMap;
  typedef std::vector<float> IsovalueVec;
  typedef std::map<unsigned short, IsovalueVec> IsovalueMap;

  static void initClass();
  static void exitClass();

  /** Call the ldm valuation action method */
  static void ldmAction(SoAction *action, SoNode* node);

  /** Key of the intersection style in the MaskDrawStyleValueMap */
  static const SoLDM::DataSetIdPair S_INTERSECTION_KEY;

protected:
  ~SoVolumeDataDrawStyle();
};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif
