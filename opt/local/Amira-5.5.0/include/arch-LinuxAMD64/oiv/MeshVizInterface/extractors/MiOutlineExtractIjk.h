/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiOutlineExtractIjk_H
#define  _MiOutlineExtractIjk_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRegular.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiVolumeMeshCurvilinear.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterIjk;

/**
 * @DTEXT Outline extractor for a structured volume mesh.
 * 
 * @ingroup MeshIViz_Extract_Outline
 * 
 * @DESCRIPTION 
 * Builds an unstructured line mesh containing the outline of the given volume mesh.
 * The outline of a mesh is made up of all the edges that belong to a single cell. 
 * Internal edges of a mesh will not be displayed except when they are
 * adjacent to dead cells.
 *
 */
class MESHIVIZ_API MiOutlineExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiOutlineExtractIjk() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiOutlineExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiOutlineExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiOutlineExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * Builds the topology and geometry of a mesh outline.
  * @param cellFilter The cell filter.
  * @return The outline extracted as an unstructured line mesh.
  * @return An unstructured line mesh representing the outline.
  */
  virtual const MeXLineMeshUnstructured& extractOutline(const MiCellFilterIjk* cellFilter=NULL) = 0;
  
  /**
  * Extracts a scalar set from the volume mesh. The scalars are mapped onto the 
  * current extracted outline. 
  *
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting line mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts a vector set from the volume mesh. The vectors are mapped onto the 
  * current extracted outline.
  *
  * @param inputSet the input vec3 set defined on the volume mesh
  * @return the output scalar set defined on the resulting line mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;
 
  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif /* _MiOutlineExtractIjk_H */


