/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MICELLEXTRACTUNSTRUCTURED_H
#define  _MICELLEXTRACTUNSTRUCTURED_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

#include <Inventor/STL/vector>

class MiCellFilterI;

/**
 * @DTEXT Cell extractor for unstructured meshes
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION Extracts a list of cells from the input unstructured mesh and builds a surface mesh representing the extracted cells.
 * 
 * 
 * 
 */

class MESHIVIZ_API MiCellExtractUnstructured : virtual public MiBaseExtractor
{
public:
    
  virtual ~MiCellExtractUnstructured() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCellExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCellExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Creates an unstructured surface mesh from the faces of the cells corresponding to the
  * given indices in the original volume mesh. Cells are scaled according to the given
  * factor. @n
  * Shrinking: factor < 1 @n
  * Expanding: factor > 1
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(const std::vector<size_t>& cellIndex, double factor, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractCell(double factor, const MiCellFilterIjk* cellFilter)
  */
  virtual const MeXSurfaceMeshUnstructured&
  extractCell(double factor, const MiCellFilterI* cellFilter=NULL) = 0;
 
  /**
  * @copydoc MiCellExtractIjk::extractScalarSet(const MiScalardSetIjk& inputSet)
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set(const MiVec3dSetIjk& inputSet)
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MICELLEXTRACT_H */


