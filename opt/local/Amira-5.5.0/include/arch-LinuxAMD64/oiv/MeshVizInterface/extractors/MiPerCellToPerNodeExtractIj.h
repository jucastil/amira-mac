/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (December 2009)
**=======================================================================*/
#ifndef  _MiPerCellToPerNodeExtractIj_h
#define  _MiPerCellToPerNodeExtractIj_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetIj.h>

class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;

/**
 * @DTEXT Convert data sets bound per cell into data sets bound per node on a given structured surface mesh.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This conversion tool is another type of extractor which takes a data set bound per cell on a structured
 * surface mesh as input and produces a new data set bound per node on the same mesh. 
 *
 * The value computed at a given node is the average of values from the surrounding cells,
 * except dead cells. 
 * 
 * The following example shows how to convert data sets bound per cell:
 * <PRE>
 *   MiPerCellToPerNodeExtractIj* extract =
 *     MiPerCellToPerNodeExtractIj::getNewInstance(mesh);
 *   const MeXScalardSetIj& perNodeScalarSet = extract->extractScalarSet(perCellScalarSet);
 *   const MeXVec3dSetIj& perNodeVectorSet = extract->extractVec3Set(perCellVectorSet);
 * </PRE>
 *
 */
class MESHIVIZ_API MiPerCellToPerNodeExtractIj : virtual public MiBaseExtractor
{
public:
  virtual ~MiPerCellToPerNodeExtractIj() {}

  //@{
  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPerCellToPerNodeExtractIj* getNewInstance(const MiSurfaceMeshRegular& mesh, bool parallel = true); 
  static MiPerCellToPerNodeExtractIj* getNewInstance(const MiSurfaceMeshRectilinear& mesh, bool parallel = true); 
  static MiPerCellToPerNodeExtractIj* getNewInstance(const MiSurfaceMeshCurvilinear& mesh, bool parallel = true); 
  //@}

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractScalarSet()
  */
  virtual const MeXScalardSetIj& extractScalarSet(const MiScalardSetIj& inputSet) =0;

  /**
  * @copydoc MiPerCellToPerNodeExtractUnstructured::extractVec3Set()
  */ 
  virtual const MeXVec3dSetIj& extractVec3Set(const MiVec3dSetIj& inputSet) = 0;

};

#endif

