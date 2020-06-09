/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiOutlineExtractIj_H
#define  _MiOutlineExtractIj_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshRegular.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshCurvilinear.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterIj;

/**
 * @DTEXT Outline extractor for a structured surface mesh.
 * 
 * @ingroup MeshIViz_Extract_Outline
 * 
 * @DESCRIPTION 
 * Builds an unstructured line mesh containing the outline of the given surface mesh.
 * The outline of a mesh is made up of all the edges that belong to a single cell. 
 * Internal edges of a mesh will not be displayed except when they are
 * adjacent to dead cells.
 * 
 */
class MESHIVIZ_API MiOutlineExtractIj : virtual public MiBaseExtractor
{
public:
  virtual ~MiOutlineExtractIj() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiOutlineExtractIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiOutlineExtractIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiOutlineExtractIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiOutlineExtractIjk::extractOutline()
  */
  virtual const MeXLineMeshUnstructured& extractOutline(const MiCellFilterIj* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiCellExtractIj::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIj& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIj::extractVec3Set()
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIj& inputSet) = 0;
 
  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif /* _MiOutlineExtractIj_H */


