/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIINTERPOLATEDLOGICALSLICEEXTRACT_H
#define  _MIINTERPOLATEDLOGICALSLICEEXTRACT_H

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extractors/MiBaseLogicalSliceExtract.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>

class MiCellFilterIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;

/**
 * @DTEXT Interpolated logical slice extractor for structured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Logicalslice
 * 
 * @DESCRIPTION An interpolated logical slice is similar to a logical slice except that instead of 
 * displaying the slice only on the side of the cells, it can interpolate a slice inside cells. 
 * This is done by providing a floating point value representing the offset along the cell axis.
 * 
 */
class MESHIVIZ_API MiInterpolatedLogicalSliceExtract : virtual public MiBaseExtractor
{
public:
  virtual ~MiInterpolatedLogicalSliceExtract() {};

  //@{
  /**
  * Factory method returning a new instance of a class implementing this abstract class.
  * @param mesh The input mesh 
  * @param parallel When true, tries to create an extract module using a parallel algorithm to speed up the extraction. 
  * @note Only some of the extraction algorithms have a parallel implementation.
  */ 
  static MiInterpolatedLogicalSliceExtract* getNewInstance(const MiVolumeMeshRegular& mesh, bool parallel = true);
  static MiInterpolatedLogicalSliceExtract* getNewInstance(const MiVolumeMeshCurvilinear& mesh, bool parallel = true);
  static MiInterpolatedLogicalSliceExtract* getNewInstance(const MiVolumeMeshRectilinear& mesh, bool parallel = true);
  //@}

  /**
  * Builds the topology and geometry of the Interpolated Logical Slice at the given value 
  * along the given slice axis.
  */
  virtual const MeXSurfaceMeshUnstructured& extractInterpolatedLogicalSlice(SliceAxis, double sliceValue, const MiCellFilterIjk* cellFilterIjk=NULL) = 0;
  
 /**
  * Extracts a scalar set from the volume mesh. The scalars are mapped onto the 
  * current extracted interpolated logical slice. 
  *
  * @param inputSet the input scalar set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh. 
  */
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetIjk& inputSet) = 0;

  /**
  * Extracts a vector set from the volume mesh. The vectors are mapped onto the 
  * current extracted logical slice. 
  *
  * @param inputSet the input vector set defined on the volume mesh
  * @return the output scalar set defined on the resulting surface mesh
  */
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetIjk& inputSet) = 0;

  /**
  * Returns the result of the extraction. 
  * @note This method returns the same object returned by extractInterpolatedLogicalSlice without recomputing a new slice.
  * This is useful to avoid to have to store the extracted surface in an intermediate object.
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif /* _MIINTERPOLATEDLOGICALSLICEEXTRACT_H */


