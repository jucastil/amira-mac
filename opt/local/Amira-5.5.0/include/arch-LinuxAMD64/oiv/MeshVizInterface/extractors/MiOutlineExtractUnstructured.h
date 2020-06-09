/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiOutlineExtractUnstructured_H
#define  _MiOutlineExtractUnstructured_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterI;

/**
 * @DTEXT Outline extractor for an unstructured mesh.
 * 
 * @ingroup MeshIViz_Extract_Outline
 * 
 * @DESCRIPTION Builds a MiLineMeshUnstructured interfaces containing the outline of the given mesh.
 * The outline of a mesh is made up of all the edges that belong to a single cell. 
 * Internal edges of a mesh will not be displayed except when they are
 * adjacent to dead cells.
 * 
 */
class MESHIVIZ_API MiOutlineExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiOutlineExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiOutlineExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiOutlineExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiOutlineExtractIjk::extractOutline()
  */
  virtual const MeXLineMeshUnstructured& extractOutline(const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiOutlineExtractIjk::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiOutlineExtractIjk::extractVec3Set()
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;
 
  /**
  * @copydoc MiOutlineExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif /* _MiOutlineExtractUnstructured_H */


