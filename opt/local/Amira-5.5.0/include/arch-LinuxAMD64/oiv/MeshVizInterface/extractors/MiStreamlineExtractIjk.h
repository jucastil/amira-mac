/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MISTREAMLINEEXTRACTIJK_H
#define  _MISTREAMLINEEXTRACTIJK_H

#include <MeshVizInterface/extractors/MiStreamlineExtractBase.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>

class MiCellFilterIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

#include <Inventor/STL/vector>

/**
 * @DTEXT  Streamline extractor for structured volume meshes.
 * 
 * @ingroup MeshIViz_Extract_Streamline
 * 
 * @DESCRIPTION
 *    Builds a list of MiLineMeshCurvilinear interfaces containing streamlines starting 
 *    from a list of source points and probes the input mesh to compute the values at the
 *    streamline nodes (See MiPointProbeUnstructured for settings on curvilinear mesh). @BR 
 *    A streamline is a line that is everywhere tangent to a vector field.
 *    Streamlines are meaningless for unsteady flow, because time is not
 *    taken into account during the computation of the line. 
 *    Streamlines are integrated from a given set of vectors using a Runge/Kutta
 *    method of order 2 .
 * 
 */
class MESHIVIZ_API MiStreamlineExtractIjk : virtual public MiStreamlineExtractBase
{
public:

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiStreamlineExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);
  static MiStreamlineExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);
  static MiStreamlineExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);
  //@}

  /**
  * Builds the topology and geometry of the streamlines starting at the given points in 
  * the given dataset. 
  *
  * @param inputdataset Defines the vector field for the streamlines integration.
  * @param startPoints Defines the list of start points for the streamlines integration.
  * @param cellFilter The call filter.
  * @return the extracted streamlines as a set of curvilinear line meshes.
  */
  virtual const std::vector<const MeXLineMeshCurvilinear*>&
  extractStreamline(const MiVec3dSetIjk& inputdataset, const std::vector<MbVec3d>& startPoints, const MiCellFilterIjk* cellFilter=NULL) = 0;

  /**
  * Extracts from the mesh a list of scalar sets. The scalars are mapped onto the 
  * current extracted streamlines. If the dataset is binded PER_NODE the scalars
  * are interpolated and one scalar is binded per node of the extracted streamlines.
  * Otherwise one scalar is binded per edge of the extracted streamlines.
  *
  * @param inputSet the input scalar set defined on the original volume mesh
  * @return the output scalar sets defined on the resulting edge meshes
  */
  virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts from the mesh a vector set. The vectors are mapped onto the 
  * current extracted streamlines. If the dataset is binded PER_NODE the vectors
  * are interpolated and one vector is binded per node of the extracted streamlines.
  * Otherwise one vector is binded per edge of the extracted streamlines.
  *
  * @param inputSet the input vector set defined on the original volume mesh
  * @return the output scalar sets defined on the resulting edge meshes
  */
  virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const std::vector<const MeXLineMeshCurvilinear*>& getExtract() const = 0;

};

#endif /* _MISTREAMLINEEXTRACTIJK_H */
