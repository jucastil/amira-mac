/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MISKINEXTRACTUNSTRUCURED_H
#define  _MISKINEXTRACTUNSTRUCURED_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/tessellator/MiTessellator.h>

class MiCellFilterI;

/**
 * @DTEXT Skin extractor for an unstructured volume mesh.
 * 
 * @ingroup MeshIViz_Extract_Skin
 * 
 * @DESCRIPTION Performs 2 types of extraction:
 *
 * extractSkin() builds a MeXSurfaceMeshUnstructured interfaces containing the skin of the given mesh.
 * The skin of a mesh is made up of all the faces that belong to only one cell. Scalar and vector sets can
 * be mapped onto this surface by calling extractScalarSet() and extractVec3Set().
 *
 * extractLineSkin() builds a MeXLineMeshUnstructured interface containing the line skin of the given mesh, which is 
 * made up of the edges from the faces that belong to the skin. When working with quadratic meshes, only outer edges
 * of non-linear cells are extracted. 
 *
 * Internal faces and edges of a mesh will not be displayed except if they are adjacent to dead cells.
 *
 * @note No dataset mapping is available on the line skin.
 */
class MESHIVIZ_API MiSkinExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiSkinExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */
  static MiSkinExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiSkinExtractIjk::extractSkin()
  */
  virtual const MeXSurfaceMeshUnstructured& extractSkin(const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * Builds the topology and geometry of the line skin.
  * @param cellFilter The cell filter.
  * @return The line skin extracted as an unstructured line mesh.
  */
  virtual const MeXLineMeshUnstructured& extractLineSkin(const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiSkinExtractIjk::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiSkinExtractIjk::extractVec3Set()
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;
 
  /**
  * @copydoc MiSkinExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MISKINEXTRACTUNSTRUCURED_H */


