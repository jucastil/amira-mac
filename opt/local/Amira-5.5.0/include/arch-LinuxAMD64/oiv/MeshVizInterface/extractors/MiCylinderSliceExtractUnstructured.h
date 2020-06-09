/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiCylinderSliceExtractUnstructured_h
#define  _MiCylinderSliceExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterI;
class MiTessellator;

/**
 * @DTEXT Cylinder slice extractor for unstructured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION 
 * A cylinder slice is a surface mesh defined by the intersection of a cylinder of 
 * infinite length with the input mesh. The cylinder is defined by a point on its 
 * central axis, a vector representing the central axis direction and the radius.
 *
 * Additional data sets can be mapped onto this extracted surface by calling the 
 * extractScalarSet() or extractVec3Set() methods.
 *
 * The following sample code shows how to extract a cylinder slice from a mesh: 
 * <PRE>
 *   MiCylinderSliceExtractUnstructured* cylinderSliceExtract =
 *     MiCylinderSliceExtractUnstructured::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& cylinderSlice =
 *     cylinderSliceExtract->extractSlice(center, radius, direction, NULL);
 * </PRE>
 *
 */
class MESHIVIZ_API MiCylinderSliceExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiCylinderSliceExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCylinderSliceExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiCylinderSliceExtractIjk::extractSlice()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& center, double radius, const MbVec3<double>& direction, const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiCellExtractIjk::extractScalarSet()
  */ 
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif 


