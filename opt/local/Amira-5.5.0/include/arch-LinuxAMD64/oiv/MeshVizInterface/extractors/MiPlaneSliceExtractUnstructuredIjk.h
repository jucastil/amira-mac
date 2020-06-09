/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPlaneSliceExtractUnstructuredIjk_h
#define  _MiPlaneSliceExtractUnstructuredIjk_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterIjk;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiTessellator;

/**
 * @DTEXT Plane slice extractor for unstructured IJK volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION A plane slice is the intersection of a given plane with the mesh volume. The extracted plane slice
 * is an unstructured surface.
 * 
 */
class MESHIVIZ_API MiPlaneSliceExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public: 
  virtual ~MiPlaneSliceExtractUnstructuredIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiPlaneSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiPlaneSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * @copydoc MiPlaneSliceExtractIjk::extractSlice()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& normal, double distance, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Computes a PER_NODE scalar set on the extracted plane slice. 
  * Note : The argument i of the method MiScalardSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting plane slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * Computes a PER_CELL scalar set on the extracted plane slice. 
  * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting plane slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Computes a vector set on the extracted plane slice.
  * Note : The argument i of the method MiVec3dSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting plane slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * Computes a vector set on the extracted plane slice.
  * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting plane slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif 


