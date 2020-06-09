/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiPolyhedralToMixVolumeExtract_h
#define  _MiPolyhedralToMixVolumeExtract_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>

#include <Inventor/STL/vector>

class MiCellFilterI;
class MiVolumeMeshUnstructured;

/**
 * @DTEXT Convert polyhedral 3D mesh to mixed volume mesh.
 * 
 * @ingroup MeshIViz_Extract_Utilities
 * 
 * @DESCRIPTION 
 * This conversion tool is another type of extractor which takes a polyhedral volume mesh
 * as input and produces a mixed volume mesh made up of a combination of tetrahedrons 
 * and pyramids compatible with the marching cube algorithm. 
 * 
 * The following example shows how to convert a polyhedral volume mesh to a mixed volume mesh:
 * <PRE>
 *   MiPolyhedralToMixVolume* extract =
 *     MiPolyhedralToMixVolume::getNewInstance(mesh);
 *   const MeXVolumeMeshUnstructured tessMesh = extract->convert();
 * </PRE>
 *
 */
class MESHIVIZ_API MiPolyhedralToMixVolumeExtract : virtual public MiBaseExtractor
{
public:
  virtual ~MiPolyhedralToMixVolumeExtract() {}

  /**
  * @copydoc MiInterpolatedLogicalSliceExtract::getNewInstance()
  */ 
  static MiPolyhedralToMixVolumeExtract* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true); 

  /**
  * Builds the topology and geometry of the mixed volume mesh.
  */  
  virtual const MeXVolumeMeshUnstructured& convert(const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiCellExtractIjk::extractScalarSet()
  */  
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) =0;

 /**
  * @copydoc MiCellExtractIjk::extractVec3Set()
  */  
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

 /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
 virtual const MeXVolumeMeshUnstructured& getExtract() const = 0;

};

#endif

