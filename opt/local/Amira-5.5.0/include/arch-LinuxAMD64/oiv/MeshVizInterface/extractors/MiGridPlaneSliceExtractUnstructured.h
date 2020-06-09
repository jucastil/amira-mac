/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiGridPlaneSliceExtractUnstructured_H
#define  _MiGridPlaneSliceExtractUnstructured_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshCurvilinear.h>

#include <Inventor/STL/vector>

class MiCellFilterI;

/**
 * @DTEXT Grid plane slice extractor on unstructured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION This extractor is similar to the plane slice extractor except that it creates a structured mesh and probes the 
 * input volume to compute the values at the surface nodes and cells (See MiPointProbeUnstructured for settings).
 * The grid created by this extractor is computed so that it encloses completely the cross section of the input volume mesh marking as dead the
 * cells outside the volume.
 * 
 */

class MESHIVIZ_API MiGridPlaneSliceExtractUnstructured : virtual public MiBaseExtractor
{
public:
    
  virtual ~MiGridPlaneSliceExtractUnstructured() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiGridPlaneSliceExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true);

  /**
  * @copydoc MiGridPlaneSliceExtractIjk::extractGrid()
  */ 
  virtual const MeXSurfaceMeshCurvilinear&
  extractGrid(const MbVec3<double>& normal, double distance, double step, const MiCellFilterI* cellFilter=NULL) = 0;
 
  /**
  * Extracts a PER_NODE scalar set from the volume mesh. The scalars are mapped onto the 
  * current extracted grid. 
  * Even if the binding of the input scalar set is PER_CELL, this extractor cannot produce a PER_CELL extract
  * because it uses the probing mechanism at each grid plane node to extract values and so does not contain
  * PER_CELL values.
  *
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting grid volume mesh
  */
  virtual const MeXScalardSetIj& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * Extracts a PER_NODE vector set from the volume mesh. The vectors are mapped onto the 
  * current extracted grid. 
  * Even if the binding of the input vector set is PER_CELL, this extractor cannot produce a PER_CELL extract
  * because it uses the probing mechanism at each grid plane node to extract values and so does not contain
  * PER_CELL values.
  *
  * @param inputSet the input vec3 set defined on the volume mesh
  * @return the output scalar set defined on the resulting grid volume mesh
  */
  virtual const MeXVec3dSetIj& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshCurvilinear& getExtract() const = 0;

};

#endif /* _MiGridPlaneSliceExtractUnstructured_H */


