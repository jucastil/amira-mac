/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIINTERPOLATEDLOGICALSLICEEXTRACTUNSTRUCTUREDIJK_H
#define  _MIINTERPOLATEDLOGICALSLICEEXTRACTUNSTRUCTUREDIJK_H

#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extractors/MiInterpolatedLogicalSliceExtract.h>

class MiCellFilterIjk;
class MiSurfaceMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;

/**
 * @DTEXT Interpolated logical slice extractor for unstructured IJK meshes
 * 
 * @ingroup MeshIViz_Extract_Logicalslice
 * 
 * @DESCRIPTION An interpolated logical slice is similar to a logical slice except that instead of 
 * displaying the slice only on the side of the cells, it can interpolate a slice inside cells. 
 * This is done by providing a floating point value representing the offset along the cell axis.
 * 
 */
class MESHIVIZ_API MiInterpolatedLogicalSliceExtractUnstructuredIjk : virtual public MiInterpolatedLogicalSliceExtract
{
public:
  
  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiInterpolatedLogicalSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  static MiInterpolatedLogicalSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true);
  //@}


 /**
 * Computes a PER_NODE scalar set on the extracted interpolated slice. 
 * Note : The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted interpolated slice. 
 * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted interpolated slice.
 * Note : The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted interpolated slice.
 * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};


#endif 


