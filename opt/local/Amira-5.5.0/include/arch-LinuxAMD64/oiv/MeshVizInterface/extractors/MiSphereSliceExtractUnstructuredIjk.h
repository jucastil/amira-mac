/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiSphereSliceExtractUnstructuredIjk_h
#define  _MiSphereSliceExtractUnstructuredIjk_h

#include <MeshVizInterface/extractors/MiSphereSliceExtractIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiCellFilterIjk;
class MiVolumeMeshHexahedronIjk;
class MiTessellator;

/**
 * @DTEXT Sphere slice extractor for unstructured IJK volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION 
 * A sphere slice is the intersection of a given sphere with the mesh volume. 
 * The extracted sphere slice is an unstructured surface mesh.
 *
 * Additional data sets can be mapped onto this extracted surface by calling the 
 * extractScalarSet() or extractVec3Set() methods.
 *
 * The following sample code shows how to extract a sphere slice from a mesh: 
 * <PRE>
 *   MiSphereSliceExtractUnstructuredIjk* sphereSliceExtract =
 *     MiSphereSliceExtractUnstructuredIjk::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& sphereSlice =
 *     sphereSliceExtract->extractSlice(center,radius, NULL);
 * </PRE>
 *
 */
class MESHIVIZ_API MiSphereSliceExtractUnstructuredIjk : virtual public MiSphereSliceExtractIjk
{
public: 
  virtual ~MiSphereSliceExtractUnstructuredIjk() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiSphereSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * Computes a PER_NODE scalar set on the extracted sphere slice. 
  * Note : The argument i of the method MiScalardSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting sphere slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * Computes a PER_CELL scalar set on the extracted sphere slice. 
  * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting sphere slice mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Computes a vector set on the extracted sphere slice.
  * Note : The argument i of the method MiVec3dSetI::get(i) refers
  * to the i-th node of the mesh. Thus the binding of the inputSet
  * must be PER_NODE. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting sphere slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * Computes a vector set on the extracted sphere slice.
  * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
  * to the cell (i,j,k). Thus the binding of the inputSet
  * must be PER_CELL. An exception is thrown otherwise.
  * 
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting sphere slice mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif 


