/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JM Godinaud (May 2006)
**=======================================================================*/

#ifndef _SOMESHSKIN_H
#define _SOMESHSKIN_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/STL/vector>
#include <LDM/SoLDMTileID.h>

#include <ReservoirViz/nodes/SoMeshShape.h>

class SoGLRenderAction;
class SoAction;
class SoDataSet;
class SoPrimitiveVertex;
class SoSubSectionId;
class SoLDMTextureManager;
class SoLDMMeshTile;
class SoTileSkinCache;
class SoLDMNodeFrontMgrOctree;

#define NUN_DATA_PER_CELL 24 // size of the cell geometry (24 float)

/**
* @RVEXT Representation of the skin of a mesh.
* 
* @ingroup ReservoirVizNodes
* 
* @DESCRIPTION
*    This node draws the skin of the current mesh. The exterior 
*    boundaries of the mesh are displayed. However if a region of interest is 
*    inserted in the scene graph and is inherited during traversal 
*    (see SoROI), only the intersection of the mesh with the ROI will be
*    rendered.
*
*    Cells marked as "dead cells" in the LDM file are not displayed at the highest resolution.
*    Cells for which the cell filter functor returns false are not displayed at the highest resolution.
*    While high resolution tiles are being loaded, dead cells, cell filters and faults will not appear.
*
*    The skin is colored by using the current property data set(s), the  
*    current color map(s), the current data range, and the current shader 
*    program. Several data sets can be used, for instance, to apply a color by 
*    mixing the data. In that case, the number of color maps and data ranges  
*    provided should equal the number of data sets, and an appropriate shader  
*    program must be provided. Furthermore, the way each cell is colored depends 
*    also on the value of the inherited field SoMeshShape#interpolation.
*
*    Each cell drawn may also be outlined by changing the value of the 
*    inherited field SoMeshShape#outline.
*    
*    The current geometry of the mesh is defined by the SoMeshGeometry node 
*    inserted before this node, and inherited during traversal.
*
*    The current property data sets are defined by one or several SoMeshProperty nodes 
*    inserted before this SoMeshSkin node, and inherited 
*    during traversal.
*
*    The current color map(s) are defined by the SoTransferFunction node(s) 
*    inserted before this SoMeshSkin node, and inherited during traversal.
*
*    The current data range is defined by the SoDataRange node inserted before 
*    this SoMeshSkin node, and inherited during traversal.
*
*    The current shader program is defined by the SoShaderProgram node inserted before 
*    this SoMeshSkin node, and inherited during traversal.
*
* @FILE_FORMAT_DEFAULT
*    MeshSkin {
*    @TABLE_FILE_FORMAT
*       @TR interpolation      @TD NEAREST
*       @TR outline            @TD FALSE
*       @TR outlineColor       @TD 0,0,0
*       @TR maxResolution      @TD 0
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*    @B SoGLRenderAction @b @BR
*       Draws an image of the mesh based on current SoMeshGeometry.
*
*    @B SoGetBoundingBoxAction @b @BR
*       Computes the bounding box that encloses the mesh.
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
class RESERVOIRVIZ_API SoMeshSkin : public SoMeshShape 
{
  SO_NODE_HEADER( SoMeshSkin );

public:

  /** Default constructor */
  SoMeshSkin();

SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual float getRelativeDistanceToTile(SbBox3i32& tileBox, 
                                          SbBox3f &tileGeomPos);

protected:    
  virtual ~SoMeshSkin();
  virtual void clearTileSkinList();

  virtual int getNextLoadedStepLevel();
  virtual SbString getDefaultShaderName() 
  {
    return "resviz_prop_frag_2D.glsl";
  }

  //Do GL or primitive rendering
  virtual void doRendering(SoAction *action, SbBool genPrimitive = FALSE);
  virtual void doRenderingWithSlices(SoAction *action, SbBool genPrimitive = FALSE);
  virtual void doRenderingFullSkin(SoAction *action, SbBool genPrimitive = FALSE);
  void updateListOfTileToLoad(SoState *state, SoLDMTextureManager* tm);

  bool isTileHidden(SoLDMNodeFrontMgrOctree* nfmoctree, SbBox3i32& roiBoxTile, SbVec3i32& cellPos,SoLDMTileID& tileID,SbVec3i32& meshDim);
  SbVec3i32 getTileIJK(SbVec3i32& cellpos);

  // List of caches of tiles to draw
  std::map<SoLDMTileID,SoTileSkinCache*,compLDMTileID> m_tilesSkin;

  SoCache* m_cache;

private:
  std::vector<SoSubSectionId*> sectionIdImin;
  std::vector<SoSubSectionId*> sectionIdJmin;
  std::vector<SoSubSectionId*> sectionIdKmin;
  std::vector<SoSubSectionId*> sectionIdImax;
  std::vector<SoSubSectionId*> sectionIdJmax;
  std::vector<SoSubSectionId*> sectionIdKmax;


};

//-----------------------------------------------------------------------------
inline int 
SoMeshSkin::getNextLoadedStepLevel() 
{ 
  return 0; 
}

//-----------------------------------------------------------------------------
inline float 
SoMeshSkin::getRelativeDistanceToTile(SbBox3i32& , SbBox3f &) 
{
  return 0;
}


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SOMESHSKIN_H
