/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiGridPlaneSliceExtractIjk_H
#define  _MiGridPlaneSliceExtractIjk_H

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>

#include <MeshVizInterface/mesh/MiVolumeMeshRegular.h>
#include <MeshVizInterface/mesh/MiVolumeMeshRectilinear.h>
#include <MeshVizInterface/mesh/MiVolumeMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshCurvilinear.h>

#include <Inventor/STL/vector>

class MiCellFilterIjk;

/**
 * @DTEXT Grid plane slice extractor on structured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION This extractor is similar to the plane slice extractor except that it creates a structured mesh and probes the 
 * input volume to compute the values at the surface nodes and cells (See MiPointProbeUnstructured for settings on curvilinear mesh). 
 * The grid created by this extractor is computed so that it encloses completely the cross section of the input volume mesh marking as dead the
 * cells outside the volume.
 * 
 */

class MESHIVIZ_API MiGridPlaneSliceExtractIjk : virtual public MiBaseExtractor
{
public:
    
  virtual ~MiGridPlaneSliceExtractIjk() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiGridPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);
  static MiGridPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);
  static MiGridPlaneSliceExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);
  //@}

  /**
  * Builds the topology and geometry of a curvilinear surface mesh defined by the given plane normal and distance to origin.
  * This grid is computed so that it encloses completely the cross section of the input volume mesh. 
  * @param normal Vector normal to the grid plane slice
  * @param distance Position of the plane relatively to the origin along the normal
  * @param step Distance between two consecutive nodes in both directions of the plane
  * @param cellFilter The cell filter object. 
  * @return A curvilinear surface mesh representing the grid plane slice
  */
  virtual const MeXSurfaceMeshCurvilinear&
  extractGrid(const MbVec3<double>& normal, double distance, double step, const MiCellFilterIjk* cellFilter=NULL) = 0;
 
  /**
  * @copydoc MiCellExtractIjk::extractScalarSet(const MiScalardSetIjk& inputSet)
  */
  virtual const MeXScalardSetIj& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set(const MiVec3dSetIjk& inputSet)
  */
  virtual const MeXVec3dSetIj& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshCurvilinear& getExtract() const = 0;

};

#endif /* _MiGridPlaneSliceExtractIjk_H */


