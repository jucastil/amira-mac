/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiTessellatedVolumeExtract_h
#define  _MiTessellatedVolumeExtract_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiCellFilterI;
class MiVolumeMeshUnstructured;
class MiTessellator;

 /*
 * @DTEXT Tessellated volume extractor for unstructured 3D mesh.
 * 
 * @ingroup MeshIViz_Extract_Tessellate
 * 
 * @DESCRIPTION Builds a tesselated linear volume mesh from a 3D mesh.
 *  The tessellation is done by using the given MiTessellator (see tessellate()).
 */

SoINTERNAL class MESHIVIZ_API MiTessellatedVolumeExtract : virtual public MiBaseExtractor
{
public:
  virtual ~MiTessellatedVolumeExtract() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiTessellatedVolumeExtract* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true); 

  /**
  * Builds a new linear volume mesh by tessellating each cell of the input mesh given to the
  * factory method getNewInstance(). The tessellation is defined by the given tessellator.
  * @param[in] tesselator The instance used to tessellate.
  * @param[in] cellFilter The optional cell filter. volume cells excluded by this filter are neither tessellated nor
  *            included "as is" in the build mesh.
  * @return The tessellated mesh.
  */  
  virtual const MeXVolumeMeshUnstructured& tessellate(MiTessellator& tesselator, const MiCellFilterI* cellFilter=NULL) = 0;

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
  virtual const MeXVolumeMeshUnstructured& getExtract() const = 0;

};

#endif

