/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiSkinExtractIjk_H
#define  _MiSkinExtractIjk_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRegular.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiVolumeMeshCurvilinear.h>
#include <MeshVizInterface/mesh/MiVolumeMeshVertexHexahedronIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterIjk;

/**
 * @DTEXT Skin extractor for a structured volume mesh.
 * 
 * @ingroup MeshIViz_Extract_Skin
 * 
 * @DESCRIPTION Builds a MiSurfaceMeshUnstructured interfaces containing the mesh skin for the given data set at the given value.
 * The skin of a mesh is made up of all the faces that belong to only one cell. 
 * Internal faces of a mesh will not be displayed unless they are
 * adjacent to dead cells.
 * 
 * 
 */
class MESHIVIZ_API MiSkinExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiSkinExtractIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiSkinExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSkinExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSkinExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSkinExtractIjk* getNewInstance(const MiVolumeMeshVertexHexahedronIjk& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the topology and geometry of a mesh skin.
  * @param cellFilter The cell filter.
  * @return The skin extracted as an unstructured surface mesh.
  */
  virtual const MeXSurfaceMeshUnstructured& extractSkin(const MiCellFilterIjk* cellFilter=NULL) = 0;
  
  /**
  * Extracts a scalar set from the volume mesh. The scalars are mapped onto the 
  * current extracted skin. 
  *
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts a vector set from the volume mesh. The vectors are mapped onto the 
  * current extracted skin.
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

#endif /* _MiSkinExtractIjk_H */


