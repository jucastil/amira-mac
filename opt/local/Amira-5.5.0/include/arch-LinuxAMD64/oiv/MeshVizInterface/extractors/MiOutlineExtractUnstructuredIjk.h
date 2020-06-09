/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiOutlineExtractUnstructuredIjk_H
#define  _MiOutlineExtractUnstructuredIjk_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterIjk;

/**
 * @DTEXT Extract the outline of an unstructured IJK mesh.
 * 
 * @ingroup MeshIViz_Extract_Outline
 * 
 * @DESCRIPTION Builds a MeXLineMeshUnstructured interfaces containing the mesh outline.
 * The outline of a mesh is made up of all the edges that belong to only one cell. 
 * Internal edges of a mesh will not be displayed except when they are only
 * adjacent to dead cells.
 * 
 */
class MESHIVIZ_API MiOutlineExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiOutlineExtractUnstructuredIjk() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiOutlineExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  
  /**
  * @copydoc MiOutlineExtractIjk::extractOutline()
  */
  virtual const MeXLineMeshUnstructured& extractOutline(const MiCellFilterIjk* cellFilter=NULL) = 0;

 /**
 * Computes a PER_NODE scalar set on the extracted outline. 
 * Note : The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting outline mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted outline. 
 * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting outline mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted outline.
 * Note : The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting outline mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted outline.
 * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting outline mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiOutlineExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif /* _MiOutlineExtractUnstructuredIjk_H */


