/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiGridPlaneSliceExtractUnstructuredIjk_H
#define  _MiGridPlaneSliceExtractUnstructuredIjk_H

#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>
#include <MeshVizInterface/extractors/MiGridPlaneSliceExtractIjk.h>

#include <MeshVizInterface/mesh/MiVolumeMeshUnstructuredIjk.h>
#include <MeshVizInterface/mesh/MiVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshCurvilinear.h>

#include <Inventor/STL/vector>

class MiCellFilterIjk;

/**
 * @DTEXT Grid plane slice extractor on unstructured IJK volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION This extractor is similar to the plane slice extractor except that it creates a structured mesh and probes the 
 * input volume to compute the values at the surface nodes and cells (See MiPointProbeUnstructured for settings). 
 * The grid created by this extractor is computed so that it encloses completely the cross section of the input volume mesh marking as dead the
 * cells outside the volume.
 * 
 */

class MESHIVIZ_API MiGridPlaneSliceExtractUnstructuredIjk : virtual public MiGridPlaneSliceExtractIjk
{
public:
    
  virtual ~MiGridPlaneSliceExtractUnstructuredIjk() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiGridPlaneSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  static MiGridPlaneSliceExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true);
 
  /**
  * @copydoc MiGridPlaneSliceExtractUnstructured::extractScalarSet()
  */ 
  virtual const MeXScalardSetIj& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiGridPlaneSliceExtractUnstructured::extractScalarSet()
  */ 
  virtual const MeXScalardSetIj& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * @copydoc MiGridPlaneSliceExtractUnstructured::extractVec3Set()
  */ 
  virtual const MeXVec3dSetIj& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiGridPlaneSliceExtractUnstructured::extractVec3Set()
  */ 
  virtual const MeXVec3dSetIj& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif /* _MiGridPlaneSliceExtractUnstructuredIjk_H */


