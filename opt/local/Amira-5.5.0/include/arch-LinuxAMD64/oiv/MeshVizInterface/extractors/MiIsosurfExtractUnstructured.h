/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MIISOSURFEXTRACTUNSTRUCTURED_H
#define  _MIISOSURFEXTRACTUNSTRUCTURED_H

#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterI;
class MiVolumeMeshUnstructured;
class MiTessellator;

/**
* @DTEXT Isosurface extractor for unstructured meshes
* 
* @ingroup MeshIViz_Extract_Isosurf
* 
* @DESCRIPTION Builds the isosurface of the given isovalue in the given dataset.
* 
* When MiVolumeCell::getIsosurfTopology() can not be defined, for instance in polyhedral
* and non-linear meshes, an MiTessellator is required to produce a volume mesh made up of
* cells compatible with the marching cube algorithm. 
* 
*/
class MESHIVIZ_API MiIsosurfExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiIsosurfExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiIsosurfExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiIsosurfExtractIjk::extractIsovalue()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractIsovalue(double isovalue, const MiScalardSetI& dataSet, const MiCellFilterI* cellFilter=NULL) = 0;

  /**
  * @copydoc MiIsosurfExtractIjk::extractScalarSet()
  */ 
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiIsosurfExtractIjk::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;
};


#endif 


