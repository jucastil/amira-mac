/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIISOSURFEXTRACTUNSTRUCTUREDIJK_H
#define  _MIISOSURFEXTRACTUNSTRUCTUREDIJK_H

#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>

class MiCellFilterIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshUnstructuredIjk;
class MiTessellator;

/**
 * @DTEXT Isosurface extractor for unstructured IJK meshes
 * 
 * @ingroup MeshIViz_Extract_Isosurf
 * 
 * @DESCRIPTION Builds the isosurface of the given isovalue in the given dataset.
 * 
 * 
 */
class MESHIVIZ_API MiIsosurfExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiIsosurfExtractUnstructuredIjk() {}
  
  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiIsosurfExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiIsosurfExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * @copydoc MiIsosurfExtractIjk::extractIsovalue()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractIsovalue(double isovalue, const MiScalardSetI& dataSet, const MiCellFilterIjk* cellFilter=NULL) = 0;

 /**
 * Computes a PER_NODE scalar set on the extracted isosurface. 
 * Note : The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting isosurface mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted isosurface. 
 * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting isosurface mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted isosurface.
 * Note : The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vector set defined on the volume mesh
 * @return the output scalar set defined on the resulting isosurface mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted isosurface.
 * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vector set defined on the volume mesh
 * @return the output scalar set defined on the resulting isosurface mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

 /**
 * @copydoc MiCellExtractIjk::getExtract()
 */
 virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;
};


#endif 


