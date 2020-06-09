/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MILOGICALSLICEEXTRACTREGULAR_H
#define  _MILOGICALSLICEEXTRACTREGULAR_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extractors/MiBaseLogicalSliceExtract.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshRegular.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>


class MiCellFilterIjk;
class MiVolumeMeshRegular;

/**
 * @DTEXT Logical slice extractor for a regular volume mesh. 
 * 
 * @ingroup MeshIViz_Extract_Logicalslice
 * 
 * @DESCRIPTION A logical slice is a surface extracted from a IJK volume mesh. 
 * It is defined by a slice axis, an index and a boolean flag. The slice axis 
 * can be SLICE_I, SLICE_J or SLICE_K. The index represents one of the cell 
 * id to extract. For instance,
 * @code
 *   extractLogicalSlice(SLICE_K,10,true);
 * @endcode
 * extract all the cell(i,j,k) with k=10, extract the upper vertex (along the 
 * k-axis) of these cells. 
 * When a cell filter is provided, the returned surface contains dead cells.
 *
 * The methods extractScalarSet() and extractVec3Set() compute a dataset that can 
 * be mapped onto the extracted surface. The new dataset is extracted from 
 * the given dataset and its size equals either the number of polygons or 
 * the number of vertices in the extracted surface. If the input dataset has 
 * a PER_CELL binding, the data of the selected cells are extracted and the 
 * size of this extracted dataset equals the number of extracted polygons.
 *
 */
class MESHIVIZ_API MiLogicalSliceExtractRegular : virtual public MiBaseExtractor
{
public:
  virtual ~MiLogicalSliceExtractRegular() {} 
  
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiLogicalSliceExtractRegular* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);

  /**
  * Builds the topology and geometry of the logical slice at the given cell index 
  * along the given axis. 
  * When a cell filter is provided, the returned surface may contain dead cells.
  * 
  * @param axis the axis along which the extraction will be performed.
  * @param sliceIndex the cell index along the selected axis to extract.
  * @param upperVertex extract the upper vertices of the selected cells if true, the lower vertices otherwise.
  * @param cellFilter the cell filter to be used to accept or reject cells.
  */
  virtual const MeXSurfaceMeshRegular& extractLogicalSlice(SliceAxis axis, size_t sliceIndex, bool upperVertex, const MiCellFilterIjk* cellFilter=NULL) = 0;


  /**
  * @copydoc MiCellExtractIjk::extractScalarSet()
  */
  virtual const MeXDataSetIj<double>& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  */
  virtual const MeXDataSetIj<MbVec3d>& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshRegular& getExtract() const = 0;

};

#endif 


