/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (May 2006)
**=======================================================================*/

#ifndef _SOMESHLOGICALSLICE_H
#define _SOMESHLOGICALSLICE_H

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
#include <ReservoirViz/nodes/SoMeshGeometry.h>

class SoGLRenderAction;
class SoAction;
class SoDataSet;
class SoLDMMeshTile;
class SoPrimitiveVertex;
class SoSubSectionId;

/**
* @RVEXT Representation of a logical slice of a mesh.
* 
* @ingroup ReservoirVizNodes
* 
* @DESCRIPTION
*    This node draws all the cells
*    on a given layer of the mesh. The number of the layer is specified
*    by the #sliceNumber field, and the axis of the layer (I, J or K)
*    is defined by the #axis field. For instance, if sliceNumber = 3
*    and axis = K, the cells(i,j,k) with k=3 are drawn.
*    
*    Only one face of the cells is drawn depending on the #axis and #side fields. 
*    For instance, if #axis = K and #side = MAX_SIDE, the 
*    upper k faces of each cells are drawn, meaning that the upper limit
*    of the layer is drawn.
*
*    Each cell drawn may also be outlined by changing the value of the 
*    inherited field SoMeshShape::#outline.
*
*    If a region of interest (see SoROI) is inserted in the scene graph  
*    and is inherited during traversal, only the intersection of the
*    slice with the ROI will be rendered. 
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
*    also on the value of the inherited field SoMeshShape::#interpolation.
*    
*    The current geometry of the mesh is defined by the SoMeshGeometry node
*    inserted before this node, and inherited during traversal.
*
*    The current property data sets are defined by one or several SoMeshProperty 
*    node(s) inserted before this node, and inherited 
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
*    MeshLogicalSlice {
*    @TABLE_FILE_FORMAT
*       @TR sliceNumber        @TD 0
*       @TR axis               @TD K
*       @TR side               @TD MIN_SIDE
*       @TR interpolation      @TD NEAREST
*       @TR outline            @TD FALSE
*       @TR outlineColor       @TD 0,0,0
*       @TR maxResolution      @TD 0
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*    @B SoGLRenderAction @b @BR
*       Draws a logical slice of the mesh based on the current SoMeshGeometry.
*
*    @B SoGetBoundingBoxAction @b @BR
*       Computes the bounding box that encloses this logical slice.
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
class RESERVOIRVIZ_API SoMeshLogicalSlice : public SoMeshShape 
{
  SO_NODE_HEADER( SoMeshLogicalSlice );

public:

  /**
   * Constructor.
   */
  SoMeshLogicalSlice();

  /**
   * Number of the slice to draw.
   */
  SoSFUInt32 sliceNumber;

  enum Axis {
    I,
    J,
    /** (Default) */
    K
  };

  /**
   * Slice axis: I, J, or K.
   */
  SoSFEnum axis;

  enum Side {
    /** (Default) */
    MIN_SIDE,
    MAX_SIDE
  };
  
  /**
  * Slice side. Specifies if the slice is drawn at the min side or the max side of
  * a layer. In other words, this field indicates the face drawn (lower or upper)
  * for each hexahedron cell on the slice.
  */
  SoSFEnum side;

SoEXTENDER public:
  virtual void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();
  virtual float getRelativeDistanceToTile(SbBox3i32& tileBox, SbBox3f &tileGeomPos);

protected:
  virtual ~SoMeshLogicalSlice();
  virtual SbString getDefaultShaderName() 
  {
    return "resviz_prop_frag_2D.glsl";
  }

  //Do GL or primitive rendering
  virtual void  doRendering(SoAction *action, SbBool genPrimitive = FALSE);

  int  getSliceNumber(SoDataSet *);

  virtual int getNextLoadedStepLevel();

  std::vector<SoSubSectionId*> m_sectionIds;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SOMESHLOGICALSLICE_H
