/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiLogicalSliceExtractUnstructuredIjk_H
#define  _MiLogicalSliceExtractUnstructuredIjk_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extractors/MiBaseLogicalSliceExtract.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiCellFilterIjk;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;

/**
* @DTEXT Logical slice extractor for an unstructured IJK volume mesh.
* 
* @ingroup MeshIViz_Extract_Logicalslice
* 
* See MiLogicalSliceExtractRegular
*
*/
class MESHIVIZ_API MiLogicalSliceExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiLogicalSliceExtractUnstructuredIjk() {} 

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiLogicalSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true);
  static MiLogicalSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  //@}

  /**
  * @copydoc MiLogicalSliceExtractRegular::extractLogicalSlice()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractLogicalSlice(SliceAxis axis, size_t sliceIndex, bool upperVertex, const MiCellFilterIjk* cellFilter=NULL) = 0;


  /**
  * Computes a PER_NODE scalar set on the extracted logical slice. 
  * Note : The argument i of the method MiScalardSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * Computes a PER_CELL scalar set on the extracted logical slice. 
  * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Computes a vector set on the extracted logical slice.
  * Note : The argument i of the method MiVec3dSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input vec3 set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * Computes a vector set on the extracted logical slice.
  * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input vec3 set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;


};

#endif /* _MiLogicalSliceExtractUnstructuredIjk_H */


