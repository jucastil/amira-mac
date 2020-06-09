/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIISOLINEEXTRACT_H
#define  _MIISOLINEEXTRACT_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/STL/vector>

class MiSurfaceMeshUnstructured;
class MiCellFilterI;
class MiLineMeshUnstructured;

/**
 * @DTEXT Isoline extractor for unstructured surface meshes.
 * 
 * @ingroup MeshIViz_Extract_Isoline
 * 
 * @DESCRIPTION Builds a list of lines containing the extracted isolines for the given data set at the given values.
 * 
 * 
 */
class MESHIVIZ_API MiIsolineExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiIsolineExtractUnstructured() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiIsolineExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true); 

  /**
  * @copydoc MiIsolineExtractIj::extractIsovalue()
  */  
  virtual const std::vector<const MeXLineMeshUnstructured*>&
  extractIsovalue(std::vector<double>& isovalueList, const MiScalardSetI& dataSet, 
                       const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiIsolineExtractIj::extractScalarSet()
  */  
  virtual const std::vector< const MeXScalardSetI* >& extractScalarSet(const MiScalardSetI& inputSet) =0;

 /**
  * @copydoc MiIsolineExtractIj::extractVec3Set()
  */  
  virtual const std::vector< const MeXVec3dSetI* >& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
 virtual const std::vector<const MeXLineMeshUnstructured*>& getExtract() const = 0;

};

#endif /* _MIISOSURFEXTRACT_H */


