/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (December 2009)
**=======================================================================*/
#ifndef  _MiPerCellToPerNodeExtractUnstructured_h
#define  _MiPerCellToPerNodeExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

class MiVolumeMeshUnstructured;
class MiSurfaceMeshUnstructured;

/**
 * @DTEXT Convert data sets bound per cell into data sets bound per node on a given unstructured mesh.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This conversion tool is another type of extractor which takes a data set bound per cell on an
 * unstructured mesh as input and produces a new data set bound per node on the same mesh. 
 *
 * The value computed at a given node is the average of values from cells sharing this node,
 * except dead cells. 
 * 
 * The following example shows how to convert data sets bound per cell:
 * <PRE>
 *   MiPerCellToPerNodeExtractUnstructured* extract =
 *     MiPerCellToPerNodeExtractUnstructured::getNewInstance(mesh);
 *   const MeXScalardSetI& perNodeScalarSet = extract->extractScalarSet(perCellScalarSet);
 *   const MeXVec3dSetI& perNodeVectorSet = extract->extractVec3Set(perCellVectorSet);
 * </PRE>
 *
 */
class MESHIVIZ_API MiPerCellToPerNodeExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiPerCellToPerNodeExtractUnstructured() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPerCellToPerNodeExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true); 
  static MiPerCellToPerNodeExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true); 
  //@}

  /**
  * Converts a PER_CELL scalar set defined on the input mesh into a PER_NODE scalar set.
  *
  * @param inputSet The input PER_CELL scalar set defined on the input mesh.
  * @return The output PER_NODE scalar set defined on the input mesh.
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) =0;

  /**
  * Converts a PER_CELL vector set defined on the input mesh into a PER_NODE vecto set.
  *
  * @param inputSet The input PER_CELL vector set defined on the input mesh.
  * @return The output PER_NODE vector set defined on the input mesh.
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

};

#endif

