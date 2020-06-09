/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MISTREAMLINEEXTRACTUNSTRUCTUREDIJK_H
#define  _MISTREAMLINEEXTRACTUNSTRUCTUREDIJK_H

#include <MeshVizInterface/extractors/MiStreamlineExtractBase.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshCurvilinear.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>

class MiCellFilterIjk;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;

#include <Inventor/STL/vector>

/**
 * @DTEXT  Streamline extractor for unstructured IJK volume meshes.
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
class MESHIVIZ_API MiStreamlineExtractUnstructuredIjk : virtual public MiStreamlineExtractBase
{
public:
  
  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiStreamlineExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshUnstructuredIjk& mesh, bool parallel = true);
  static MiStreamlineExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true);
  //@{

  //@{
  /**
  * Builds the topology and geometry of the streamlines starting at the given points in 
  * the given dataset. The resulting streamlines can be retrieved by calling getExtract().
  *
  * Note: the dataset associated to the mesh 
  * are not extracted by this method. Thus, the resulting streamlines generated
  * contain only their geomtery and topology extracted from the input dataset.
  * In order to extract some dataset the methods extractScalarSet(), extractVec3Set()
  * must be explicitly called after extractStreamline().
  * Returns the result of the streamline extraction as a list of line meshes.
  *
  * @param inputdataset: defines the vector field for the streamlines integration
  * @param startPoints: defines the list of start points for the streamlines integration
  * @param cellFilter:
  * @return the extracted streamlines as curvilinear line meshes
  */
  virtual const std::vector<const MeXLineMeshCurvilinear*>&
  extractStreamline(const MiVec3dSetI& inputdataset, const std::vector<MbVec3d>& startPoints, const MiCellFilterIjk* cellFilter=NULL) = 0;
  virtual const std::vector<const MeXLineMeshCurvilinear*>&
  extractStreamline(const MiVec3dSetIjk& inputdataset, const std::vector<MbVec3d>& startPoints, const MiCellFilterIjk* cellFilter=NULL) = 0;
  //@{

 /**
 * Computes a PER_NODE scalar set on the extracted streamlines. 
 * Note : The argument i of the method MiScalardSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar sets defined on the resulting streamline meshes
 */
 virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetI& inputSet) = 0;

 /**
 * Computes a PER_CELL scalar set on the extracted isosurface. 
 * Note : The argument i,j,k of the method MiScalardSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input scalar set defined on the volume mesh
 * @return the output scalar sets defined on the resulting streamline meshes
 */
 virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

 /**
 * Computes a vector set on the extracted isosurface.
 * Note : The argument i of the method MiVec3dSetI::get(i) refers
 * to the i-th node of the mesh. Thus the binding of the inputSet
 * must be PER_NODE. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting streamline meshes
 */
 virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
 * Computes a vector set on the extracted isosurface.
 * Note : The argument i,j,k of the method MiVec3dSetIjk::get(i,j,k) refers
 * to the cell (i,j,k). Thus the binding of the inputSet
 * must be PER_CELL. An exception is thrown otherwise.
 * 
 * @param inputSet the input vec3 set defined on the volume mesh
 * @return the output scalar set defined on the resulting streamline meshes
 */
 virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

 /**
 * Returns the result of the extraction. 
 * @note  This method returns the same objects returned by extractStreamline without recomputing new streamlines.
 * This is useful to avoid to have to store the extracted streamlines in intermediate objects.
 */
 virtual const std::vector<const MeXLineMeshCurvilinear*>& getExtract() const = 0;

};


#endif 


