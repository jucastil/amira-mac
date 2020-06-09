/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIISOLINELINEEXTRACTIJ_H
#define  _MIISOLINELINEEXTRACTIJ_H

#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>

class MiCellFilterIj;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <Inventor/STL/vector>

/**
 * @DTEXT Isoline extractor for structured surface meshes.
 * 
 * @ingroup MeshIViz_Extract_Isoline
 * 
 * @DESCRIPTION Builds a list of lines containing the extracted isolines for the given data set at the given values.
 * 
 * 
 */
class MESHIVIZ_API MiIsolineExtractIj : virtual public MiBaseExtractor
{
public:
  virtual ~MiIsolineExtractIj() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiIsolineExtractIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true);
  static MiIsolineExtractIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true);
  static MiIsolineExtractIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true);
  //@}

 /**
  * Builds the isolines of the given isovalues in the given dataset.
  * @param isovalueList List of values for which an isoline must be computed
  * @param dataSet The input data set used to compute isovalues from
  * @param cellFilter The cell filter
  * @return the output set of isolines
  */
  virtual const std::vector<const MeXLineMeshUnstructured*>&
  extractIsovalue(std::vector<double>& isovalueList, const MiScalardSetIj& dataSet, 
                  const MiCellFilterIj* cellFilter=NULL) = 0;
  /**
  * Computes a scalar set on the extracted isolines.
  * @param inputSet the input scalar set defined on the surface mesh
  * @return the output scalar set defined on the resulting isoline mesh
  */
  virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetIj& inputSet) =0;

  /**
  * Computes a vector set on the extracted isolines.
  * @param inputSet the input vector set defined on the surface mesh
  * @return the output vector set defined on the resulting isoline mesh
  */
  virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetIj& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const std::vector<const MeXLineMeshUnstructured*>& getExtract() const = 0;

};

#endif /* _MIISOLINEEXTRACT_H */

