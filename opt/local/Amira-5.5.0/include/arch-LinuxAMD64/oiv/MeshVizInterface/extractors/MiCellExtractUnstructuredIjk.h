/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MICELLEXTRACTUNSTRUCTUREDIJK_H
#define  _MICELLEXTRACTUNSTRUCTUREDIJK_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <MeshVizInterface/extractors/MiCellExtractIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>


/**
 * @DTEXT Cell extractor for unstructured IJK meshes
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION Extracts a list of cells from the input unstructured IJK mesh and builds a surface mesh representing the extracted cells.
 * 
 */

class MESHIVIZ_API MiCellExtractUnstructuredIjk : virtual public MiCellExtractIjk , virtual public MiBaseExtractor
{
public:
    
  virtual ~MiCellExtractUnstructuredIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCellExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

/**
 * Computes a PER_NODE scalar set on the extracted interpolated slice. 
 * 
 * @note The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted interpolated slice. 
 * 
 * @note The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted interpolated slice.
 * 
 * @note The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vector set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted interpolated slice.
 * 
 * @note The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vector set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif /* _MICELLEXTRACTUNSTRUCTUREDIJK_H */


