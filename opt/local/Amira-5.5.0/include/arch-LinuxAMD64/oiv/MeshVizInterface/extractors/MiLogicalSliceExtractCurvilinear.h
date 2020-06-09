/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MILOGICALSLICEEXTRACTCURVILINEAR_H
#define  _MILOGICALSLICEEXTRACTCURVILINEAR_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extractors/MiBaseLogicalSliceExtract.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshCurvilinear.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>

class MiCellFilterIjk;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT Logical slice extractor for a curvilinear volume mesh. 
 * 
 * @ingroup MeshIViz_Extract_Logicalslice
 * 
 * @see MiLogicalSliceExtractRegular
 *
 */
class MESHIVIZ_API MiLogicalSliceExtractCurvilinear : virtual public MiBaseExtractor
{
public:
  virtual ~MiLogicalSliceExtractCurvilinear() {} 
  
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiLogicalSliceExtractCurvilinear* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);

  /**
  * @copydoc MiLogicalSliceExtractRegular::extractLogicalSlice()
  */
  virtual const MeXSurfaceMeshCurvilinear& extractLogicalSlice(SliceAxis axis, size_t sliceIndex, bool upperVertex, const MiCellFilterIjk* cellFilter=NULL) = 0;

 /**
  * @copydoc MiLogicalSliceExtractRegular::extractScalarSet().
  */
  virtual const MeXDataSetIj<double>& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * @copydoc MiLogicalSliceExtractRegular::extractVec3Set().
  */
  virtual const MeXDataSetIj<MbVec3d>& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiLogicalSliceExtractRegular::getExtract().
  */
  virtual const MeXSurfaceMeshCurvilinear& getExtract() const = 0;


};

#endif 


