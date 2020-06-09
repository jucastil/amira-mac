/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiCylinderSliceExtractIjk_h
#define  _MiCylinderSliceExtractIjk_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshCurvilinear;
class MiVolumeMeshRectilinear;
class MiTessellator;

/**
 * @DTEXT Cylinder slice extractor for structured volume meshes
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
 *   MiCylinderSliceExtractIjk* cylinderSliceExtract =
 *     MiCylinderSliceExtractIjk::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& cylinderSlice =
 *     cylinderSliceExtract->extractSlice(center, radius, direction, NULL);
 * </PRE>
 *
 */
class MESHIVIZ_API MiCylinderSliceExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiCylinderSliceExtractIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiCylinderSliceExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCylinderSliceExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiCylinderSliceExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the topology and geometry of a cylinder slice intersecting the volume mesh.
  * 
  * @param center A point located on the axis of the cylinder
  * @param radius The radius of the cylinder
  * @param direction A vector representing the axis of the cylinder
  * @param cellFilter The cell filter object. 
  * @return An unstructured surface mesh representing the cylinder slice
  */
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& center, double radius, const MbVec3<double>& direction, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif 


