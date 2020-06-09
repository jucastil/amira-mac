/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiTessellatedSurfaceExtract_h
#define  _MiTessellatedSurfaceExtract_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/STL/vector>

class MiCellFilterI;
class MiSurfaceMeshUnstructured;
class MiTessellator;

/**
 * @DTEXT Tessellated surface mesh extractor for unstructured and non linear 2D mesh.
 * 
 * @ingroup MeshIViz_Extract_Tessellate
 * 
 * @DESCRIPTION Builds a tessellated linear surface mesh from non linear 2D mesh.
 *   The tessellation is done by using the given MiTessellator (see tessellate()).
 */
class MESHIVIZ_API MiTessellatedSurfaceExtract : virtual public MiBaseExtractor
{
public:
  virtual ~MiTessellatedSurfaceExtract() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiTessellatedSurfaceExtract* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true); 

  /**
  * Builds a new linear surface mesh by tessellating each non linear cell of the input mesh given to the
  * factory method getNewInstance().
  * @param[in] tesselator The instance used to tessellate.
  * @param[in] cellFilter The optional cell filter. surface cells excluded by this filter are neither tessellated nor
  *            included "as is" in the build mesh.
  * @return The tessellated mesh.
  */  
  virtual const MeXSurfaceMeshUnstructured& tessellate(MiTessellator& tesselator, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiTessellatedLineExtract::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) =0;

  /**
  * @copydoc MiTessellatedLineExtract::extractVec3Set()
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
  * @copydoc MiTessellatedLineExtract::getExtract()
  */
 virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif

