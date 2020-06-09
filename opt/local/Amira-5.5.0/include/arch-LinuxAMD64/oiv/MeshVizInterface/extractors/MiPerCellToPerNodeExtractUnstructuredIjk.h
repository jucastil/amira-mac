/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (December 2009)
**=======================================================================*/
#ifndef  _MiPerCellToPerNodeExtractUnstructuredIjk_h
#define  _MiPerCellToPerNodeExtractUnstructuredIjk_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiVolumeMeshHexahedronIjk;

/**
 * @DTEXT Convert data sets bound per cell into data sets bound per node on a given structured hexahedron mesh.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This conversion tool is another type of extractor which takes a data set bound per cell on a
 * MiVolumeMeshHexahedronIjk as input and produces a new data set bound per node on the same mesh. 
 *
 * The value computed at a given node is the average of values from cells sharing this node,
 * except dead cells. 
 * 
 * The following example shows how to convert data sets bound per cell:
 * <PRE>
 *   MiPerCellToPerNodeExtractUnstructuredIjk* extract =
 *     MiPerCellToPerNodeExtractUnstructuredIjk::getNewInstance(mesh);
 *   const MeXScalardSetI& perNodeScalarSet = extract->extractScalarSet(perCellScalarSet);
 *   const MeXVec3dSetI& perNodeVectorSet = extract->extractVec3Set(perCellVectorSet);
 * </PRE>
 *
 */
class MESHIVIZ_API MiPerCellToPerNodeExtractUnstructuredIjk : virtual public MiBaseExtractor
{
public:
  virtual ~MiPerCellToPerNodeExtractUnstructuredIjk() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPerCellToPerNodeExtractUnstructuredIjk* getNewInstance(const MiVolumeMeshHexahedronIjk& mesh, bool parallel = true); 

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractScalarSet()
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) =0;

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

};

#endif

