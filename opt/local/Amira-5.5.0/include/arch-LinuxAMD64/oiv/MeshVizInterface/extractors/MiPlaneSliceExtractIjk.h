/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
  #ifndef  _MiPlaneSliceExtractIjk_h
#define  _MiPlaneSliceExtractIjk_h

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
 * @DTEXT Plane slice extractor for structured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION A plane slice is the intersection of a given plane with the mesh volume. The extracted plane slice
 * is an unstructured surface.
 * 
 */
class MESHIVIZ_API MiPlaneSliceExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiPlaneSliceExtractIjk() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the topology and geometry of a plane slice intersecting the volume mesh.
  * 
  * @return the plane slice extracted as an unstructured surface mesh.
  * @param normal Vector normal to the plane slice
  * @param distance Position of the plane relatively to the origin along the normal
  * @param cellFilter The cell filter object. 
  * @return An unstructured surface mesh representing the plane slice
  */
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& normal, double distance, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Extracts a scalar set from the volume mesh. The scalars are mapped onto the 
  * current extracted plane slice. 
  *
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts a vector set from the volume mesh. The vectors are mapped onto the 
  * current extracted plane slice.
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

#endif 


