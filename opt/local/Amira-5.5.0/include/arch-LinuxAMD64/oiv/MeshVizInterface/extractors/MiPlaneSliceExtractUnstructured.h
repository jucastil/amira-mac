/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPlaneSliceExtractUnstructured_h
#define  _MiPlaneSliceExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterI;
class MiTessellator;

/**
 * @DTEXT Plane slice extractor for unstructured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION A plane slice is the intersection of a given plane with the mesh volume. The extracted plane slice
 * is an unstructured surface.
 * 
 */
class MESHIVIZ_API MiPlaneSliceExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiPlaneSliceExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiPlaneSliceExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiPlaneSliceExtractIjk::extractSlice()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& normal, double distance, const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiPlaneSliceExtractIjk::extractScalarSet()
  */ 
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiPlaneSliceExtractIjk::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif 


