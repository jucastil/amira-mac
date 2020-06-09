/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (December 2009)
**=======================================================================*/
#ifndef  _MiPerCellToPerNodeExtractIjk_h
#define  _MiPerCellToPerNodeExtractIjk_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIjk.h>

class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;


/**
 * @DTEXT Convert data sets bound per cell into data sets bound per node on a given structured volume mesh.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This conversion tool is another type of extractor which takes a data set bound per cell on a
 * structured volume mesh as input and produces a new data set bound per node on the same mesh. 
 *
 * The value computed at a given node is the average of values from the surrounding cells,
 * except dead cells. 
 * 
 * The following example shows how to convert data sets bound per cell:
 * <PRE>
 *   MiPerCellToPerNodeExtractIjk* extract =
 *     MiPerCellToPerNodeExtractIjk::getNewInstance(mesh);
 *   const MeXScalardSetIjk& perNodeScalarSet = extract->extractScalarSet(perCellScalarSet);
 *   const MeXVec3dSetIjk& perNodeVectorSet = extract->extractVec3Set(perCellVectorSet);
 * </PRE>
 *
 */
class MESHIVIZ_API MiPerCellToPerNodeExtractIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiPerCellToPerNodeExtractIjk() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPerCellToPerNodeExtractIjk* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);
  static MiPerCellToPerNodeExtractIjk* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);
  static MiPerCellToPerNodeExtractIjk* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);
  //@}

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractScalarSet()
  */
  virtual const MeXScalardSetIjk& extractScalarSet(const MiScalardSetIjk& inputSet) =0;

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractVec3Set()
  */ 
  virtual const MeXVec3dSetIjk& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif

