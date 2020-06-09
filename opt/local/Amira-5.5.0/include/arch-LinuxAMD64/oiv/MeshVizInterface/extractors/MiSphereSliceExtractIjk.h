/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiSphereSliceExtractIjk_h
#define  _MiSphereSliceExtractIjk_h

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
 * @DTEXT Sphere slice extractor for structured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION 
 * A sphere slice is the intersection of a given sphere with the mesh volume. 
 * The extracted sphere slice is an unstructured surface mesh.
 *
 * Additional data sets can be mapped onto this extracted surface by calling the 
 * extractScalarSet() or extractVec3Set() methods.
 *
 * The following sample code shows how to extract a sphere slice from a mesh: 
 * <PRE>
 *   MiSphereSliceExtractIjk* sphereSliceExtract =
 *     MiSphereSliceExtractIjk::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& sphereSlice =
 *     sphereSliceExtract->extractSlice(center,radius, NULL);
 * </PRE>
 *
 */
class MESHIVIZ_API MiSphereSliceExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiSphereSliceExtractIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiSphereSliceExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSphereSliceExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiSphereSliceExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the topology and geometry of a sphere slice intersecting the volume mesh.
  * 
  * @param center The position of the center of the sphere
  * @param radius The radius of the sphere
  * @param cellFilter The cell filter object. 
  * @return An unstructured surface mesh representing the sphere slice
  */
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& center, double radius, const MiCellFilterIjk* cellFilter=NULL) = 0;

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


