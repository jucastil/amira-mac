/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiTessellatedLineExtract_h
#define  _MiTessellatedLineExtract_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/STL/vector>

class MiCellFilterI;
class MiLineMeshUnstructured;
class MiTessellator;

/**
 * @DTEXT Tessellated line mesh extractor for unstructured non linear 1D mesh.
 * 
 * @ingroup MeshIViz_Extract_Tessellate
 * 
 * @DESCRIPTION Builds a tessellated line mesh from a non linear 1D mesh.
 *   The tessellation is done by using the given MiTessellator (see tessellate()).
 *    
 */
class MESHIVIZ_API MiTessellatedLineExtract : virtual public MiBaseExtractor
{
public:
  virtual ~MiTessellatedLineExtract() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiTessellatedLineExtract* getNewInstance(const MiLineMeshUnstructured& mesh, bool parallel = true); 

  /**
  * Builds a new linear line mesh by tessellating each non linear cell of the input mesh given to the
  * factory method getNewInstance().
  * @param[in] tesselator The instance used to tessellate.
  * @param[in] cellFilter The optional cell filter. Line cells excluded by this filter are neither tessellated nor
  *            included "as is" in the build mesh.
  * @return The tessellated mesh.
  */  
  virtual const MeXLineMeshUnstructured& tessellate(MiTessellator& tesselator, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * Extracts a scalar set from the input mesh. For PER_NODE dataset, the value of each point 
  * of the tessellation is calculated by using the shape functions of the input cell and the parametric 
  * coordinates of the each tessellated point. For PER_CELL dataset, the value of each tessellated cell 
  * is just a copy of the value of each input cell.
  *
  * @param[in] inputSet the input scalar set defined on the input mesh.
  * @return the output scalar set defined on the tessellated mesh. 
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) =0;

  /**
  * Extracts a vector set from the input mesh. For PER_NODE dataset, the value of each point 
  * of the tessellation is calculated by using the shape functions of the input cell and the parametric 
  * coordinates of the each tessellated point. For PER_CELL dataset, the value of each tessellated cell 
  * is just a copy of the value of each input cell.
  *
  * @param[in] inputSet the input vector set defined on the input mesh.
  * @return the output vector set defined on the tessellated mesh. 
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
  * Returns the tessellated mesh extracted by the previous call to tessellate().
  */
 virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif

