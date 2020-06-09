/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MISTREAMLINEEXTRACTUNSTRUCTURED_H
#define  _MISTREAMLINEEXTRACTUNSTRUCTURED_H

#include <MeshVizInterface/extractors/MiStreamlineExtractBase.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>

class MiCellFilterI;
class MiVolumeMeshUnstructured;
class MiSurfaceMeshUnstructured;

#include <Inventor/STL/vector>

/**
 * @DTEXT  Streamline extractor for unstructured volume meshes.
 * 
 * @ingroup MeshIViz_Extract_Streamline
 * 
 * @DESCRIPTION
 *    Builds a list of MiLineMeshCurvilinear interfaces containing streamlines starting 
 *    from a list of source points and probes the input mesh to compute the values at the
 *    streamline nodes (See MiPointProbeUnstructured for settings). @BR
 *    A streamline is a line that is everywhere tangent to a vector field. 
 *    Streamlines are meaningless for unsteady flow, because time is not
 *    taken into account during the computation of the line. 
 *    Streamlines are integrated from a given set of vectors using a Runge/Kutta
 *    method of order 2 .
 * 
 */
class MESHIVIZ_API MiStreamlineExtractUnstructured : virtual public MiStreamlineExtractBase
{
public:

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiStreamlineExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true);
  static MiStreamlineExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true);
  //@}

  /**
  * Builds the topology and geometry of the streamlines starting at the given points in 
  * the given dataset. The resulting streamlines can be retrieved by calling getExtract().
  *
  * @param inputDataSet Defines the vector field for the streamlines integration
  * @param startPoints Defines the list of start points for the streamlines integration
  * @param cellFilter The cell filter
  * @return the extracted streamlines as curvilinear line meshes
  */
  virtual const std::vector<const MeXLineMeshCurvilinear*>&
  extractStreamline(const MiVec3dSetI& inputDataSet, const std::vector<MbVec3d>& startPoints, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiStreamlineExtractIjk::extractScalarSet()
  */ 
  virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiStreamlineExtractIjk::extractVec3Set()
  */ 
  virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiStreamlineExtractIjk::getExtract()
  */ 
  virtual const std::vector<const MeXLineMeshCurvilinear*>& getExtract() const = 0;

};

#endif /* _MISTREAMLINEEXTRACTUNSTRUCTURED_H */
