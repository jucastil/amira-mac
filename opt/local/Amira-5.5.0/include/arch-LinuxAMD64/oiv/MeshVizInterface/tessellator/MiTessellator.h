/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiTessellator_h
#define _MiTessellator_h

class MiCell;
class MiLineCell;
class MiSurfaceCell;
class MiVolumeCell;

#include <MeshVizInterface/MxMeshIViz.h>

#include <MeshVizInterface/tessellator/MiEdgeErrorMetric.h>

#include <MeshVizInterface/extrmesh/geometry/MeWGeometryI.h>
#include <MeshVizInterface/extrmesh/topology/MeWVolumeTopologyExplicitI.h>
#include <MeshVizInterface/extrmesh/topology/MeWSurfaceTopologyExplicitI.h>
#include <MeshVizInterface/extrmesh/topology/MeWLineTopologyExplicitI.h>

/**
 * @DTEXT Abstract tessellator interface.
 * 
 * @ingroup MeshIViz_Extract_Tessellate
 * 
 * @DESCRIPTION Defines the interface used to handle the tessellation of non linear meshes.@BR
 * 
 * This class is an abstract interface and no constructor is available. A concrete instance
 * of this interface can be allocated by calling either getNewTessellatorBasic() or
 * getNewTessellatorGeometry(). The application can either use one of these instances, or
 * implement its own tessellation tool by extending this interface and implementing all the
 * abstract methods.
 *
 * MiTessellator defines the miscellaneous methods used to tessellate either line meshes, surface
 * meshes or volume meshes. The setMesh method defines the topology and geometry of the input mesh from which 
 * the lines, surfaces or volumes to be tessellated are extracted.
 * 
 * List of methods used to tessellate a line cell:
 *   - startLineTessellation()
 *   - finishLineTessellation()
 *   - tessellateLineCell()
 * 
 * The following pseudo code explains how these methods are used by a class that extracts 
 * or draws some lines from an input mesh.
 @verbatim
    aLineExtractorMethod(MiTessellator* tessellator, inputMesh, ...) 
    {
       // Extract the useful line cells.
       ...
       // now start the tessellation
       tessellator->setMesh(inputMesh.getTopology(),inputMesh.getGeometry());
       tessellator->startLineTessellation(tessellatedTopo,tessellatedGeom);
       for each line cell lC extracted from the input cell iC
       {
          tessellator->tessellateLineCell(lC,iC);
       }
       tessellator->finishLineTessellation();
       tessellator->unsetMesh();
       return tessellatedTopo and tessellatedGeom
    }
 @endverbatim
 *
 * List of methods used to tessellate a surface cell:
 *   - startSurfaceTessellation()
 *   - finishSurfaceTessellation()
 *   - tessellateSurfaceCell()
 * 
 * The following pseudo code explains how these methods are used by a class that extracts 
 * or draws some surfaces from an input mesh.
 @verbatim
    aSurfaceExtractorMethod(MiTessellator* tessellator, inputMesh, ...) 
    {
       // Extract the useful surface cells.
       ...
       // now start the tessellation
       tessellator->setMesh(inputMesh.getTopology(),inputMesh.getGeometry());
       tessellator->startSurfaceTessellation(tessellatedTopo,tessellatedGeom);
       for each surface cell sC extracted from the input cell iC
       {
          tessellator->tessellateSurfaceCell(sC,iC);
       }
       tessellator->finishSurfaceTessellation();
       tessellator->unsetMesh();
       return tessellatedTopo and tessellatedGeom
    }
 @endverbatim
 *
 * List of methods used to tessellate a volume cell:
 *   - startVolumeTessellation()
 *   - finishVolumeTessellation()
 *   - tessellateVolumeCell()
 * 
 * The following pseudo code explains how these methods are used by a class that extracts 
 * or draws some volumes from an input mesh.
 @verbatim
    aVolumeExtractorMethod(MiTessellator* tessellator, inputMesh, ...) 
    {
       // Extract the useful volume cells.
       ...
       // now start the tessellation
       tessellator->setMesh(inputMesh.getTopology(),inputMesh.getGeometry());
       tessellator->startVolumeTessellation(tessellatedTopo,tessellatedGeom);
       for each volume cell vC
       {
          tessellator->tessellateVolumeCell(vC);
       }
       tessellator->finishVolumeTessellation();
       tessellator->unsetMesh();
       return tessellatedTopo and tessellatedGeom
    }
 @endverbatim
 *
 */

class MESHIVIZ_API MiTessellator
{
public:
  virtual ~MiTessellator() {}

  /**
  * Returns a time stamp for this tessellator. @BR When the content of the tessellator 
  * changes, the time stamp must increase. The time stamp allows MeshViz 
  * to be aware of any change to this tessellator.
  */
  virtual size_t getTimeStamp() const = 0;

  /** @name Factory methods */
  // @{
  
  /**
  * Returns a new instance of a basic implementation of the interface MiTessellator. @BR
  * This basic instance does not really tessellate the given cell because it does
  * not add any points in the result. The line cells to tessellate are
  * replaced by their sub segments returned by the method MiLineCell::getSubEdgeNodesIndex().
  * The surface cells  to tessellate are
  * replaced by their sub segments returned by the method MiSurfaceCell::getSubTriangleNodesIndex().
  * For instance the following image shows the result of the basic tessellator when tessellating
  * a quadratic triangle cell.
  *  @IMAGE BasicTessellationTriangle6.png 
  */
  static MiTessellator* getNewTessellatorBasic();

  /**
  * Returns a new instance of a geometrical implementation of the interface MiTessellator. @BR
  * This geometrical tessellator splits the edges of line or surface cells in a recursive way.
  * This tessellator does not take into account any dataset attached to the cell's nodes.
  * It uses only the geometrical criterion defined by the instance of MiEdgeErrorMetric<MbVec3d>
  * given. If an edge is seen as not linear by this criterion, the tessellator splits it
  * into 2 sub edges, which are then also checked with this criterion, and so on. 
  * However, the tessellation stops when the recursive depth exceeds the environment variable 
  * MESHVIZ_TESSELLATION_MAX_DEPTH (see SoPreferences) even if the geometrical criterion is not reached.
  * In other words, the sub-edges minimum length is 1/2^MESHVIZ_TESSELLATION_MAX_DEPTH of the tessellated edge original length.
  * The default value is 10, meaning that a given edge will never be divided into more
  * than 2^10 = 1024 edges.
  *
  * @note MiEdgeErrorMetric is just an interface with no constructor available. It is up
  * to the application to decide which test should be done to check if 3 points are almost
  * aligned or not. However, the class MxEdgeErrorMetricGeometry is an implementation provided 
  * for convenience.  It implements a simple test with a tolerance factor.
  * 
  * The following image shows an example of the result of the geometrical tessellator when tessellating
  * a quadratic triangle cell.
  *  @IMAGE GeometryTessellationTriangle6.png
  * @param edgeMetric The instance of MiEdgeErrorMetric used by the geometry tessellator as 
  *                   the criteria to decide if an edge of a current level of tessellation 
  *                   should be split or not.
  */
  static MiTessellator* getNewTessellatorGeometry(const MiEdgeErrorMetric<MbVec3d>& edgeMetric);

  /**
  * Returns a new instance of a polyhedral implementation of the interface MiTessellator. @BR
  * This polyhedral tessellator splits polyhedron cells into a set of tetrahedra and pyramids.
  * This tessellator does not take into account any dataset attached to the cell's nodes.
  * The break down criterion is only based on the topological definition of each volume cell 
  * given by the MiVolumeCell interface, namely the number of nodes and the number of faces. 
  * New nodes are then added at the center of the volume cell and eventually at the center of
  * each face if having more that four nodes.
  *
  * @note Tessellating a line or a surface cell with this tessallator simply returns the cell as is.
  * 
  */
  static MiTessellator* getNewTessellatorPolyhedron();
  // @}

  /** @name Tessellation input mesh*/
  // @{

  /**
  * Defines the topology and geometry of the input mesh from which the lines, surfaces and volumes
  * are extracted before being tessellated.
  * @param [in] topology The input mesh topology.
  * @param [in] geometry The input mesh geometry.
  */
  virtual void setMesh(const MiTopologyExplicitI& topology, const MiGeometryI& geometry) = 0;

  /**
  * Removes the input mesh after tessellation.
  */
  virtual void unsetMesh() = 0;

  // @}

  /** @name Tessellation of volume cells. */
  // @{

  /**
  * Starting point of the tessellation of volumes. @BR
  * When a list of volume cells needs to be tessellated, this method is called first.
  * @see finishVolumeTessellation().
  * @param[in] tessellatedTopology The topology class in which the resulting cells of the
  *            tessellation are added. (see tessellateVollumeCell()).
  * @param[in] tessellatedGeometry The geometry class in which the resulting coordinates of
  *            the tessellation are added. (see tessellateVolumeCell()).
  */
  virtual void startVolumeTessellation(MeWVolumeTopologyExplicitI& tessellatedTopology, MeWGeometryI& tessellatedGeometry) = 0;

  /**
  * End point of the tessellation of volumes. @BR
  * This method is called after all the volume cells are tessellated.
  * @see startVolumeTessellation().
  */
  virtual void finishVolumeTessellation() = 0;

  /**
  * Tessellates a volume cell and appends the resulting indexed tessellation to the 
  * tessellatedTopology and tessellatedGeometry given to this tessellator by the previous call 
  * to startVolumeTessellation().
  * @param [in] volumeCell the volume cell to be tessellated. 
  * @return the number of cells generated by the tessellation of this cell.
  */
  virtual size_t tessellateVolumeCell(const MiVolumeCell* volumeCell) = 0;

  // @}

  /** @name Tessellation of surface cells. */
  // @{

  /**
  * Starting point of the tessellation of surfaces. @BR
  * When a list of surface cells needs to be tessellated, this method is called first.
  * @see finishSurfaceTessellation().
  * @param[in] tessellatedTopology The topology class in which the resulting triangles of the
  *            tessellation are added. (see tessellateSurfaceCell()).
  * @param[in] tessellatedGeometry The geometry class in which the resulting coordinates of
  *            the tessellation are added. (see tessellateSurfaceCell()).
  */
  virtual void startSurfaceTessellation(MeWSurfaceTopologyExplicitI& tessellatedTopology, MeWGeometryI& tessellatedGeometry) = 0;

  /**
  * End point of the tessellation of surfaces. @BR
  * This method is called after all the surface cells are tessellated.
  * @see startSurfaceTessellation().
  */
  virtual void finishSurfaceTessellation() = 0;

  /**
  * Tessellates a surface cell and appends the resulting indexed tessellation to the 
  * tessellatedTopology and tessellatedGeometry given to this tessellator by the previous call 
  * to startSurfaceTessellation().
  * @param [in] surfaceCell the surface cell to be tessellated. 
  * @param [in] inputMeshCell the cell of the input mesh from which the surfaceCell is extracted. @BR
  *        For instance, if the surface cell is a part of an isosurface extracted from a volume mesh,
  *        inputMeshCell is the volume cell from which the surfaceCell is extracted. @BR
  *        If the surfaceCell is not extracted from another cell, inputMeshCell must be equal to
  *        surfaceCell.
  * @return the number of triangles generated by the tessellation of this cell.
  */
  virtual size_t tessellateSurfaceCell(const MiSurfaceCell* surfaceCell, const MiCell* inputMeshCell) = 0;

  // @}



  /** @name Tessellation of line cells. */
  // @{

  /**
  * Starting point of the tessellation of lines. @BR
  * When a list of line cells needs to be tessellated, this method is called first.
  * @see finishLineTessellation().
  * @param[in] tessellatedTopology The topology class in which the resulting segments of the
  *            tessellation are added. (see tessellateLineCell()).
  * @param[in] tessellatedGeometry The geometry class in which the resulting coordinates of
  *            the tessellation are added. (see tessellateLineCell()).
  */
  virtual void startLineTessellation(MeWLineTopologyExplicitI& tessellatedTopology, MeWGeometryI& tessellatedGeometry) = 0;

  /**
  * End point of the tessellation of lines. @BR
  * This method is called after all the line cells are tessellated.
  * @see startLineTessellation().
  */
  virtual void finishLineTessellation() = 0;

  /**
  * Tessellates a line cell and appends the resulting indexed tessellation to the 
  * tessellatedTopology and tessellatedGeometry given to this tessellator by the previous call 
  * to startLineTessellation().
  * @param [in] lineCell The line cell to be tessellated. 
  * @param [in] inputMeshCell The cell of the input mesh from which the line cell is extracted. 
  *             For instance inputMeshCell can be a volume cell and lineCell could be one of its 
  *             edges.
  * @return the number of edges generated by the tessellation of this cell.
  */
  virtual size_t tessellateLineCell(const MiLineCell* lineCell, const MiCell* inputMeshCell) = 0;
  
  //@}

};


#endif
