/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (October 2009)
**=======================================================================*/
#ifndef  _MiClipLineExtractIj_h
#define  _MiClipLineExtractIj_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>

class MiCellFilterIj;
class MiSurfaceMeshRegular;
class MiSurfaceMeshCurvilinear;
class MiSurfaceMeshRectilinear;
class MiTessellator;

/**
 * @DTEXT Clip line extractor for structured surface meshes
 * 
 * @ingroup MeshIViz_Extract_ClipLine
 * 
 * @DESCRIPTION A clip line is the intersection of a given plane with the surface mesh. The extracted line
 * is an unstructured line.
 * 
 */
class MESHIVIZ_API MiClipLineExtractIj : virtual public MiBaseExtractor
{
public:
  virtual ~MiClipLineExtractIj() {}

  //@{
  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiClipLineExtractIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiClipLineExtractIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  static MiClipLineExtractIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true, MiTessellator* tessellator=NULL);
  //@}

  /**
  * Builds the topology and geometry of a line intersecting the surface mesh and the given plane.
  * 
  * @return the clip line extracted as an unstructured line mesh.
  * @param normal Vector normal to the plane 
  * @param distance Position of the plane relatively to the origin along the normal
  * @param cellFilter The cell filter object. 
  * @return An unstructured line mesh representing the clip line
  */
  virtual const MeXLineMeshUnstructured& extractLine(const MbVec3<double>& normal, double distance, const MiCellFilterIj* cellFilter=NULL) = 0;

  /**
  * Extracts a scalar set from the surface mesh. The scalars are mapped onto the 
  * current extracted clip sline. 
  *
  * @param inputSet the input scalar set defined on the surface mesh
  * @return the output scalar set defined on the resulting line mesh
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIj& inputSet) = 0;

  /**
  * Extracts a vector set from the surface mesh. The vectors are mapped onto the 
  * current extracted clip line.
  *
  * @param inputSet the input vec3 set defined on the surface mesh
  * @return the output scalar set defined on the resulting line mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIj& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif 


