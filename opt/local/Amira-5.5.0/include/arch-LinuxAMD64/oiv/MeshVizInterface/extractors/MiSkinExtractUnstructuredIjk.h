/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MISKINEXTRACTUNSTRUCTUREDIJK_H
#define  _MISKINEXTRACTUNSTRUCTUREDIJK_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiCellFilterIjk;
class MiTessellator;

/**
 * @DTEXT Extract the skin of an unstructured IJK mesh.
 * 
 * @ingroup MeshIViz_Extract_Skin
 * 
 * @DESCRIPTION Builds a MiSurfaceMeshUnstructured interfaces containing the mesh skin for the given data set at the given value.
 * The skin of a mesh is made up of all the faces that belong to only one cell. 
 * Internal faces of a mesh will not be displayed except if they are
 * adjacent to dead cells.
 * 
 * 
 */
class MESHIVIZ_API MiSkinExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiSkinExtractUnstructuredIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiSkinExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSkinExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * @copydoc MiSkinExtractIjk::extractSkin()
  */
  virtual const MeXSurfaceMeshUnstructured& extractSkin(const MiCellFilterIjk* cellFilter=NULL) = 0;
  
 /**
 * Computes a PER_NODE scalar set on the extracted skin. 
 * Note : The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting interpolated slice mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted skin. 
 * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar set defined on the resulting skin mesh
 */
 virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted skin.
 * Note : The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting skin mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted skin.
 * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting skin mesh
 */
 virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
 virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MISKINEXTRACTCURVILINEAR_H */


