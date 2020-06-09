/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JM Godinaud (Jul 2006)
**=======================================================================*/

#ifndef _SOMESHPLANESLICE_H
#define _SOMESHPLANESLICE_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFPlane.h>

#include <Inventor/STL/vector>
#include <LDM/SoLDMTileID.h>

#include <ReservoirViz/nodes/SoMeshShape.h>

class SoGLRenderAction;
class SoAction;
class SoDataSet;
class SoLDMMeshTile;
class SoPrimitiveVertex;

class SoTileSliceGlRenderer;
class SoTileSliceOutlineRenderer;
class SoTileSlicePrimitiveRenderer;
class SoTileSliceRayPickRenderer;
class SoTileBboxRenderer;

/**
* @RVEXT Representation of a geometric slice of a mesh.
* 
* @ingroup ReservoirVizNodes
* 
* @DESCRIPTION
*    This node draws all the cells
*    that intersect the given geometric plane. The 
*    intersection plane is defined by the field #plane. Each cell 
*    that intersects the plane is displayed by drawing its intersection
*    polygon. Thus, SoMeshPlaneSlice draws a plane surface cutting the mesh.
*    
*    Each cell drawn may also be outlined by changing the value of the 
*    inherited field SoMeshShape#outline.
*
*    If a region of interest (see SoROI) is inserted in the scene graph  
*    and is inherited during traversal, only the intersection of the
*    plane with the ROI will be rendered. 
*
*    Cells marked as "dead cells" in the LDM file are not displayed at the highest resolution.
*    Cells for which the cell filter functor returns false are not displayed at the highest resolution.
*    While high resolution tiles are being loaded, dead cells, cell filters and faults will not appear.
*
*    The slice is colored using the current property data set(s), the  
*    current color map(s), the current data range, and the current shader 
*    program. Several data sets can be used, for instance, to apply a color by 
*    mixing the data. In that case, the number of color maps and data ranges  
*    provided should equal the number of data sets, and an appropriate shader  
*    program must be provided. Furthermore, the way each cell is colored depends 
*    also on the value of the inherited field SoMeshShape#interpolation.
*    
*    The current geometry of the mesh is defined by the SoMeshGeometry node 
*    inserted before this node, and inherited during traversal.
*
*    The current property data sets are defined by one or several 
*    SoMeshProperty nodes inserted before this node, and inherited 
*    during traversal.
*
*    The current color map(s) are defined by the SoTransferFunction node(s) 
*    inserted before this node, and inherited during traversal.
*
*    The current data range is defined by the SoDataRange node inserted before 
*    this node, and inherited during traversal.
*
*    The current shader program is defined by the SoShaderProgram node inserted  
*    before this node, and inherited during traversal.
*
* @FILE_FORMAT_DEFAULT
*    MeshPlaneSlice {
*    @TABLE_FILE_FORMAT
*       @TR plane              @TD 0, 0, 1
*       @TR interpolation      @TD NEAREST
*       @TR outline            @TD FALSE
*       @TR outlineColor       @TD 0,0,0
*       @TR maxResolution      @TD 0
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*    @B SoGLRenderAction @b @BR
*       Draws a geometric slice of the mesh based on current SoMeshGeometry.
*
*    @B SoGetBoundingBoxAction @b @BR
*       Computes the bounding box that encloses this geometric slice.
*
* @SEE_ALSO
*    SoMeshGeometry,
*    SoMeshProperty,
*    SoTransferFunction,
*    SoDataRange,
*    SoShaderProgram,
*    SoROI
* 
*/
class RESERVOIRVIZ_API SoMeshPlaneSlice : public SoMeshShape 
{
  SO_NODE_HEADER( SoMeshPlaneSlice );

public:

 /** 
  * Constructor.
  */
  SoMeshPlaneSlice();

  /**
  * Plane defining the slice. The default plane corresponds to the XY plane.
  */
  SoSFPlane plane;

  /**  
  * Returns the minimum LDM resolution level. 
  *
  * The slice equal resolution option is not yet available for SoMeshPlaneSlice.
  */
  virtual int getCurrentResolution();

SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual float getRelativeDistanceToTile(SbBox3i32& tileBox, SbBox3f &tileGeomPos);

protected:    
  virtual ~SoMeshPlaneSlice();
  virtual SbString getDefaultShaderName() 
  {
    return "resviz_prop_frag_3D.glsl";
  }

  virtual void  doRendering(SoAction *action, SbBool genPrimitive = FALSE);
  void getTilesNearSlice(SoState *state);

  virtual int getNextLoadedStepLevel() ;

  //to cache slice position
  SbPlane  m_slicePlane;

  SoGLVolCacheList*             m_VRTexList;

  SoTileSliceGlRenderer        *m_glRenderer;
  SoTileSliceOutlineRenderer   *m_outlineRenderer;
  SoTileSlicePrimitiveRenderer *m_primitiveRenderer;
  SoTileSliceRayPickRenderer   *m_rayPickRenderer;
  SoTileBboxRenderer           *m_bboxRenderer;

  std::vector<SoLDMTileID>      m_tilesList;
  std::vector<SoLDMTileID>      m_tilesDrawn;

  std::vector<SoLDMTileID>      m_tilesToDraw;

  size_t m_cellFilterFctorTS;

private:
  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SOMESHPLANESLICE_H
