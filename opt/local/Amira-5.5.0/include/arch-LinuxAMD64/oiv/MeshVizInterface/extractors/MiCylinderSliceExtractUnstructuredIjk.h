/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiCylinderSliceExtractUnstructuredIjk_h
#define  _MiCylinderSliceExtractUnstructuredIjk_h

#include <MeshVizInterface/extractors/MiCylinderSliceExtractIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterIjk;
class MiVolumeMeshHexahedronIjk;
class MiTessellator;

/**
 * @DTEXT Cylinder slice extractor for unstructured IJK volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION 
 * A cylinder slice is a surface mesh defined by the intersection of a cylinder of 
 * infinite length with the input mesh. The cylinder is defined by a point on its 
 * central axis, a vector representing the central axis direction and the radius.
 *
 * Additional data sets can be mapped onto this extracted surface by calling the 
 * extractScalarSet() or extractVec3Set() methods.
 *
 * The following sample code shows how to extract a cylinder slice from a mesh: 
 * <PRE>
 *   MiCylinderSliceExtractUnstructuredIjk* cylinderSliceExtract =
 *     MiCylinderSliceExtractUnstructuredIjk::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& cylinderSlice =
 *     cylinderSliceExtract->extractSlice(center, radius, direction, NULL);
 * </PRE>
 * 
 */
class MESHIVIZ_API MiCylinderSliceExtractUnstructuredIjk : virtual public MiCylinderSliceExtractIjk
{
public: 
  virtual ~MiCylinderSliceExtractUnstructuredIjk() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCylinderSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * Computes a PER_NODE scalar set on the extracted cylinder slice. 
  * Note : The argument i of the method MiScalardSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting cylinder slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * Computes a PER_CELL scalar set on the extracted cylinder slice. 
  * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting cylinder slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Computes a vector set on the extracted cylinder slice.
  * Note : The argument i of the method MiVec3dSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting cylinder slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * Computes a vector set on the extracted cylinder slice.
  * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting cylinder slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif 


