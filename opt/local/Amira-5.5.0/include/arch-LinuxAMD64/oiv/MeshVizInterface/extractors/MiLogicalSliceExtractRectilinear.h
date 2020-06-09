/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MILOGICALSLICEEXTRACTRECTILINEAR_H
#define  _MILOGICALSLICEEXTRACTRECTILINEAR_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extractors/MiBaseLogicalSliceExtract.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshRectilinear.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>

class MiCellFilterIjk;
class MiVolumeMeshRectilinear;

/**
 * @DTEXT Logical slice extractor for a rectilinear volume mesh. 
 * 
 * @ingroup MeshIViz_Extract_Logicalslice
 * 
 * See MiLogicalSliceExtractRegular
 *
 */
class MESHIVIZ_API MiLogicalSliceExtractRectilinear : virtual public MiBaseExtractor
{
public:
  virtual ~MiLogicalSliceExtractRectilinear() {} 
  
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance().
  */
  static MiLogicalSliceExtractRectilinear* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);

  /**
  * @copydoc MiLogicalSliceExtractRegular::extractLogicalSlice()
  */
  virtual const MeXSurfaceMeshRectilinear& extractLogicalSlice(SliceAxis axis, size_t sliceIndex, bool upperVertex, const MiCellFilterIjk* cellFilter=NULL) = 0;

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
  virtual const MeXSurfaceMeshRectilinear& getExtract() const = 0;

};

#endif 


