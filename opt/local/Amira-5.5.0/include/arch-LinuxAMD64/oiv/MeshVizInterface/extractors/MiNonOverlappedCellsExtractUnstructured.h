/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (September 2010)
**=======================================================================*/
#ifndef  _MiNonOverlappedCellsExtractUnstructured_h
#define  _MiNonOverlappedCellsExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/STL/vector>

class MiCellFilterI;
class MiSurfaceMeshUnstructured;
class MeXSurfaceMeshUnstructured;

/**
 * @DTEXT Remove overlapped cells from a given unstructured surface mesh or a list of meshes.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This tool is another type of extractor which takes an unstructured surface mesh as input and 
 * produces a new surface mesh where overlapped cells are discarded. 
 * We define an overlapped cell as a cell lying on the same plane as a set of cells which 
 * are entirely hiding this cell.
 * In the output mesh, the geometry refers to the input geometry and the topology refers
 * to the input topology, except that the overlapped cells are set as "dead cells".
 * 
 * This tool can also work on a list of unstructured surface meshes. In that case, it merges 
 * all of them into an output mesh, using the original geometries and topologies where overlapped
 * cells from all input meshes are set as dead. To work on a list of surface meshes, call 
 * getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool).
 *
 * To detach the resulting mesh from the input meshes, it must be cloned 
 * (see MeXSurfaceMeshUnstructured::getNewClone()).
 * 
 * The following example shows how to remove overlapped cells in a list of meshes:
 * <PRE>
 *   MiNonOverlappedCellsExtractUnstructured* extract =
 *     MiNonOverlappedCellsExtractUnstructured::getNewInstance(meshList);
 *   const MeXScalardSetI& scalarSet = extract->extractScalarSet(scalarSets);
 *   const MeXVec3dSetI& vectorSet = extract->extractVec3Set(vectorSets);
 * </PRE>
 *
 */
class MESHIVIZ_API MiNonOverlappedCellsExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiNonOverlappedCellsExtractUnstructured() {}

  /**
  * Factory method returning a new instance that works on a single input surface mesh. 
  * @param mesh the input surface mesh.
  * @param parallel dummy argument not yet used.  
  */ 
  static MiNonOverlappedCellsExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true); 

  /**
  * Factory method returning a new instance that works on a list of surface meshes. 
  * @param meshList the input meshes.
  * @param parallel dummy argument not yet used.  
  */ 
  static MiNonOverlappedCellsExtractUnstructured* getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>& meshList, bool parallel = true); 


  /**
  * Builds the topology and geometry of the surface mesh after removing all overlapped cells.
  * This method must not be called when the extractor is working on a list of meshes. (.ie. the 
  * extractor has been built by getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool))
  */  
  virtual const MeXSurfaceMeshUnstructured& extractSurface(const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * Builds the topology and geometry of the surface mesh after removing all overlapped cells.
  * The resulting mesh is made of all cells of the input meshes but those overlapped.
  * @param cellFilters list that must contain same number of cell filters as the number of input meshes
  *                    in getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool)
  */  
  virtual const MeXSurfaceMeshUnstructured& extractSurface(const std::vector<const MiCellFilterI*>* cellFilters) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractScalarSet()
  * This method must not be called when the extractor is working on a list of meshes. (.ie. the 
  * extractor has been built by getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool))
  */  
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& scalarSet) =0;

  /*
  * @copydoc MiCellExtractIjk::extractScalarSet()
  * @param scalarSets list that must contain same number of scalar sets as the number of input meshes
  *                    in getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool)
  */  
  virtual const MeXScalardSetI& extractScalarSet(const std::vector<const MiScalardSetI*>& scalarSets) =0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  * This method must not be called when the extractor is working on a list of meshes. (.ie. the 
  * extractor has been built by getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool))
  */  
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& vec3Set) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  * @param vec3Sets list that must contain same number of vector sets as the number of input meshes
  *                    in getNewInstance(const std::vector<const MiSurfaceMeshUnstructured*>&, bool)
  */
  virtual const MeXVec3dSetI& extractVec3Set(const std::vector<const MiVec3dSetI*>& vec3Sets) = 0;


  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
 virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif

